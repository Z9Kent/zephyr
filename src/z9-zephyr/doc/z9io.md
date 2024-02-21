# Z9 Security z9io Sub-Controller/Reader I/O Protocol Version 2.0, Document Revision 14
![Z9 Security](z9security.png)

_Copyright &copy; 2015-2024 Z9 Security.
Use of this documentation requires both an active non-disclosure agreement, and an active software redistribution agreement, with Z9 Security,
and is subject to the terms of those agreements. Any other use, or disclosure, of this documentation is prohibited._


## Revision History

| Revision | Date         | Description                                                                                                                               |
|----------|--------------|-------------------------------------------------------------------------------------------------------------------------------------------|
| 14       | Apr 21 2023  | CRC16 (protocol version 2.0)                                                                                                              |
| 13       | Apr 14 2023  | Add encryption (protocol version 2.0)                                                                                                     |
| 12       | Apr 14 2023  | Add `FileAvailable` and `ProcessFile` (protocol version 2.0)                                                                              |
| 11       | Mar 20 2023  | Add `HostInfo` and `HostStatus` (protocol version 2.0)                                                                                    |
| 10       | Feb 14 2023  | Add `ProtocolPassthru` (protocol version 2.0)                                                                                             |
| 9        | Dec 14, 2022 | Migrate to Markdown format                                                                                                                |
| 8        | Feb 11, 2020 | Add `multidrop` byte to `Hello` packet.  Document multidrop.  Document `AnalogInConfig`.  Protocol version 1.0.                           |
| 7        | Feb 1, 2020  | Replace 2-byte sequence number in header with 1-byte address and 1-byte sequence number, for multidrop.  Protocol version updated to 1.0. |
| 6        | Nov 10, 2017 | Add `ReaderStatus`                                                                                                                        |
| 5        | Nov 2 2017   | Document `AnalogRead`, `BioRead`                                                                                                          |
| 4        | Nov 6 2015   | Added `credUnid` to `BioVerified` and `ReaderState`.  Protocol version updated to 0.9                                                     |

# Overview

The Z9 Sub-Controller I/O Protocol (Z9IO) is a simple, compact protocol used to communicate between an intelligent access
control panel (access control panel which makes access control decisions) and a sub-controller (a device which only performs I/O to 
relays, inputs, Wiegand card readers, etc). In a smart lock, e.g. the Z9 Lock, it can be used between the "controller board" side
of the lock, and the "reader board" side of the lock.  In this case, the "controller board" side performs the role of the
intelligent access control panel.

The protocol can be used either over serial (RS-232, RS-485, etc) or over TCP/IP.

I/O that is on-board the physical intelligent controller is generally implemented using a process which supports this protocol
over TCP/IP on a local socket, to the panel firmware process (`z9.spcore`).

The current version of this protocol is 2.0.  This is reflected in the `Hello` and `BoardInfo` messages as described below.

The latest version of this document is published at: <https://z9security.jfrog.io/artifactory/gradle-release-local/z9/z9io/dev-snapshot/z9io-dev-snapshot.md>

Note that backwards-compatibility is not generally retained between major version changes (say, between 0.9 and 1.0, or 1.0 and 2.0).

# TCP/IP

When using TCP/IP, the sub-controller listens on a socket, and the intelligent controller is the client.  The default 
port the sub-controller should listen on is 5559.

# Encoding

The Z9IO protocol is a binary protocol.  All multi-byte numeric values are encoded in network byte order (big-endian)

# Packet Structure

All packets have the structure, with a header and trailer surrounding content-type-specific content.

| Byte Offset | Description                                    |
|-------------|------------------------------------------------|
| 0           | `0x7f`                                         |
| 1           | bytecount (high byte)                          |
| 2           | bytecount (low byte)                           |
| 3           | address (always 0 unless multidrop is enabled) |
| 4           | sequence number                                |
| 5           | content type ("discriminator")                 |
| 6..n        | content-type-specific bytes                    |
| n+1         | CRC16 (high byte)                              |
| n+2         | CRC16 (low byte)                               |

The bytecount is the total bytecount of all bytes, including header (starting with `0x7f`) and trailer (CRC16).

The address is always the address of the sub-controller, regardless of whether the message is to or from the sub-controller.  
If multidrop is not enabled, the address is always 0.

From the host to the sub-controller: The sequence number starts at 0 and increments for each packet.  A repetition of the same sequence number indicates retransmission of a packet.
A gap in sequence numbers must be considered a communications error.

From the sub-controller to the host, in non-multidrop mode: The sequence number starts at 0 and increments for each packet.  A repetition of the same sequence number indicates retransmission of a packet.
A gap in sequence numbers must be considered a communications error.  In this case The sequence number is numbered independently on each side, starting at 0 and incrementing.

From the sub-controller to the host, in multidrop mode: the sequence number must always match the poll it is in response to.

Content types are described in a section below.

The CRC16 algorithm is defined in Appendix A.

# Packet Content

Content types for byte 5 of a packet (from intelligent controller to sub-controller):

