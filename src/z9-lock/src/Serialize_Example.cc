
#include <cstdint>
#include <utility>
#include "Z9Serialize.h"
#include "Z9LockIOProtocol_Current.h"


#define MEM(width, name, type) \
    { offsetof(T, name), \
      sizeof(std::declval<T>().name), \
      width, \
      Z9Serialize_ptr<type>::value, \
      #name }


template<>
struct Z9Serialize<LockDateTime_ToSecond> : Z9Serialize_struct
{
    using type = Z9Serialize;
    using T = LockDateTime_ToSecond;
    static constexpr auto NAME = "LockDateTime_ToSecond";

    static constexpr SerializeItem members[] = 
    {
        MEM(2, year, uint16_t),
        MEM(1, month, uint8_t),
        MEM(1, day, uint8_t),
        MEM(1, hour, uint8_t),
        MEM(1, minute, uint8_t),
        MEM(1, second, uint8_t),
    };
    
    static constexpr auto NUM_MEMBERS = std::extent_v<decltype(members)>;

    void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const override
    {
        deserialize_struct(reader, dest, width, NAME, members, NUM_MEMBERS);
    }
};

template <>
struct Z9Serialize<LockBundleHeader> : Z9Serialize_struct
{
    using type = Z9Serialize;
    using T = LockBundleHeader;
    static constexpr auto NAME = "LockBundleHeader";
    
    static constexpr SerializeItem members[] =
    {
        MEM(1, origin, LockIdentificationType),
        MEM(1, intermediary, LockIdentificationType),
        MEM(1, destination, LockIdentificationType),
        MEM(8, originId, uint64_t),
        MEM(8, intermediaryId, uint64_t),
        MEM(8, destinationId, uint64_t),
        MEM(7, expires, LockDateTime_ToSecond),
        MEM(1, opaque, bool),
        MEM(1, packetCount, uint8_t),
    };

    static constexpr auto NUM_MEMBERS = std::extent_v<decltype(members)>;
    
    void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const override
    {
        deserialize_struct(reader, dest, width, NAME, members, NUM_MEMBERS);
    }
};

template <>
struct Z9Serialize<LockPublicKeyExchange> : Z9Serialize_struct
{
    using type = Z9Serialize;
    using T = LockPublicKeyExchange;
    static constexpr auto NAME = "LockPublicKeyExchange";

    static constexpr SerializeItem fixed[] = 
    {
        MEM(66, publicKeyBytes, variableArray<65>),
    };

    static constexpr auto NUM_FIXED = std::extent_v<decltype(fixed)>;
    
    static constexpr SerializeItem variable[] =
    {
    };

    void deserialize(reader_t const& reader, uint8_t *dest, width_t width, width_t size) const override
    {
        deserialize_struct(reader, dest, width, NAME, fixed, NUM_FIXED);
    }
};

#if 0
template <>
struct Z9Serialize<LockIdentificationType> : Z9Serialize_enum
{
    using base_t = Z9Serialize_enum;
    using T = LockIdentificationType;
    static constexpr auto NAME = "LockIdentificationType";

    static const char * const values[] = 
    {
        [0] = "NONE",
        [1] = "LOCK",
        [2] = "HUB_CONTROLLER",
        [3] = "AUTHORITATIVE_SOURCE",
    };

    static constexpr auto NUM_VALUES = std::extent_v<decltype(values)>;
    
    void deserialize(base_t::reader_t reader, uint8_t *dest, base_t::width_t width) const override
    {
        deserialize_enum(reader, dest, width, NAME, values, NUM_VALUES);
    }
};
#endif