# Eros Protocol Definition

The Eros protocol is a new version/extension of the MyPass (formely Leaf for Mobile) protocol
allowing for a zero-knowledge secure channel to be established between two devices.

The Eros protocol uses the PKI based ECIES system to encrypt data between two devices. The standard
components for the ECIES implementation are:

| Component                   | Choice/Details                                                    |
| --------------------------- | ----------------------------------------------------------------- |
| ECC Curve                   | NIST P-256 (secp256r1)                                            |
| Diffie Hellman Scheme       | ECDH                                                              |
| KDF                         | HKDF using SHA-256                                                |
| Symmetric Encryption Scheme | AES128-GCM                                                        |
| MAC Scheme                  | MAC is accomplished using AES128 in GCM mode for data encryption. |

## Terminology

### Entities/Devices

In the subsequent sections, several terms are used for the entities on each side of a given
transaction:

* The **Central Device** or **A** is represented by the entity initiating the transaction and
  issuing commands, such as a mobile phone in the case of a BLE based connection.
* The **Peripheral Device** or **B** is represented by the entity responding to commands
  issued by the Central Device, such as an offline lock or access reader in the case of a
  BLE based connection.

### Nonces

The word **nonce** is used to describe a random sequence of bytes an entity will generate,
which should only be used for the life of a single transaction.

### Cryptography

| Term    | Meaning                                     |
|---------|---------------------------------------------|
| `ECC`   | Elliptic Curve Cryptography                 |
| `ECDH`  | Elliptic Curve Diffie Hellman               |
| `ECIES` | Elliptic Curve Integrated Encryption Scheme |
| `KDF`   | Key Derivation Function                     |
| `HKDF`  | HMAC based Key Derivation Function          |
| `MAC`   | Message Authentication Code                 |
| `IV`    | Initialization Vector                       |

## Protocol Steps

The Eros protocol follows the high level scheme below:

* Device A below shall simply be referred to as **A**.
* Device B below shall simply be referred to as **B**.

0. Both **A** and **B** have public IDs `idA` and `idB`.
1. **A** generates ECC KeyPair (`pubA`, `privA`), `nonceA`, and transmits `idA`|`pubA`|`nonceA` to **B**.
   *This is referred to as the ECIES Challenge Request message*.
2. **B** generates ECC KeyPair (`pubB`, `privB`), `nonceB`.
3. **B** derives shared secret `ss` using ECDH(pub=`pubA`, priv=`privB`).
4. **B** derives session key and starting IV `sKey`|`IV` using HKDF(ikm=`ss`, salt=`nonceA`|`nonceB`, info=`idA`|`idB`).
5. **B** responds to **A** with `idB`|`pubB`|`nonceB`.
   *This is referred to as the ECIES Challenge Response message*.
6. **A** derives shared secret `ss` using ECDH(pub=`pubB`, priv=`privA`).
7. **A** derives session key and starting IV `sKey`|`sIV` using HKDF(ikm=`ss`, salt=`nonceA`|`nonceB`, info=`idA`|`idB`).
8. **A** freely transmits data using AES128-GCM(iv=`sIV`, key=`sKey`)
9. **B** uses the last block `lIV` from the message sent by **A** and freely responds with data using AES128-GCM(iv=`lIV`, key=`sKey`)
10. Subsequent messages sent between **A** and **B** use the last block of the previous message for the **IV**.

## Packet Structure

Each packet is generally structured as the following:

```
/*
 * Leaf BLE messaging protocol structure.
 */
typedef struct _leaf_ble_msg_t
{
    unsigned char  start;      // start sequence byte 0x82 or 0xC2
    leaf_tag_t     tag;        // msg tag
    unsigned short length;     // 2 byte msg length, serialized big endian

    // these fields are included in the length and encrypted for cipher msgs
    unsigned char  sequence;                     // 1 byte rotating sequence
    unsigned char  value[400]; // msg payload
} leaf_ble_msg_t;
```