| Value (Decimal) | Content Type                       | Description                                                                                                   |
|-----------------|------------------------------------|---------------------------------------------------------------------------------------------------------------|
| 2               | `RawWrite`                         | Wiegand output                                                                                                |
| 3               | `DigitalWrite`                     | Relay or other output                                                                                         |
| 6               | `SerialWrite`                      | Serial port output                                                                                            |
| 8               | `Hello`                            | First message to establish connection                                                                         |
| 10              | `Config`                           | Finalize configuration                                                                                        |
| 11              | `FileQuery`                        | Query file data                                                                                               |
| 13              | `BoardStatusQuery`                 | Query board status                                                                                            |
| 15              | `Ping`                             | Check to see that sub-controller is still responding                                                          |
| 17              | `AnalogInConfig`                   | Analog input configuration                                                                                    |
| 18              | `DigitalInConfig`                  | Digital input configuration                                                                                   |
| 20              | `DisplayWrite`                     | Write to a text display (e.g. LCD display)                                                                    |
| 26              | `ReaderState`                      | Set the state of an intelligent card reader                                                                   |
| 30              | `ProtocolPassthru`                 | Passthru of another protocol (e.g. z9lockio)                                                                  |
| 31              | `HostInfo`                         | Additional host information beyond `Hello`, used by the control board side of a Z9 Lock, to the reader board. |
| 32              | `HostStatus`                       | Dynamic host status to be sent by the control board side of a Z9 Lock, to the reader board.                   |
| 35              | `EncryptedContent`                 | Encrypted packet content (AES-128)                                                                            |
| 36              | `EncryptionKeyExchange`            | Negotiation of link-level key to use for encrypted communications.                                            |
| 37              | `ApplicationEncryptionKeyExchange` | Negotiation of application-level keys.                                                                        |

Content types for byte 5 of a packet (from sub-controller to intelligent controller):

| Value (Decimal) | Content Type                       | Description                                                                                                                                                                            |
|-----------------|------------------------------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1               | `RawRead`                          | A wiegand card read                                                                                                                                                                    |
| 4               | `DigitalRead`                      | Initial, or change, in digital input value                                                                                                                                             |
| 5               | `TemperatureRead`                  | A temperature sensor read                                                                                                                                                              |
| 7               | `BoardInfo`                        | Board information, in response to `Hello`                                                                                                                                              |
| 9               | `AnalogRead`                       | Initial, or change, in analog input value                                                                                                                                              |
| 12              | `FileContents`                     | File contents, sent in response to `FileQuery`                                                                                                                                         |
| 14              | `BoardStatus`                      | Board status, in response to `BoardStatusQuery`                                                                                                                                        |
| 16              | `Pong`                             | In response to `Ping`                                                                                                                                                                  |
| 19              | `RawKey`                           | A key press on a keypad                                                                                                                                                                |
| 22              | `Nak`                              | Negative acknowledgement (rejection) of a message                                                                                                                                      |
| 21              | `Ack`                              | Acknowledgement of a message                                                                                                                                                           |
| 23              | `BioVerified`                      | Biometric has been verified                                                                                                                                                            |
| 24              | `RawKeys`                          | Raw keypad keys (multiple)                                                                                                                                                             |
| 25              | `UserIdRead`                       | User ID read.  Generally due to entering user ID on keypad.                                                                                                                            |
| 27              | `BioRead`                          | A biometric read                                                                                                                                                                       |
| 28              | `ReaderStatus`                     | Comm, tamper, power status of a card reader                                                                                                                                            |
| 30              | `ProtocolPassthru`                 | Passthru of another protocol (e.g. z9lockio)                                                                                                                                           |
| 33              | `FileAvailable`                    | Indicates that a file is available.  Generally for software (firmware) update files.  If the recipient is interested, they might then send `FileQuery`.                                |
| 34              | `ProcessFile`                      | Indicates that a file is to be processed.  Generally for software (firmware) update files, in which case "processing" it means applying the software update, and generally restarting. |
| 35              | `EncryptedContent`                 | Encrypted packet content (AES-128)                                                                                                                                                     |
| 36              | `EncryptionKeyExchange`            | Negotiation of link-level key to use for encrypted communications.                                                                                                                     |
| 37              | `ApplicationEncryptionKeyExchange` | Negotiation of application-level keys.                                                                                                                                                 |

# Message Flow

The Z9IO protocol allows either side to send a packet at any time.  However, the following rules apply:

* If multidrop is not enabled, each side numbers its sequence numbers independently, starting with 0 and incrementing with each message.  That is, there is no
correlation between the sequence numbers sent by the intelligent controller with those sent by the sub-controller.
* If multidrop is enabled, the intelligent controller numbers its sequence numbers starting with 0 and incrementing with each message.  This include
`Poll` messages.  In this mode, all sub-controller packets are sent in response to a `Poll`, and the sequence number of the response must match the `Poll`.
* If either side receives a packet with a sequence number that is not the previous packet received's sequence number +1, then it must
be considered a communication error, and the connection closed and re-established.  In the case of multidrop, this only applies to the messages from the
intelligent controller to the sub-controller.
* The sub-controller must send an `Ack` in direct response to every message from the intelligent controller, except in multidrop mode, where the
sub-controller may send another available message if it has one, in place of an `Ack`.
* The `Ack`, or other response, must be sent within 2 seconds of the message to which it is responding.  The only exception to this is the response to the
`Hello` packet, which must be sent within 8 seconds.
* In addition to the `Ack`, the sub-controller has an obligation to send a secondary response, depending on the content type.  In multidrop mode, the secondary
response must be in response to a subsequent `Poll`.
* In the event of an error, the sub-controller may send a `Nak` in place of an `Ack`.
* In the event of no response or a `Nak` from the sub-controller, the intelligent controller may resend its packet with the same sequence number
* If the sub-controller has a packet to send with an input change, such as `DigitalRead`, `RawRead`, is simply sends it.  The intelligent
controller must never send an `Ack` or `Nak`.

