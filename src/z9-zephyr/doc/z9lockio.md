# Z9 Security z9lockio Smart Lock I/O Protocol Version 0.1, Document Revision 1
![Z9 Security](z9security.png)

_Copyright &copy; 2015-2024 Z9 Security.
Use of this documentation requires both an active non-disclosure agreement, and an active software redistribution agreement, with Z9 Security,
and is subject to the terms of those agreements. Any other use, or disclosure, of this documentation is prohibited._


## Revision History

| Revision | Date        | Description       |
|----------|-------------|-------------------|
| 1        | Oct 19 2023 | Initial revision. |

# Overview

`z9lockio` is an application-level smart lock protocol and data model for communication between an authoriatative source (cloud), a mobile device, and
the secure side of a Z9 Lock.  It is also intended to be able to be used for communication between a Z9 SP-Core controller with a BLE hub, and a Z9 Lock.
Unless noted explicitly, this document describes the protocol as used with a mobile device as the conduit between the authoritative source and the lock, 
as opposed to the use of a Z9 SP-Core controller with a BLE hub.

The protocol is intended to be able to be used over TCP/IP, as well as BLE.  The protocol is intended to be able to be directly serialized/deserialized
via TCP, but assumes that it is being passed through across a lower-level protocol over BLE.  
Specifically, the maximum serialized packet size is around 1K bytes, which is fine for TCP, but is too large for BLE.

The latest version of this document is published at: <https://z9security.jfrog.io/artifactory/gradle-release-local/z9/z9lockio/dev-snapshot/z9lockio-dev-snapshot.md>

# Encoding

The z9lockio protocol is a binary protocol.  All multi-byte numeric values are encoded in network byte order (big-endian)

# Lock Packet Structure

All packets have the structure, with a header and trailer surrounding content-type-specific content.

| Byte Offset | Description                    |
|-------------|--------------------------------|
| 0           | `0x7a`                         |
| 1           | `0x39`                         |
| 2           | bytecount (high byte)          |
| 3           | bytecount (low byte)           |
| 4           | content type ("discriminator") |
| 5..n-5      | content-type-specific bytes    |

The bytecount is the total bytecount of all bytes, including header (starting with `0x7a39`)

This corresponds to the `LockPacket` data structure in code.

# Content

The actual content of the packet, determined by the content type, is documented in the form of Javadoc currently, published here: <https://z9security.jfrog.io/artifactory/gradle-release-local/z9/z9lockprotocol_javadoc/dev-snapshot/z9lockprotocol_javadoc-dev-snapshot.zip>

The actual encoded format can be inferred directly from the Javadoc, using the following simple rules:

| Type      | Encoding                                      |
|-----------|-----------------------------------------------|
| `boolean` | 1 byte, `0x00` for `false`, `0x01` for `true` |
| `byte`    | 1 byte                                        |
| `short`   | 2 bytes, network byte order                   |
| `int`     | 4 bytes, network byte order                   |
| `long`    | 8 bytes, network byte order                   |
| `Enum`    | 1 byte                                        |
| `byte[]`  | literal bytes                                 |

Note that because the source data model is defined using Java data structures, the serialization and deserialization code is mechanically derived from them.
Therefore, there is generally no need for engineers to hand-code the serialization and deserialization of this protocol, as Z9 provides it in all relevant languages.

The full documentation of the enumeration values, data structures, and exact serialization format is published at: <https://z9security.jfrog.io/artifactory/gradle-release-local/z9/z9lockio-data/dev-snapshot/z9lockio-data-dev-snapshot.md>


Not all content types are used for all types of connections.  For example, some content types are needed for TCP/IP only, some content types are
for communication with an SP-Core controller only.  This is primarily due to the real-time communications capability that the lock has when a BLE hub
and SP-Core are present.  Also note that when SP-Core is used, the SP-Core controller is the authoritative source.

Some content types are not sent directly, but are rather encrypted (opaque) and sent as `LockOpaqueContent`.  This is true for NOC payloads, for example.


