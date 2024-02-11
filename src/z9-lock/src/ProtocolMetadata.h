
#include <meta/meta.hpp>
#include "kas_string.h"
#include "init_from_list.h"


#pragma once

#define Z9_STRING KAS_STRING

namespace z9{}
namespace z9::protocol
{
   using namespace meta;

// macro to hold structure member metadata
#define Z9_MEMBER(s_type, wire_size, name, ...) \
       list<int_<wire_size>                        \
          , int_<offsetof(s_type, name)>           \
          , int_<sizeof(std::declval<s_type>().name)> \
          , decltype(std::declval<s_type>().name)  \
          , Z9_STRING(#name)>

#define Z9_MEMBER_NONE() \
 list<int_<0>, int_<0>, int_<0>, uint8_t, Z9_STRING("*none*")>

// expand to arrays:
// constexpr auto names[] = {
//      [NAME ## _ ## _VALUE] = #NAME,
//      ... for each VALUE ...
//  };

#define Z9_ENUM(NAME, VALUES...)  list<NAME, Z9_STRING(#NAME), Z9_STRING(#VALUES),...>
}
