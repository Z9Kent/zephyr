#include "Z9Message.h"

// utility functions to help recast message from base type -> derived type
namespace detail
{
    using namespace meta;

    template <typename OBJ, typename MSG, typename = void>
    struct exec_msg : std::false_type
    {
        void invoke(...) {}
    };

    template <typename OBJ, typename MSG>
    struct exec_msg<OBJ, MSG 
                       , std::void_t<std::invoke_result_t<OBJ, MSG *>>
                       > : std::true_type
    {
        void invoke(OBJ& obj, MessageObject_ABC *msg) const
        { 
            return obj(static_cast<MSG *>(msg));
        }
    };
                    

    template <typename T, std::size_t N, std::size_t...Is>
    void constexpr do_exec(T& obj, MessageObject_ABC *msg, std::index_sequence<N, Is...>)
    {
        if (msg->index() == N)
           exec_msg<T, at_c<ALL_LockMsg, N>>().invoke(obj, msg);
        else if constexpr (sizeof...(Is))
            do_exec(obj, msg, std::index_sequence<Is...>());
    }

    template <typename OBJ, typename MSG, typename...Ts>
    static constexpr uint32_t do_registered(OBJ& obj, list<MSG, Ts...>)
    {
        uint32_t result = exec_msg<OBJ, MSG>::value;
        if constexpr (sizeof...(Ts))
            result |= do_registered(obj, list<Ts...>()) << 1;
        return result;
    }
}

template <typename T, typename NAME>
void LockObjectBase<T, NAME>::exec(MessageObject_ABC *msg)
{
    detail::do_exec(derived(), msg, std::make_index_sequence<NUM_LockMsg>());
}

template <typename T, typename NAME>
uint16_t const LockObjectBase<T, NAME>::registered() const
{
    return detail::do_registered(const_cast<T&>(static_cast<const T&>(derived())), ALL_LockMsg());
}


//
// End base classes
//
LockMsg_IPB ipb;
LockMsg_LATCH latch;

LockObj_Privacy priv;