| Content                       | Content type | Opaque | Direction                                                  |
|-------------------------------|--------------|--------|------------------------------------------------------------|
| `LockIdentification`          | 0            | No     | All                                                        |
| `LockIdentificationResult`    | 1            | No     | All                                                        |
| `LockDbChange_Config`         | 2            | Yes    | Authoritative source to lock                               |
| `LockDbChangeResp`            | 3            | Yes    | Lock to authoritative source                               |
| `LockEvtControl`              | 4            | Yes    | Authoritative source to lock                               |
| `LockEvtBatch`                | 5            | Yes    | Lock to authoritative source                               |
| `LockDevStateRecordControl`   | 6            | Yes    | TBD - intended for Z9 SP-Core controller with BLE hub      |
| `LockDevStateRecord`          | 7            | Yes    | TBD - intended for Z9 SP-Core controller with BLE hub      |
| `LockGetTimeReq`              | 8            | Yes    | Mobile device to lock                                      |
| `LockGetTimeResp`             | 9            | Yes    | Lock to mobile device                                      |
| `LockSetTimeReq`              | 10           | Yes    | Mobile device to lock                                      |
| `LockSetTimeResp`             | 11           | Yes    | Lock to mobile device                                      |
| `LockPushFileChunkReq`        | 12           | TBD    | SP-Core controller to lock                                 |
| `LockPushFileChunkResp`       | 13           | TBD    | Lock to SP-Core controller                                 |
| `LockPullFileChunkReq`        | 14           | TBD    | SP-Core controller to lock                                 |
| `LockPullFileChunkResp`       | 15           | TBD    | Lock to SP-Core controller                                 |
| `LockUpgradeReq`              | 16           | Yes    | SP-Core controller to lock                                 |
| `LockUpgradeResp`             | 17           | Yes    | Lock to SP-Core controller                                 |
| `LockDbQuery`                 | 18           | Yes    | SP-Core controller to lock                                 |
| `LockDbQueryResp_Config`      | 19           | Yes    | Lock to SP-Core controller                                 |
| `LockHostGrantReq`            | 20           | Yes    | Lock to SP-Core controller                                 |
| `LockHostGrantResp`           | 21           | Yes    | SP-Core controller to lock                                 |
| `LockDevActionReq`            | 22           | Yes    | Mobile device to lock, SP-Core controller to lock          |
| `LockDevActionResp`           | 23           | Yes    | Lock to mobile device, lock to SP-Core controller          |
| `LockPolicyAssertionReq`      | 24           | Yes    | SP-Core controller to lock                                 |
| `LockPolicyAssertionResp`     | 25           | Yes    | Lock to SP-Core controller                                 |
| `LockConnectionTermination`   | 26           | No     | Both                                                       |
| `LockDbChange_Hol`            | 27           | Yes    | Authoritative source to lock                               |
| `LockDbChange_Sched`          | 28           | Yes    | Authoritative source to lock                               |
| `LockDbChange_SchedPolicy`    | 29           | Yes    | Authoritative source to lock                               |
| `LockDbChange_Cred`           | 30           | Yes    | Authoritative source to lock                               |
| `LockDbQueryResp_Hol`         | 31           | Yes    | Lock to SP-Core controller                                 |
| `LockDbQueryResp_Sched`       | 32           | Yes    | Lock to SP-Core controller                                 |
| `LockDbQueryResp_SchedPolicy` | 33           | Yes    | Lock to SP-Core controller                                 |
| `LockDbQueryResp_Cred`        | 34           | Yes    | Lock to SP-Core controller                                 |
| `LockCredAuthorization`       | 35           | Yes    | Authoritative source to lock                               |
| `LockAccessReq`               | 37           | Yes    | Mobile device to lock                                      |
| `LockAccessResp`              | 38           | Yes    | Lock to mobile device                                      |
| `LockBundleHeader`            | 40           | Both   | All                                                        |
| `LockPublicKeyExchange`       | 41           | No     | Authoritative source to lock, lock to authoritative source |
| `LockOpaqueContent`           | 42           | N/A    | All                                                        |
| `LockMobileBleChallengeNonce` | 43           | TBD    | Lock to mobile device                                      |

# Encryption

When encryption is used at this layer of the protocol, it is always via `LockOpaqueContent`.  The preceding (unencrypted) `LockBundleHeader` indicates
`opaque`=true.

