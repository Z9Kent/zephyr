

#include <cstdint>
#include <cstddef>		// offsetof
#include <type_traits>
#include <functional>
#include <zephyr/kernel.h>
#include "variableArray.h"
#include "kas_string.h"
#include "init_from_list.h"
#include "meta/meta.hpp"

// XXX do everything here
#include "Z9LockIOProtocol_Current_MetaData.h"

#pragma once
#define Z9_STRING KAS_STRING

namespace z9::protocols::z9lockio
{
	using namespace meta;
	using namespace kas;

// begin XXX
// list of top-level formats
using FORMATS_TYPES = transform<Z9_TYPES, quote<front>>;


struct extract_names
{
    template <typename T>
    using invoke = at_c<T, 1>;
};

using FORMATS_NAMES = transform<Z9_TYPES, extract_names>;


// list of member types
struct extract_member_types
{
    struct get_member_types
    {
        template <typename T>
        using invoke = at_c<T, 3>;
    };

    template <typename T>
    using invoke = transform<at_c<T, 2>, get_member_types>;
};

using MEMBER_TYPES = join<transform<Z9_TYPES, extract_member_types>>;

// find types not previously defined
struct not_in_base
{
    template <typename T>
    using invoke = bool_<!in<FORMATS_TYPES, T>::value>;
};

using INT_TYPES = filter<unique<MEMBER_TYPES>, not_in_base>;
using ALL_DEFNS = concat<Z9_TYPES, INT_TYPES>;
using ALL_TYPES = concat<FORMATS_TYPES, INT_TYPES>;

// end XXX


struct Z9Serialize_base
{
	//using vt_base_t = Z9Serialize_base;
	
	using reader_t   = std::function<uint8_t()>;
	using writer_t   = std::function<void(uint8_t)>;
	using printer_t  = const char *(*)();
	using width_t    = uint16_t;

	// NB: `width` is `sizeof` of the structure field. `size` is bytes of serialization
	virtual void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size)   const = 0;
	virtual void serialize  (writer_t const& writer, uint8_t const *source, width_t width, width_t size) const = 0;
	virtual void print      (printer_t& print, uint8_t const *source, width_t width) const {}		// not ABC yet
	// return size in bytes of entire structure
	virtual width_t width   () const { return {}; };	
};

inline const Z9Serialize_base *getFormatter(uint8_t n);

template <typename T, typename = void> 
struct Z9Serialize;

template <typename T, typename = void>
struct Z9Serialize_ptr
{
	//using type = Z9Serialize_ptr;
	static const inline Z9Serialize<T> instance;
	static constexpr Z9Serialize_base const * const value = &instance;
};

template <unsigned N, bool S>
struct Z9Serialize_int : Z9Serialize_base
{
	using type = Z9Serialize_int;

	width_t width() const override { return N; }

	void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const override
	{

		// since can only read forward and serialized may not be page aligned,
		// read to temp, then write out LittleEndian (reversed)
		uint8_t temp[N], *p = temp;
		for (unsigned n = N; n--; )
			*p++ = reader();

		// TODO: base code on std::endian<> results
		for (unsigned n = N; n--; )
			*dest++ = *--p;
		
		// sign extend `signed` variables
		if constexpr (S)
		{
			uint8_t extend = *p & 0x80 ? ~0 : 0;
			for (unsigned n = N; n++ < width; )
				*dest++ = extend;
		}
		else for (unsigned n = N; n++ < width; )
			*dest++ = 0;
	}
	
	void serialize(writer_t const& writer, uint8_t const *source, width_t width, width_t size) const override
	{
		// TODO: Vase code on std::endian<> results
		// serialize data into temp buffer, sign extending as required
		uint8_t temp[width];
		const uint8_t *p = &temp[width];

		// if serialized width is same or smaller than source, copy directly
		if (width <= N)
			p = source + N;
		else
		{
			// copy data to temp buffer, sign extending as required
			auto extra = width - N;
			std::memcpy(temp+extra, source, N);

			if constexpr (S)
			{
				uint8_t sign = source[N-1] & 0x80 ? 0xff : 0;
				std::memset(temp, sign, extra);
			}
			else
				std::memset(temp, 0, extra);
		}

		// copy prepared data to output
		while (width--)
			writer(*--p);
	}
};

