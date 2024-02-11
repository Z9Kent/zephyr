#include "ProtocolMetadata.h"
#include "Z9Serialize.h"
#include "Z9LockIOProtocol_Current_MetaData.h"
#include "init_from_list.h"

#pragama once

namespace z9::protocols::z9lockio
{
using namespace meta;
using namespace z9;
using namespace meta::placeholders;
using namespace kas;
using namespace z9::protocol::z9lockio;


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

#if 0
// create type to serialize Z9LockIOProtocols
using Item_t = typename Z9Serialize_struct::SerializeItem;

#if 1
template <typename T, typename NAME, typename MEMBERS>
struct Z9LockIOProtocol_Serialize : Z9Serialize_struct
{
    
    using message_t = T;
    using name      = NAME;
    using members   = init_from_list<Item_t, MEMBERS>;

    void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const override
    {
        deserialize_struct(reader, dest, width, NAME(), members::value, members::size);
    }  
};
#endif

using one = front<Z9_TYPES>;
Item_t item { front<at_c<one, 2>>() };
//Z9LockIOProtocol_Serialize<at_c<one,0>, at_c<one, 1>, at_c<one, 2>> first;
#if 1
constexpr auto members = init_from_list<Item_t, at_c<one, 2>>();
constexpr auto _()
{
    static_assert(members.size == at_c<one, 2>::size());
    return members.data;
}
#endif
#endif

template <typename T, typename = void>
struct has_discriminator : std::false_type {};

template <typename T>
struct has_discriminator<T, std::void_t<int_<T::DISCRIMINATOR>>>
        : std::true_type {};

using DISCRIMINATORS_t = filter<FORMATS_TYPES, quote<has_discriminator>>;


struct Z9_TYPE_CTOR
{
    using type = Z9_TYPE_CTOR;

    template <typename T, typename = void>
    using invoke = Z9Serialize_ptr<T>;
};

using Z_t = transform<Z9_TYPES, quote<Z9Serialize_ptr>>::type;
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
    static_assert(ZZZZ::size == 75);
    //static_assert(INT_TYPES::size() == 4);
    //static_assert(DISCRIMINATORS_t::size() == 46);

    using N = meta::find_index<FORMATS_TYPES, T>;

    //return formatters[N::value];
    //return ZZZZ.data[n];
    //return ZZZZ.data[N::value];
    //return ZZZZ().value[N::value];
    return ZZZZ_value[N::value];
    return {};

}

}