Note that the lower transport layer (TCP/IP or BLE) may also be encrypted.  Since TCP/IP is only used for testing and development, it is generally not encrypted.
The BLE layer is assumed to be secured in some encrypted fashion, the implementation of which is outside the scope of this document, and in fact
not specified by Z9.

The actual encryption details depend on the source/destination.

Between the authoritative source and the lock (with the mobile device as an intermediary unable to decrypt), the key used is derived by key agreement between
the elliptic curve key pairs of the authoritative source and the lock.

Between the mobile device and the lock, the key used is derived from the shared secret contained in the `LockCredAuthorization`, as well as a BLE challenge nonce that 
is generated for each interaction.

The encryption between the control side of the lock, and the reader side of the lock, is outside the scope of this document, and is covered in the z9io protocol specification.

# Message Flow

Although the LockPacket is the basic unit of data transmission, there is always at least 2 of these together in a "bundle".

The first packet in the bundle always has `LockBundleHeader` as the content, and that indicates how many subsequent packets are in the bundle, as well as
routing information, and whether the rest of the bundle is encrypted or not.

The first bundles exchanged in both directions, when a TCP/IP connection is established, is always unencrypted, and contains `LockIdentification`

The second bundle exchanged in both directions, when a TCP/IP connection is established, is always unencrypted, and contains `LockIdentificationResult`

Note that this exchange is required over TCP/IP, but is redundant over BLE, as the identification information is already exchanged as part of the lower-level
BLE connection establishment (the lock's serial number is present in the advertising packet).
This is why the `LockIdentification` and `LockIdentificationResult` packets are not used over BLE.  Over BLE, the lock determines the mobile device's identity
from the first `LockBundleHeader` sent by the mobile device.

Once both sides have been identified, what happens next depends on whether the lock has been paired with the cloud yet.

If the lock has not been paired with the cloud, then the next bundle sent by the mobile device will be `LockPublicKeyExchange`, originating from the
authoritative source (cloud), which contains the authoritative source's public key.  The lock will respond with `LockPublicKeyExchange`, with its own
public key.

If the lock has been paired with the cloud, then nearly everything will be `LockOpaqueContent`, either from the authoritative source to the lock, or from
the lock to the authoritative source.  This will contain configuration and credentials from the authoritative source to the lock, and events from the lock to the
authoritative source.

Exchanges initiated by the mobile device generally consist of 2 bundles with `LockOpaqueContent`, one
from the authoritative source to the lock, and another from the mobile device to the lock.  The first is a `LockCredAuthorization` encrypted into 
`LockOpaqueContent` by the authoritative source.  
The second is any of the mobile-initiated content types, also encrypted into `LockOpaqueContent`.  This will generally result in a corresponding response from the lock to the mobile device.

For requesting access from a lock, the mobile-initiated content is `LockAccessReq` and the response is `LockAccessResp`.

The mobile device can get/set the time on the lock, in which case the exchanges are `LockGetTimeReq`/`LockGetTimeResp` and `LockSetTimeReq`/`LockSetTimeResp`.

## Commisioning/Pairing Lifecycle

A lock starts out in construction mode.  In construction mode, the lock is not paired with the cloud, and grants access to any credential.

Through an extended button press that is product-specific, the lock can be put into pairing mode.  In pairing mode, the lock will exchange public keys with the cloud (via the mobile device).

Note that pairing mode only lasts a specific amount of time, say, 10 minutes, after which the lock reverts back to construction mode if the pairing process has not completed.

Once public keys have been exchanged, the lock is paired (also known as "customer mode" or "normal mode").

The exchange of NOC data that includes the actual lock configuration only happens after the lock is paired.

Through an extended button press that is product-specific, the lock can be factory reset, which puts it back into construction mode.


### Construction Mode

When a lock is in construction mode, the operation is different in the following ways:

* `LockAccessReq` is sent unencrypted, without a `LockCredAuthorization` bundle preceeding it.  The lock will grant access to any `LockAccessReq` received in construction mode.
* no `LockOpaqueContent` is sent or received
* no audits/events are stored for lock activity such as access granted/denied.

## Error Handling

Within a communications session, if any protocol error occurs, the side detecting the error should terminate the session.  Such errors include:

* Inconsistent ids in bundle header, for example if the lock sends one id in one header, and another id in a subsequent header.
* Sending of unencrypted messages required to be encrypted, or vice versa.