The messages from the intelligent controller which require a secondary response, are as follows:

| Content Type                       | Secondary Response Content Type    |
|------------------------------------|------------------------------------|
| `Hello`                            | `BoardInfo`                        |
| `FileQuery`                        | `FileContents`                     |
| `BoardStatusQuery`                 | `BoardStatus`                      |
| `Ping`                             | `Pong`                             |
| `EncryptionKeyExchange`            | `EncryptionKeyExchange`            |
| `ApplicationEncryptionKeyExchange` | `ApplicationEncryptionKeyExchange` |

## Typical Message Flow

The initial flow of messages upon connection is generally as follows:

| Intelligent Controller        | Sub-Controller Response, Secondary Response                                          |
|-------------------------------|--------------------------------------------------------------------------------------|
| `Hello`                       | `Ack`,`BoardInfo`                                                                    |
| `Poll`                        | `Ack` or any other single message.  Note that `Poll` is only used in multidrop mode. |
| `Ping`                        | `Ack`,`Pong`                                                                         |
| `BoardStatusQuery`            | `Ack`,`BoardStatus`                                                                  |
| `DigitalInConfig` (0 or more) | `Ack` (1 for each)                                                                   |
| `AnalogInConfig` (0 or more)  | `Ack` (1 for each)                                                                   |
| `Config`                      | `Ack`                                                                                |

When idle, and multidrop is not enabled, the message flow just consists of `Ping`/`Pong`:

| Intelligent Controller | Sub-Controller Response, Secondary Response |
|------------------------|---------------------------------------------|
| `Ping`                 | `Ack`,`Pong`                                |
| `Ping`                 | `Ack`,`Pong`                                |
| ...                    | ...                                         |

When multidrop is enabled, the message flow also contains `Poll`.  The sub-controller only sends
messages in response to a `Poll` in this case, or `Ack` if there is no message.

When multidrop is not enabled, then for inputs at the sub-controller, it simply sends a message without waiting for the intelligent controller
to send anything:

When the sub-controller receives a Wiegand card read (or a Wiegand key press):

| Intelligent Controller | Sub-Controller Packet |
|------------------------|-----------------------|
|                        | `RawRead`             |

When the sub-controller receives a single key press such that the sub-controller knows how to process the raw bits of the key press into a key code:

| Intelligent Controller | Sub-Controller Packet |
|------------------------|-----------------------|
|                        | `RawKey`              |

When the sub-controller receives multiple key presses such that the sub-controller knows how to process the raw bits of the key press into a key code:

| Intelligent Controller | Sub-Controller Packet |
|------------------------|-----------------------|
|                        | `RawKeys`             |

When the sub-controller has been presented with a biometric and has verified (or failed to verify) the biometric:

| Intelligent Controller | Sub-Controller Packet |
|------------------------|-----------------------|
|                        | `BioVerified`         |

When the sub-controller has been presented with a user ID (generally entered on the keypad):

| Intelligent Controller | Sub-Controller Packet |
|------------------------|-----------------------|
|                        | `UserIdRead`          |

When the sub-controller detects a change in a digital input:

| Intelligent Controller | Sub-Controller Packet |
|------------------------|-----------------------|
|                        | `DigitalRead`         |

When the sub-controller detects a change in an analog input:

| Intelligent Controller | Sub-Controller Packet |
|------------------------|-----------------------|
|                        | `AnalogRead`          |

When the intelligent controller wants to change a digital output:

| Intelligent Controller | Sub-Controller Packet |
|------------------------|-----------------------|
| `DigitalWrite`         | `Ack`                 |

# Encryption

When encryption is in use, the encryption is AES-128-GCM.  The key is negotiated as described below.

For encrypted bytes, the first 12 bytes of the data will be the IV used to encrypt the message.  This will be randomly generated for each message.

The encrypted bytes follow, followed by the 16-byte GCM tag.

Note that the header and trailer are not encrypted.  Only the packet content is, and the resulting serialized
packet content is then encrypted, and encoded using the `EncryptedContent` packet content.

When being encrypted into `EncryptedContent`, the packet content to be encrypted specifically includes:

* 1-byte content type
* content-type-specific bytes

It specifically excludes:
* `0x7f` start byte
* bytecount (high byte)
* bytecount (low byte)
* address (always 0 unless multidrop is enabled)
* sequence number
* CRC16 (high byte)
* CRC16 (low byte)


Even when encryption is in use, not all packet contents are encrypted.

The following packet contents are **always** encrypted, if encryption is enabled.  Furthermore, if
encryption is possible, they are never sent before the encryption key for the link has been established:

* `RawRead`
* `RawWrite`
* `DigitalWrite`
* `SerialWrite`
* `Config`
* `FileQuery`
* `AnalogInConfig`
* `DigitalInConfig`
* `DisplayWrite`
* `ProtocolPassthru`
* `HostInfo`
* `HostStatus`
* `ApplicationEncryptionKeyExchange`
* `RawKey`
* `RawKeys`
* `BioVerified`
* `UserIdRead`
* `BioRead`
* `DigitalRead`
* `AnalogRead`
* `TemperatureRead`
* `ReaderStatus`
* `FileAvailable`
* `ProcessFile`