template <typename T, typename NAME, typename...ENUMS>
struct Z9Serialize_enum : Z9Serialize<std::underlying_type_t<T>>
{
	// just the `print` support. 

};

// there doesn't seem to be a `std::` type trait to get base type from array
template <typename T>
struct array_base {};
template <typename T, std::size_t N>
struct array_base <T[N]> { using type = T; };
template <typename T>
using array_base_t = typename array_base<T>::type;

template <typename T, std::size_t N>
struct Z9Serialize_array : Z9Serialize_base
{
	using type = Z9Serialize_array;

	width_t width() const override { return sizeof(T) * N; }

	void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const override
	{
		size  /= N;
		width /= N;
		for (auto n = N; n--; dest += width)
			Z9Serialize<T>().deserialize(reader, dest, width, size);
	}
	
	void serialize(writer_t const& writer, const uint8_t *source, width_t width, width_t size) const override
	{
		size  /= N;
		width /= N;
		for (auto n = N; n--; source += width)
			Z9Serialize<T>().serialize(writer, source, width, size);
	}
};

template <std::size_t N, typename COUNTER_T, typename VALUE_T>
struct Z9Serialize<variableArray<N, COUNTER_T, VALUE_T>> : Z9Serialize_base
{
	using type = Z9Serialize;
	width_t width() const override { return sizeof(COUNTER_T) + N + sizeof(VALUE_T); }

	void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const override
	#if 1
	;
	#else
	{
		COUNTER_T counter;
		Z9Serialize<COUNTER_T>().deserialize(reader, (uint8_t *)(void *)&counter, sizeof(counter), size);
    
		VALUE_T   data[N];
		auto p = static_cast<uint8_t *>((void *)data);
		for (auto n = counter; n--; p += width)
			Z9Serialize<VALUE_T>().deserialize(reader, p, width, size);
		
		auto value = static_cast<variableArray<N, COUNTER_T, VALUE_T> *>((void *)dest);
		value->set(counter, data);
	}
	#endif
	
	void serialize(writer_t const& writer, const uint8_t *source, width_t width, width_t size) const override
	{
		//serialize_struct(writer, dest, width, NAME(), members, MEMBERS::size()); 
	}
	
}; 


template <typename T, typename NAME, typename MEMBERS, typename...Xtra>
struct Z9Serialize_struct : Z9Serialize_base
{
	using type = Z9Serialize_struct;
    struct SerializeItem
    {
		template <typename B, typename O, typename S, typename FN, typename N>
		constexpr SerializeItem(meta::list<B, O, S, FN, N>) 
			: bytes     { B::value }
			, offset    { O::value }
			, size      { S::value }
			, format    { meta::find_index<ALL_TYPES, FN>::value }
			, name      { N::value }
			{}
      
		constexpr SerializeItem(uint16_t bytes, uint16_t offset, uint16_t size,
			uint8_t format,  const char *name)
				: bytes (bytes)
				, offset (offset)
				, size (size)
				, format (format)
				, name (name)
				{}
				
        uint16_t bytes;          // serialized size of item
        uint16_t offset;         // offset of item into structure
        uint16_t size;           // size of item in structure
        uint16_t format;			// index into formats
        const char *name;       // member name for print
    };

	using message_t = T;
	using name      = NAME;
	static constexpr auto members = init_from_list<SerializeItem, MEMBERS>::value;

	void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const override
	{
		deserialize_struct(reader, dest, width, NAME(), members, MEMBERS::size()); 
	}
	
	void serialize(writer_t const& writer, const uint8_t *source, width_t width, width_t size) const override
	{
		serialize_struct(writer, source, width, NAME(), members, MEMBERS::size()); 
	}
	
