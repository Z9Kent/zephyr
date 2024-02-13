    
#include <cstdint>
#include <utility>
#include <array>

#include "Z9LockIOProtocol_Current.h"

struct Z9LockIO_Protocol
{
    using MESSAGES = Z9_MESSAGES;

    // register consumers of messages
    static void register_obj(Z9LockIO_base *obj, unsigned n)
    {
        auto& p = messages.at(n);
        if (p)
            printk("%s: %u already registered: %p", __func__, n, p);
        else
            p = obj;
    }

    // XXX maybe two constructors?, then while loop...
    // returns true if more
    bool deserialize(KCB& kcb)
    {
        KernelBuffer_obj buf;
        auto reader = [&kcb]() { return kcb.pop(); }
        return deserialize(reader, buf, buf.size());
    }

    bool deserialize(uint8_t *p, width_t len)
    {
        KernelBuffer_obj buf;
        // reader should respect size -- throw OOR
        auto reader = [&p]() { return *p++; }
        return deserialize(reader, buf, buf.size();)
    }


    
private:
    bool deserialize(reader_t reader, uint8_t *buf, width_t len)
    {
        // deserialize header to get length & discriminator
        LockPacket pkt;
        Z9Serialize_ptr<decltype(pkt)>::value->deserialize((void *)pkt, sizeof(pkt));

        // all transmissions must be begin with a bundle header -- see if any packets
        if (rx_bundle().packets != 0)
        {
            // expecting packet. should it be encrypted
            if (rx_bundle().encrypted != (pkt.discriminator == LockOpaqueContent))
            {
                // discard packet -- throw?? --

            }
        }
        else if (pkt.discriminator != LockBundleHeader::DISCRIMINATOR)
        {
            // discard packet -- throw?? --
            return false;
        }

        // properly sequenced packet -- decode        
        auto format = formats.at(pkt.discriminator);
        format->deserialize(reader, buf, len);

        // exec method, casting type
        invoke<std::make_index_sequence<Z9_MESSAGES::size()>>(p, descriminator);

        return true;
    }

    template <std::size_t N, std::size_t...Is>
    void invoke(void *p, unsigned n)
    {
        if (n = N)
        {
            auto derived = static_cast<at_c<T, n>>(p);
            messages.at(n)(*this, derived);
        }
        else if constexpr (sizeof...(Is))
            do_exec(obj, msg, std::index_sequence<Is...>());
    }

    static inline std::array<Z9LockIO_base *, Z9_MESSAGES::size> messages;
};

// Prototype

template <typename Protocol>
struct Protocol_Base;

template <typename Protocol, typename MSG>
struct Z9LockIO_MSG : virtual Protocol_Base<Protocol>
{

};

template <typename...ImplementedMessages>
struct Z9LockIO_Protocol : Z9LockIO_MSG<Z9LockIO_Protocol, ImplementedMessages>...
                         : virtual Protocol_Base<Z9LockIO_Protocol>
{

};

struct Z9LockIO<LockBundleHeader> : virtual Protocol_Base<Z9LockIO_Protocol>
{
    using T = LockBundleHeader;

    void operator()(Z9LockIO_Protocol *msg, T *p)
    {
        value = *p;
        msg->set_bundleInfo(p->packetCount, p->opaque);
    }

    void send(Z9LockIO_Protocol *msg, uint8_t packetCount = 1, bool opaque = false)
    {
        // XXX could "swap" values, then "swap" back to save allocation of local variable
        T reverse = value;
        std::swap(reverse.origin  , reverse.destination);
        std::swap(reverse.originId, reverse.destinationId);
        reverse.packetCount = packetCount;
        reverse.opaque      = opaque;
        msg->sendBundleHeader(reverse);
    }

private:
    // static so as not to allocate too much memory from stack
    static inline T value;
};

struct Z9LockIO<LockAccessReq>
{
    using T = LockAccessReq;
    
    void operator()(T *p, bool wasEncrypted)
    {
        printk("AccessReq: ID=%0"PRIx32 ", mobile=%"PRIu64 "\n", p->requestId, p->mobileId);

        // evaluate request
        extern bool access_button_state;
        auto errorCode = access_button_state ? 42 : 0;
        
        // generate response
        LockAccessResp rsp { .requestId = p->requestId,
                             .errorCode = errorCode,
                             .granted   = !errorCode };
        send(rsp);
    }
};

struct Z9LockIO<LockPublicKeyExchange>
{
    using T = LockPublicKeyExchange;
    
    void operator()(T *p)
    {
        if (p->publicKeyBytes.size() != 65)
        {
            // fail -- throw
        }

        // XXX need to tell crypto which key we are setting   

        // perform ECDH key derivation
        // send/receive packet format is [length][length bytes]
        printk("received Key Exchange: KeyLen = %d, KeyHdr = %x\n", p->publicKeyBytes.size()
                                                                  , p->publicKeyBytes()[0]);

        auto [cnt, public] = Z9Lock_ECDH(p->publicKeyBytes);
        if (cnt == publicKeyBytes.size())
        {
            p->publicKeyBytes.set(cnt, public);
            send(p);
        }
    }
};

struct Z9LockIO<LockOpaqueContent>
{
    using T = LockOpaqueContent;

    // decrypt in place
    void operator()(T *p)
    {
        auto& key = choose_key();
        
        if (!gcm_decrypt(reader, key, p->iv, p->tag))
        {
            // decrypt fail -- throw?
        }
    }

    void make_opaque()
    {
        T opaque;
        auto& key = choose_key();
        auto length = writer.length();

        gcm_encrypt(writer, key, opaque.iv, opaque.tag);
        send(writer, &opaque); 
    }
}

template <typename Protocol>
struct Protocol_Base
{
    use MESSAGES = Protocol::Messages;

    template <typename T, typename N = meta::index<MESSAGES, N>>
    std::enable_if_t<!std::is_same_v<N, meta::NPOS>>
    virtual operator(T *) { unsupported(N::value); }

    template <typename T, typename N = meta::index<MESSAGES, N>>
    std::enable_if_t<!std::is_same_v<N, meta::NPOS>>
    virtual send(T *msg) { send_packet(N::value, void *msg); }

    virtual void send_packet(size_t n, void *msg)
    {

    }


    meta::invoke<MESSAGES>
};