In particular, the following packet contents are to be unencrypted, even when encryption is enabled:

* `Hello`
* `BoardStatusQuery`
* `BoardStatus`
* `BoardInfo`
* `Poll`
* `Ack`
* `Nak`
* `Ping`
* `Pong`
* `EncryptionKeyExchange`
* `FileContents`, assuming the file is an encrypted and signed firmware update file.

`Hello` and `BoardInfo` tell each side whether encryption is enabled (with key negotiation complete).

When both side report encryption is enabled, both sides can and must begin encrypting messages.

If encryption is not enabled on either or both sides, then the intelligent controller can request it by sending
`EncryptionKeyExchange`.

## Encryption Key Negotiation

At "linking" time, the upstream and downstream devices determine a shared, random seed as follows:

* Upstream device sends `EncryptionKeyExchange` with type 0 and 16 random bytes.  This is the upstream linking seed.
* The downstream device responds with `EncryptionKeyExchange` with type 1 and 16 random bytes.  This is the downstream linking seed.
* The shared random seed is the bitwise XOR of the upstream and downstream linking seeds.  Both sides store this.

To determine the actual session key:
* Upstream device sends `EncryptionKeyExchange` with type 2 and 16 random bytes.  This is the upstream session seed.
* The downstream device responds with `EncryptionKeyExchange` with type 3 and 16 random bytes.  This is the downstream session seed.
* The encryption key is the bitwise XOR of the shared random seed, the upstream session seed, and the downstream session seed.

# Specific Packet Contents

## `Hello`

| Byte Offset | Description                                                                                                                        |
|-------------|------------------------------------------------------------------------------------------------------------------------------------|
| 0           | Protocol version (major) - as a binary number                                                                                      |
| 1           | Protocol version (minor) - as a binary number                                                                                      |
| 2           | Multidrop enabled: 0 (false) or 1 (true)                                                                                           |
| 3           | Encryption enabled (the key has been negotiated): 0 (false) or 1 (true).  Note that `Hello` messages themselves are not encrypted. |

Note that the current protocol version is the 2-component number (major.minor) 2.0.

## `Ack`

| Byte Offset | Description                                  |
|-------------|----------------------------------------------|
| 0           | Spare (unused)                               |
| 1           | Sequence number of packet being acknowledged |

## `Nak`

| Byte Offset | Description                                             |
|-------------|---------------------------------------------------------|
| 0           | Spare (unused)                                          |
| 1           | Sequence number of packet being negatively acknowledged |
| 2           | Reason code for nak (rejection)                         |

The reason code is sub-controller implementation-specific.  There are no predefined reason codes.

## `BoardInfo`

| Byte Offset | Description                                                                                                                            |
|-------------|----------------------------------------------------------------------------------------------------------------------------------------|
| 0           | Protocol version (major) - as a binary number                                                                                          |
| 1           | Protocol version (minor) - as a binary number                                                                                          |
| 2           | Model number (high byte)                                                                                                               |
| 3           | Model number (low byte)                                                                                                                |
| 4           | Firmware version (major) - as a binary number                                                                                          |
| 5           | Firmware version (minor) - as a binary number                                                                                          |
| 6           | Encryption enabled (the key has been negotiated): 0 (false) or 1 (true).  Note that `BoardInfo` messages themselves are not encrypted. |
| 7..14       | 8-byte serial number of the sender, used for key diversification if encryption is enabled.                                             |
| 15..23      | reserved (set to 0)                                                                                                                    |
| 24          | Digital input(s) enabled/available: 0 (false) or 1 (true)                                                                              |
| 25          | Digital output(s) enabled/available: 0 (false) or 1 (true)                                                                             |
| 26          | Analog input(s) enabled/available: 0 (false) or 1 (true)                                                                               |
| 27          | Wiegand input(s) enabled/available: 0 (false) or 1 (true)                                                                              |
| 28..32      | Reserved (set to 0)                                                                                                                    |

Note that the current protocol version is the 2-component number (major.minor) 2.0.

The model number is a unique number assigned by Z9 Security for each type of sub-controller (physical or firmware process).
If this number has not been assigned for a specific implementation, use the number 0.

Firmware version is a 2-component number determined by the sub-controller implementation, reflecting its version (major.minor, e.g. 1.0).

## `Poll`

This content type has empty content (0 bytes).

This message is only used if multidrop is enabled (see `Hello` content definition).

## `Ping`

This content type has empty content (0 bytes).

## `Pong`

This content type has empty content (0 bytes).

## `BoardStatusQuery`

This content type has empty content (0 bytes).

## `BoardStatus`

Note: all fields in this type are optional and may be set to 0.