| Field    | Length | Description                                                |
| -------- | ------ | ---------------------------------------------------------- |
| start    | 1      | Start sequence byte: `0x82` plaintext `0xC2` for ciphered. |
| tag      | 1      | Message tag.                                               |
| length   | 2      | Big endian message length. Covers all subsequent fields.   |
| sequence | 1      | Rotating sequence byte. Encrypted in cipher messages.      |
| value    | 0-400  | Message data.                                              |

## Message Types

| Message                  | Tag    | Encrypted   | Description                                                                                     |
| ------------------------ | ------ | ----------- | ----------------------------------------------------------------------------------------------- |
| Ack/Nak response         | `0x00` | No          | Generic response message to acknowledge or return error codes.                                  |
| ECIES challenge request  | `0x09` | No          | ECIES challenge request data. Sent at the beginning of a transaction.                           |
| ECIES challenge response | `0x0A` | No          | Response to ECIES challenge request. Contains data to complete establishment of secure channel. |
| Passthrough data.        | `0x0B` | Conditional | Opaque data payload which is not expected to be processed by this library.                      |

### Ack/Nak

This message type is used to convey errors or success statuses when no further data
can or should be sent.

| Field  | Length | Description              |
|--------|--------|--------------------------|
| Status | 1      | Single byte status code. |

#### Statuses

| Status | Meaning                                                                                                       |
|--------|---------------------------------------------------------------------------------------------------------------|
| `0x00` | Success/Continue. Used to "ACK" a data packet when no data needs to be sent by one entity.                    |
| `0x01` | Generic Error. Transaction must be aborted.                                                                   |
| `0x02` | Auth/Encryption mismatch. There was an error in the secure channel. Transaction must be aborted or restarted. |

### ECIES Challenge Request

The ECIES challenge request is issued by the Central device at the very beginning of a transaction.

| Field              | Length | Description                                  |
|--------------------|--------|----------------------------------------------|
| Central ID         | 8      | The public ID of the Central.                |
| Central Public Key | 65     | The Ephemeral ECC public key of the Central. |
| Central Nonce      | 16     | One time use nonce generated by the Central. |

### ECIES Challenge Response

The ECIES challenge response is sent by the Peripheral device immediately following a
*ECIES Challenge Request*.

| Field                 | Length | Description                                  |
|-----------------------|--------|----------------------------------------------|
| Peripheral ID         | 8      | The public ID of the Central.                |
| Peripheral Public Key | 65     | The Ephemeral ECC public key of the Central. |
| Peripheral Nonce      | 16     | One time use nonce generated by the Central. |

### Passthrough Data

Passthrough data contains additional information inside of the `value` field of the outer packet structure.
This ensures that message metadata is not leaked outside of the secure session.

```
/*
 * Passthrough message type structure.
 */
typedef struct _passthrough_value_t
{
    unsigned char target;   // entity the payload is targeted for
    unsigned char index;    // fragment index
    unsigned char total;    // total number of fragments in communication
    unsigned short length;  // big endian fragment length
    unsigned char data[395] // fragment data
} passthrough_value_t;
```

| Field           | Length | Description                                               |
|-----------------|--------|-----------------------------------------------------------|
| Message target  | 1      | ID target for packet.                                     |
| Fragment index  | 1      | 0 indexed fragment number.                                |
| Total fragments | 1      | Total number of message fragments for passthrough writes. |
| Fragment bytes  | 2      | Big endian fragment length.                               |
| Fragment Data   | 1-N    | Data for fragment.                                        |

#### Target IDs

The target ID is meant to internally route packets meant for specific modules in a distributed
processing system. The target ID applies to both command packets and response packets.

The range `0-128` is reserved for command packet routing. The range `129-255` is reserved for
reply packet routing.

```
typedef enum _target_id_t
{
    target_module = 0,
    target_host,
    target_client = 129,
    target_service
} target_id_t;
```

| ID  | Target                                                                                                                 |
|-----|------------------------------------------------------------------------------------------------------------------------|
| 0   | This module. The packet should be routed to the current module for upgrades/local processing.                          |
| 1   | Host. A connected host device. Could be a controller or a control module.                                              |
| 129 | Client. This target would be used if the connected mobile device client needs to process the reply.                    |
| 130 | Service/Server. This target would be used if the reply should be sent to a server/service, typically a cloud platform. |
