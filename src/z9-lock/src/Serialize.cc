


#include <cstdint>
#include <cstddef>
#include <utility>


struct packetIO
{
	using reader_t   = uint8_t (*)();
	using writer_t   = void (*)(uint8_t);
	using printer_t  = const char *(*)();
	using width_t  = uint16_t;

	virtual void deserialize(reader_t reader, uint8_t *dest, width_t width)   const = 0;
	virtual void serialize  (writer_t writer, uint8_t const *source, width_t) const {};
	virtual void print      (printer_t print, uint8_t const *source, width_t) const {}		// not ABC yet
	virtual width_t width   () const = 0;
};

template <unsigned N, bool S>
struct packet_int_base : packetIO
{
	width_t width() const override { return N; }

	void deserialize(reader_t reader, uint8_t *dest, width_t width) const override
	{

	// since can only read forward and serialized may not be page aligned,
	// read to temp, then write out LittleEndian (reversed)
	uint8_t temp[N], *p = temp;
	for (unsigned n = N; n--; )
		*p++ = reader();

	// TODO: base code on std::endian<> results
	for (unsigned n = N; n--; )
		*dest++ = *--p;
	
	if constexpr (S)
	{
		uint8_t extend = *p & 0x80 ? ~0 : 0;
		for (unsigned n = N; n++ < width; )
			*dest++ = extend;
	}
	else for (unsigned n = N; n++ < width; )
		*dest++ = 0;
		
	}
	void serialize(writer_t writer, uint8_t const *source, width_t width) const override
	{
	// TODO: base code on std::endian<> results
	// serialize data into temp buffer, sign extending as required
	uint8_t temp[width], *p = &temp[width];

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
};

template <typename T>
using packet_int = packet_int_base<sizeof(T), std::is_signed_v<T>>;

template <typename T>
struct packet_enum_base : packet_int<std::underlying_type_t<typename T::enum_t>>
{
	// just the `print` support. 

};

template <typename T, typename NAMES>
struct packet_enum : packet_enum_base<packet_enum<T, NAMES>>
{
	using enum_t = T;
	using base_t = packet_enum_base<packet_enum<T>>;

	static constexpr const char *names[] = instantiate_list<NAMES>();
	
	static constexpr auto NUM_names = std::extent_v<decltype(names)>;	
};

template <typename T>
struct packet_struct_base : packetIO
{
	using items_t = typename T::items;

	void deserialize(reader_t reader, uint8_t *dest, width_t width) const override
	{
		for (auto& item : items_t())
			item.serialize->deserialize(reader, dest + item.offset, item.width);
	}
};


template <typename T, typename MEMBERS, typename DATA = meta::list<>>
struct packet_struct : packet_struct_base<packet_struct<T, MEMBERS, DATA>>
{
	using base_t = packet_struct_base<packet_struct<T, MEMBERS, DATA>>;


}



/**
 * Enum: {@link LockIdentificationType.h}.
 */
enum LockIdentificationType
{
	LockIdentificationType_NONE,
	LockIdentificationType_LOCK,
	LockIdentificationType_HUB_CONTROLLER,
	LockIdentificationType_MOBILE,
	LockIdentificationType_AUTHORITATIVE_SOURCE,
};

/**
 * Main structure for module: {@link LockBundleHeader.h}.
 */
struct LockBundleHeader
{
	//struct LockPacketContent base;
	enum LockIdentificationType origin;
	enum LockIdentificationType intermediary;
	enum LockIdentificationType destination;
	uint64_t originId;
	uint64_t intermediaryId;
	uint64_t destinationId;
	//struct LockDateTime_ToSecond expires;
	//bool opaque:1;
	//int8_t packetCount:3;
};

struct Z9Serialize
{
    
};


// read integer in network order
template <unsigned N, bool S = false>
void read_int(uint8_t (*reader)(), uint8_t *p, unsigned width)
{
	// XXX needs to be readble
	constexpr size_t read_size = N;

	// since can only read forward and serialized may not be page aligned,
	// read to temp, then write out LittleEndian (reversed)
	uint8_t temp[N], *q = temp;
	for (unsigned n = N; n--; )
		*q++ = reader();

	// TODO: base code on std::endian<> results
	for (unsigned n = N; n--; )
		*p++ = *--q;
	
	if constexpr (S)
	{
		uint8_t extend = *q & 0x80 ? ~0 : 0;
		for (unsigned n = N; n++ < width; )
			*p++ = extend;
	}
	else for (unsigned n = N; n++ < width; )
		*p++ = 0;
}
#if 0
void read_struct(uint8_t (*fn)(), uint8_t *p, unsigned width)
{
	for (auto const& item : items)
		item.serialize(p + item.offset, item.width)
}


void process_packet(KCB *kcb)
{
	KCB_temp buf;		// deletes on out-of-context
	auto discriminator = kcb.pop();
	auto pkt = Serialize<Z9LockIO_Protocol>(kcb, buf);

	switch (discriminator)
	{
		case LockBundleHeader_DISCRIMINATOR:
		{
			auto& o = pkt.read<LockBundleHeader_DISCRIMINATOR>();
			// process base values

			for (auto& suffix : pkt.suffix<LockBundleHeader_DISCRIMINATOR>(o.max))
			{
				// process suffix values
			}
			break;
		}
	} 
}
#endif