| Byte Offset | Description                                                        |
|-------------|--------------------------------------------------------------------|
| 0..3        | Milliseconds since startup                                         |
| 4..5        | Available memory in bytes                                          |
| 6           | `Hello` received (0 for false, 1 for true)                         |
| 7           | Protocol connection type - 0 for none, 1 for serial, 2 for network |
| 8..11       | Number of packets read (via serial)                                |
| 12..15      | Number of packets written (via serial)                             |
| 16..19      | Number of packets read (via network)                               |
| 20..23      | Number of packets written (via network)                            |
| 24..27      | Number of protocol errors reading packets (via serial)             |
| 28..29      | Last protocol error number reading packets (via serial)            |
| 30..33      | Number of protocol errors writing packets (via serial)             |
| 34..35      | Last protocol error number writing packets (via serial)            |
| 36..39      | Number of protocol errors reading packets (via network)            |
| 40..41      | Last protocol error number reading packets (via network)           |
| 42..45      | Number of protocol errors writing packets (via network)            |
| 46..49      | Last protocol error number writing packets (via network)           |
| 50..53      | Reserved (set to 0)                                                |

## `DigitalInConfig`

Note that this configures a single digital input, so one of these is sent for each possible input.

| Byte Offset | Description                                                                                                                    |
|-------------|--------------------------------------------------------------------------------------------------------------------------------|
| 0           | Input index (starting at 0)                                                                                                    |
| 1           | Enabled (0 for false, 1 for true)                                                                                              |
| 2           | Invert (0 for false, 1 for true).  If inverted, active is the opposite of value in `DigitalRead`, otherwise they are the same. |
| 3..6        | Reserved (set to 0)                                                                                                            |

## `AnalogInConfig`

Note that this configures a single analog input, so one of these is sent for each possible input.

| Byte Offset | Description                                                                                      |
|-------------|--------------------------------------------------------------------------------------------------|
| 0           | Input index (starting at 0)                                                                      |
| 1           | Enabled (0 for false, 1 for true)                                                                |
| 2           | Invert (0 for false, 1 for true).  If inverted, INACTIVE and ACTIVE are swapped in `AnalogRead`. |
| 3..5        | Reserved (set to 0)                                                                              |
| 6..7        | low range start value                                                                            |
| 8..9        | low range stop value                                                                             |
| 10..11      | high range start value                                                                           |
| 12..13      | high range stop value                                                                            |
| 14..17      | Reserved (set to 0)                                                                              |

## `Config`

| Byte Offset | Description                                                      |
|-------------|------------------------------------------------------------------|
| 0           | Reserved (set to 0)                                              |
| 1..4        | Bit mask of digital inputs to enable (bit 0 for input 0, etc.)   |
| 5..8        | Bit mask of digital outputs to enable (bit 0 for output 0, etc.) |
| 9..12       | Bit mask of analog inputs to enable (bit 0 for input 0, etc.)    |
| 13          | Bit mask of Wiegand inputs to enable (bit 0 for input 0, etc.)   |
| 14..18      | Reserved (set to 0)                                              |

## `RawRead`

Note: Wiegand card readers output their key presses as Wiegand, so the key presses also come across as a RawRead, typically with
whatever 4-bit or 8-bit keypad format the reader uses.

| Byte Offset | Description                                                                                                             |
|-------------|-------------------------------------------------------------------------------------------------------------------------|
| 0           | Reader index (Wiegand or other input index), starting at 0                                                              |
| 1           | Number of bits to trim in last byte of card data.  So for example for 26-bit Wiegand, this would be 6, because 32-6=26. |
| 2           | Number of bytes of card data that follow, maximum 32                                                                    |
| 3..(n-1)    | Card data bytes                                                                                                         |

## `RawWrite`

| Byte Offset | Description                                                                                                             |
|-------------|-------------------------------------------------------------------------------------------------------------------------|
| 0           | Reader index (Wiegand output index), starting at 0                                                                      |
| 1           | Number of bits to trim in last byte of card data.  So for example for 26-bit Wiegand, this would be 6, because 32-6=26. |
| 2           | Number of bytes of card data that follow, maximum 32                                                                    |
| 3..(n-1)    | Card data bytes                                                                                                         |

## `DigitalRead`

| Byte Offset | Description                                                                                                                 |
|-------------|-----------------------------------------------------------------------------------------------------------------------------|
| 0           | Digital input index, starting at 0                                                                                          |
| 1           | Raw value (0 for off, 1 for on)                                                                                             |
| 2           | Interpreted value (same as raw value, unless `DigitalInConfig` was sent with invert=true, in which case it is the opposite) |

## `AnalogRead`

| Byte Offset | Description                                                                           |
|-------------|---------------------------------------------------------------------------------------|
| 0           | Analog input index, starting at 0                                                     |
| 1           | Analog value as a 16-bit value.                                                       |
| 3           | Value interpretation: 0-4, where 0=INACTIVE, 1=ACTIVE, 2=SHORT, 3=CUT, 4=OUT_OF_RANGE |

## `DigitalWrite`

| Byte Offset | Description                                                                             |
|-------------|-----------------------------------------------------------------------------------------|
| 0           | Digital output index, starting at 0                                                     |
| 1           | Value (0 for off, 1 for on)                                                             |
| 2..3        | 0 for indefinite/permanent, otherwise pulse duration: duration in milliseconds to pulse |

The sub-controller is required to be able to perform a pulse of an output for a given number of milliseconds.  This is important because especially over
serial channels, the delays introduced by sending an "on" DigitalWrite followed by an "off" DigitalWrite can be too variable and result in an 
unreliable pulse duration.

## `RawKey`