	void deserialize_struct(reader_t const& reader, uint8_t *dest, width_t width, const char *name, 
                            SerializeItem const *items, uint8_t num_items) const
    {
		printk("Deserializing type: %s, %u members\n", name, MEMBERS::size());
		for (auto p = items; num_items--; ++p)
		{
		//	printk("--Deserilizing member: %s, offset=%u, size=%u, bytes=%u, format=%u\n",
		//			p->name, p->offset, p->size, p->bytes, p->format);
			getFormatter(p->format)->deserialize(reader, dest + p->offset, p->size, p->bytes);
		}
	}
	void serialize_struct(writer_t const& writer, const uint8_t *source, width_t width, const char *name, 
                            SerializeItem const *items, uint8_t num_items) const
    {
		printk("Serializing type: %s, %u members\n", name, MEMBERS::size());
		for (auto p = items; num_items--; ++p)
		{
		//	printk("--Deserilizing member: %s, offset=%u, size=%u, bytes=%u, format=%u\n",
		//			p->name, p->offset, p->size, p->bytes, p->format);
			getFormatter(p->format)->serialize(writer, source + p->offset, p->size, p->bytes);
		}
	}
};

// specialize Z9Serialize based on `T`
template <typename T>
struct Z9Serialize<T, std::enable_if_t<std::is_integral_v<T>>> :
		Z9Serialize_int<sizeof(T), std::is_signed_v<T>> {};

template <typename T>
struct Z9Serialize<T, std::enable_if_t<std::is_enum_v<T>>> : 
		Z9Serialize<std::underlying_type_t<T>> {};

template <typename T>
struct Z9Serialize<T, std::enable_if_t<std::is_bounded_array_v<T>>> : 
		Z9Serialize_array<array_base_t<T>, std::extent_v<T>> {};

template <typename T, typename NAME, typename MEMBERS, typename...XTRA>
	struct Z9Serialize<list<T, NAME, MEMBERS, XTRA...>> : 
		Z9Serialize_struct<T, NAME, MEMBERS, XTRA...> {};

// begin XXX
//using Z_t = transform<Z9_TYPES, quote<Z9Serialize_ptr>>::type;
using Z_t = transform<ALL_DEFNS, quote<Z9Serialize_ptr>>::type;
using ZZZZ = init_from_list<Z9Serialize_base const *, Z_t>;
constexpr auto ZZZZ_value = init_from_list<Z9Serialize_base const *, Z_t>::value;
//using Z_t = init_from_list<Z9Serialize_base const *, Z9_TYPES, quote<Z9Serialize_ptr>>;

// generate list of formatters
//using ZZZZ = init_from_list<Z9Serialize_base const *, FORMATS, Z9_TYPE_CTOR>;

//constexpr auto ZZZZ = init_from_list<Z9Serialize_base const *, Z_t>();
//constexpr auto ZZZZ_size  = init_from_list<Z9Serialize_base const *, Z_t>::size;
//using ZZZZ = init_from_list<Z9Serialize_base const *, Z9_TYPES, Z9_TYPE_CTOR>;

//using ZZZZ = init_from_list<Z9Serialize_base const *, transform<Z9_TYPES, quote<Z9Serialize_ptr>>>;

template <typename T>
constexpr const Z9Serialize_base *getFormatter()
{
    static_assert(ZZZZ::size == ALL_TYPES::size());
	static_assert(ALL_DEFNS::size() == ALL_TYPES::size());
    //static_assert(INT_TYPES::size() == 4);
    //static_assert(DISCRIMINATORS_t::size() == 46);

    using N = meta::find_index<FORMATS_TYPES, T>;

    //return formatters[N::value];
    //return ZZZZ.data[n];
    //return ZZZZ.data[N::value];
    //return ZZZZ().value[N::value];
    return ZZZZ_value[N ::value];
    return {};

}

const Z9Serialize_base *getFormatter(uint8_t n)
{
	return ZZZZ_value[n];
}

template <std::size_t N, typename COUNTER_T, typename VALUE_T>
void Z9Serialize<variableArray<N, COUNTER_T, VALUE_T>>
:: deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const 
	{
#if 0
		COUNTER_T counter;
		Z9Serialize<COUNTER_T>().deserialize(reader, (uint8_t *)(void *)&counter, sizeof(counter), size);
    
		VALUE_T   data[N];
		auto p = static_cast<uint8_t *>((void *)data);
		for (auto n = counter; n--; p += width)
			Z9Serialize<VALUE_T>().deserialize(reader, p, width, size);
		
		auto value = static_cast<variableArray<N, COUNTER_T, VALUE_T> *>((void *)dest);
		value->set(counter, data);
#endif
	}
// end XXX
}