Note that the Escape ASCII character (27 decimal) is a key that cancels any door access transaction in progress.

| Byte Offset | Description                                   |
|-------------|-----------------------------------------------|
| 0           | Keypad index (or reader index), starting at 0 |
| 1           | Key's ASCII code                              |

## `BioVerified`

| Byte Offset  | Description                                                                                                                                                                                     |
|--------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0            | Reader index (Wiegand or other input index), starting at 0                                                                                                                                      |
| 1            | Biometric technology, see values below                                                                                                                                                          |
| 2            | 0 for verification failed, 1 for verification succeeded                                                                                                                                         |
| 3            | Number of bytes of user ID data that follow, maximum 32                                                                                                                                         |
| 4..(n-6)     | User ID data bytes.  Each byte is an ASCII value.  If the User ID is a number, then this is an ASCII string representing the number.                                                            |
| (n-5)        | 0 for credential unid absent, 1 for credential unid present.  Note that either user ID must be specified, or credential unid present.  If both are specified, credential unid takes precedence. |
| (n-4)..(n-1) | If credential unid present, this is the unid of the credential.  Otherwise, zero.                                                                                                               |

### Biometric Technologies

| Value | Description   |
|-------|---------------|
| 0     | Generic       |
| 1     | Fingerprint   |
| 2     | Face          |
| 3     | Voice         |
| 4     | Iris          |
| 5     | Retina        |
| 6     | Hand geometry |
| 7     | Finger vein   |

## `BioRead`

| Byte Offset | Description                                                                |
|-------------|----------------------------------------------------------------------------|
| 0           | Reader index, starting at 0                                                |
| 1           | Biometric technology, see values above                                     |
| 2           | Biometric format, see values below                                         |
| 3-4         | Number of bytes of biometric data that follow (16-bit value), maximum 2048 |
| 5..(n-1)    | Biometric data bytes                                                       |

### Biometric Formats

| Value | Description              |
|-------|--------------------------|
| 0     | Fingerprint: ZKTeco      |
| 1     | Fingerprint: ANSI 378    |
| 2     | Fingerprint: ISO 19794-2 |
| 3     | Face: ZKTeco             |

## `UserIdRead`

| Byte Offset | Description                                                                                                                          |
|-------------|--------------------------------------------------------------------------------------------------------------------------------------|
| 0           | Reader index (Wiegand or other input index), starting at 0                                                                           |
| 1           | Number of bytes of user ID data that follow, maximum 32                                                                              |
| 2..(n-1)    | User ID data bytes.  Each byte is an ASCII value.  If the User ID is a number, then this is an ASCII string representing the number. |

## `RawKeys`

Note that the Escape ASCII character (27 decimal) is a key that cancels any door access transaction in progress.

| Byte Offset | Description                                             |
|-------------|---------------------------------------------------------|
| 0           | Keypad index (or reader index), starting at 0           |
| 1           | Number of bytes key data to follow, maximum 32          |
| 2..(n-1)    | Key data bytes - each byte is the ASCII code of the key |

## `ReaderState`

Note that the User ID is optional in this message, it is only provided if the reader is in the middle of a transaction, and the User ID is known.
The same is true for credential unid and credential holder unid.

| Byte Offset  | Description                                                                                                                                                              |
|--------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0            | Reader index (Wiegand or other input index), starting at 0                                                                                                               |
| 1            | Door mode type (see values below)                                                                                                                                        |
| 2            | State type (see values below)                                                                                                                                            |
| 3..6         | State type sequence number (This value increments when and only when the same stateType happens "again", but the previous stateType and the new stateType are the same). |
| 7            | Number of bytes of user ID data that follow, maximum 32                                                                                                                  |
| 8..(n-11)    | User ID data bytes.  Each byte is an ASCII value.  If the User ID is a number, then this is an ASCII string representing the number.                                     |
| (n-10)       | 0 for credential unid absent, 1 for credential unid present.                                                                                                             |
| (n-9)..(n-6) | If credential unid present, this is the unid of the credential.  Otherwise, zero.                                                                                        |
| (n-5)        | 0 for credential holder unid absent, 1 for credential holder unid present.                                                                                               |
| (n-4)..(n-1) | If credential holder unid present, this is the unid of the credential holder.  Otherwise, zero.                                                                          |

### Door Mode Types

| Value | Description                                                                               |
|-------|-------------------------------------------------------------------------------------------|
| 0     | Unlocked - free access                                                                    |
| 1     | No access                                                                                 |
| 2     | Card only                                                                                 |
| 3     | Card and PIN                                                                              |
| 4     | PIN only                                                                                  |
| 5     | Card or PIN                                                                               |
| 6     | Facility code only                                                                        |
| 7     | (Card and PIN) or PIN - Very uncommon and not supported by most hardware.                 |
| 8     | Emergency Unlocked - free access                                                          |
| 9     | Emergency No access (lockdown)                                                            |
| 10    | Blocked: Card only                                                                        |
| 11    | First Cred Unlock: Card only                                                              |
| 12    | Card and Bio                                                                              |
| 13    | Card and Bio and PIN                                                                      |
| 14    | Bio only                                                                                  |
| 15    | Bio and PIN                                                                               |
| 16    | (Bio and PIN) or PIN. - Very uncommon and not supported by most hardware                  |
| 17    | Bio or PIN                                                                                |
| 18    | Bio or Card                                                                               |
| 19    | Bio or Card or PIN                                                                        |
| 20    | (Card and PIN) or (Bio and PIN)                                                           |
| 21    | (Card and PIN) or (Bio and PIN) or PIN - Very uncommon and not supported by most hardware |
| 22    | (Card and PIN) or (Bio only)                                                              |
| 23    | (Card and PIN) or (Bio only) or PIN - Very uncommon and not supported by most hardware    |
| 24    | Card or (Bio and PIN)                                                                     |
| 25    | Card or (Bio and PIN) or PIN - Very uncommon and not supported by most hardware           |
| 26    | No access - also no REX                                                                   |
| 27    | Emergency No access (lockdown) - also no REX                                              |
| 28    | ID number (on keypad) and biometric.                                                      |
| 29    | First Cred Unlock: Card and PIN.                                                          |
| 30    | First Cred Unlock: PIN only.                                                              |
| 31    | First Cred Unlock: Card or PIN.                                                           |
| 32    | First Cred Unlock: Card and Bio.                                                          |
| 33    | First Cred Unlock: Card and Bio and PIN.                                                  |
| 34    | First Cred Unlock: Bio only.                                                              |
| 35    | First Cred Unlock: Bio and PIN.                                                           |
| 36    | First Cred Unlock: Bio or PIN.                                                            |
| 37    | First Cred Unlock: Bio or Card.                                                           |
| 38    | First Cred Unlock: Bio or Card or PIN.                                                    |
| 39    | First Cred Unlock: (Card and PIN) or (Bio and PIN).                                       |
| 40    | First Cred Unlock: (Card and PIN) or (Bio only).                                          |
| 41    | First Cred Unlock: Card or (Bio and PIN)                                                  |

### State Types

| Value | Description                                                                                                                                       |
|-------|---------------------------------------------------------------------------------------------------------------------------------------------------|
| 0     | Idle (awaiting card, pin if not in a static state)                                                                                                |
| 1     | Card has been read                                                                                                                                |
| 2     | Confirming PIN is (awaiting to be, or in the process of being) read                                                                               |
| 3     | Keys (from a keypad) is/are being read.  For Unique PIN                                                                                           |
| 4     | Command keys (from a keypad) is/are being read                                                                                                    |
| 5     | Credential to authorize a command is/are being read                                                                                               |
| 6     | Access granted pending escort (true granted/denied will depend on escort)                                                                         |
| 7     | Access granted, but awaiting elevator floor selection                                                                                             |
| 8     | Access granted, or command granted                                                                                                                |
| 9     | Access denied                                                                                                                                     |
| 10    | Timeout - a form of DENY that generates no events                                                                                                 |
| 11    | Access granted pending minimum occupancy (true granted/denied will depend on minimum number of valid credentials being presented)                 |
| 12    | Awaiting host grant processing                                                                                                                    |
| 13    | Next Credential: Idle (awaiting card, pin)                                                                                                        |
| 14    | Next Credential: Confirming PIN is (awaiting to be, or in the process of being) read                                                              |
| 15    | Biometric has been read and verified                                                                                                              |
| 16    | "Confirming" biometric is awaiting to be read.                                                                                                    |
| 17    | Cancel - a form of DENY that generates no events                                                                                                  |
| 18    | "Confirming" card is awaiting to be read.                                                                                                         |
| 19    | ID number has been read.                                                                                                                          |
| 20    | Biometric has been read (and has not been verified, or is in the process of being verified)                                                       |
| 21    | Access granted pending multi-cred (true granted/denied will depend on presentation of all required cred according to the multi-cred restriction). |

## `ReaderStatus`

| Byte Offset | Description                                                |
|-------------|------------------------------------------------------------|
| 0           | Reader index (Wiegand or other input index), starting at 0 |
| 1           | Offline (0 for online, 1 for offline)                      |
| 2           | Tamper (0 for normal, 1 for tamper)                        |
| 3           | Power (0 for normal, 1 for power failure)                  |

## `ProtocolPassthru`

| Byte Offset | Description                                                                                                                  |
|-------------|------------------------------------------------------------------------------------------------------------------------------|
| 0           | Protocol ID (see table below)                                                                                                |
| 1           | The total number of fragments the passthru message is broken into.  If not broken up (fits in one message), this value is 1. |
| 2           | The 0-based index of the fragment.                                                                                           |
| 3..4        | Number of passthru bytes                                                                                                     |
| 5..(n-1)    | Passthru bytes                                                                                                               |

### Passthru Protocol IDs

| Value | Description    |
|-------|----------------|
| 0     | None           |
| 1     | z9lockio       |
| 2     | secure element |

## `HostInfo`

| Byte Offset | Description                                        |
|-------------|----------------------------------------------------|
| 0           | Host model number (high byte)                      |
| 1           | Host model number (low byte)                       |
| 2           | Host firmware version (major) - as a binary number |
| 3           | Host firmware version (minor) - as a binary number |
| 4..11       | Host 64-bit serial number                          |

## `HostStatus`

| Byte Offset | Description                                   |
|-------------|-----------------------------------------------|
| 0           | Host pairing state                            |
| 1           | Tamper (0 for normal, 1 for tamper)           |
| 2           | Low battery (0 for normal, 1 for low battery) |
| 3           | Sync requested (0 for true, 1 for false)      |

### Host Pairing States

| Value | Description            |
|-------|------------------------|
| 0     | Construction mode      |
| 1     | Pairing mode           |
| 2     | Paired (customer mode) |

## `FileAvailable`

| Byte Offset | Description         |
|-------------|---------------------|
| 0           | File ID, see below. |
| 1..4        | 32-bit file length  |

**File IDs**

| Value | Description              |
|-------|--------------------------|
| 0     | None                     |
| 1     | Software/firmware update |

## `EncryptedContent`

| Byte Offset | Description                                                                          |
|-------------|--------------------------------------------------------------------------------------|
| 0..1        | Number of encrypted bytes, plus 12 for the the 12-byte IV, plus 16 bytes for the tag |
| 2..(n-1)    | 12-byte IV, followed by 16-byte tag, followed by encrypted bytes                     |

The first 12 bytes of the data will be the IV used to encrypt the message.  This will be randomly generated for each message.
The next 16 bytes will be the tag.

## `EncryptionKeyExchange`

| Byte Offset | Description                                                 |
|-------------|-------------------------------------------------------------|
| 0           | `EncryptionKeyExchangeType`                                 |
| 1           | number of bytes                                             |
| 2..18       | bytes, meaning/use dependent on `EncryptionKeyExchangeType` |

### `EncryptionKeyExchangeType` Values

| Value | Description                                                                                                                                                                                                                                                                                                 |
|-------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0     | Link-layer encryption: Linking seed request.  Sent by upstream device.  Sent only if never linked, or after factory reset.  bytes sent is random seed generated by sender.                                                                                                                                  |
| 1     | Link-layer encryption: Linking seed response.  Sent by downstream device in response to Linking seed request (0).  bytes sent is random seed generated by sender.  The base linking seed will be the bitwise XOR of both seeds.                                                                             |
| 2     | Link-layer encryption: Session seed request.  Sent by upstream device.  bytes sent is random seed generated by sender.                                                                                                                                                                                      |
| 3     | Link-layer encryption: Session seed response. Sent by downstream device in response to Session seed request (2).  bytes sent is random seed generated by sender.  The actual AES session key will be the bitwise XOR of the base linking seed, the session seed req bytes, and the session seed resp bytes. |

## `ApplicationEncryptionKeyExchange`

| Byte Offset | Description                                                                      |
|-------------|----------------------------------------------------------------------------------|
| 0           | `ApplicationEncryptionKeyExchangeType`                                           |
| 1           | number of key/nonce bytes                                                        |
| 2..34       | key/nonce bytes, meaning/use dependent on `ApplicationEncryptionKeyExchangeType` |

### `EncryptionKeyExchangeType` Values

| Value | Description                                                                                                                                                                                                           |
|-------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0     | Cloud-lock encryption: Request for (lock) public key.  Sent by upstream device.                                                                                                                                       |
| 1     | Cloud-lock encryption: Response with (lock) public key.  Sent by downstream device in response to Request for (lock) public key (4).                                                                                  |
| 2     | Cloud-lock encryption: Cloud-lock encryption: request for key agreement.  Sent by upstream device.  bytes sent is the cloud EC public key, 33 bytes.                                                                  |
| 3     | Cloud-lock encryption: response with key agreement using lock public key and cloud public key.  Sent by downstream device in response to request for key agreement (2).  bytes sent is agreed key (ECDH), 16 bytes.   |
| 4     | Mobile-lock encryption: Request for nonce that will be used to challenge the mobile device over BLE.  Sent by downstream device to upstream device.  Upstream device generates nonce.  Request bytes sent is 0 bytes. |
| 5     | Mobile-lock encryption: Response to BLE challenge nonce request.  Generated by upstream device, and sent by upstream device to downstream device.  Response bytes sent is nonce, 16 bytes.                            |

## `FileQuery`

| Byte Offset | Description                                                                                                                                |
|-------------|--------------------------------------------------------------------------------------------------------------------------------------------|
| 0           | File ID, see `FileAvailable`                                                                                                               |
| 1..4        | 32-bit offset requested.  0 for the beginning of the file, otherwise should generally be offset + numBytes from most recent `FileContents` |

## `FileContents`

| Byte Offset | Description                                                                                                                                                                   |
|-------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 0           | File ID, see `FileAvailable`                                                                                                                                                  |
| 1..4        | 32-bit offset of data provided within file - must match offset requested in `FileQuery`                                                                                       |
| 5           | End-of-file (EOF), 0=false, 1=true.  Note that if eof=true, bytes may be provided, in which case it means that the end of file is immediately after the bytes being provided. |
| 6           | 0 for no exception, nonzero for any kind of error accessing or providing the file.                                                                                            |
| 7..8        | The number of bytes (16-bit value)                                                                                                                                            |
| 9..n-1      | Requested file bytes.                                                                                                                                                         |

## `ProcessFile`

| Byte Offset | Description                  |
|-------------|------------------------------|
| 0           | File ID, see `FileAvailable` |

# Appendix A: CRC16 Algorithm

The CRC16 is a 16-bit CRC calculated over all bytes in the message, except the 2 CRC16 bytes themselves.

The algorithm is CCITT-16, with a seed of 0x0000.  This is exactly the same CRC algorithm and seed used in the
OSDP specification.


