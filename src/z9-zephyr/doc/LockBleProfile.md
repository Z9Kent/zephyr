# Wavelynx Lock BLE Profile Specification

**Version:** 2

This document describes the packet structure and operations surrounding BLE
advertisement of the WaveLynx Lock Reader Module as well as its BLE GATT
profile. The Lock Module operates as a BLE peripheral device and as such, needs
to relay data to host devices scanning for its presence. This is done through a
specified BLE advertising payload.

The high level details enclosed in the lock advertisement are as follows:

* Lock Service UUID.
* Lock ID.
* Lock Status.
* Sync Required.

The underlying GATT profile implemented by the lock is composed of a single service and
associated characteristic in order to facilitate rapid writes/reads during a
connection/transaction cycle.

## Advertisement Packet Structure

BLE advertisement packets are constrained to a maximum of 31 bytes, so care must be taken to include
all required fields within the limited amount of space. As such, the following fields are encoded
in each advertisement.

| Field                     | Default Value     | Field Length | Description                                                                                               |
| ------------------------- | ----------------- | ------------ | --------------------------------------------------------------------------------------------------------- |
| Local Name (Lock Payload) | N/A               | 8            | The BLE SIG "Local Name" field is used to convey the **Lock Payload**                                     |
| Service UUID              | Lock Service UUID | 16           | Contains the 128 bit Lock service UUID. This is needed for background discovery on consumer smart phones. |

### Advertisement Data

Each of the fields described in the previous section need to be encoded in the advertisement packet
per the Bluetooth SIG encoding definition (including length and headers). The following describes
how the payload is encoded in this packet

| Field               | Length | Value                                 |
| ------------------- | ------ | ------------------------------------- |
| Local Name Header   | 2      | `0x0909`                              |
| Local Name Data     | 8      | Base64 encoded **Lock Payload** data. |
| Service UUID Header | 2      | `0x1107`                              |
| Service UUID        | 16     | `0x0242ac120002afa111eda9847599914c`  |

### Lock Service UUID

The following service UUID is advertised in the **Service UUID** field. This represents the sole
GATT service used to communicate to the locks:

```
7599914c-a984-11ed-afa1-0242ac120002
```

### Advertisement Lock Payload

The lock payload is transmitted in the BLE advertisement inside of the Bluetooth SIG "Local Name"
field. The data contained in the field is byte encoded using the payload structure described below.
This payload is then **base64** encoded when placed in the advertisement for easy capture and
decoding by BLE central devices.

| Field       | Length | Description                                                                                                                             |
|-------------|--------|-----------------------------------------------------------------------------------------------------------------------------------------|
| Lock Status | 1      | Bitmask relaying the mode and status of the lock. See *Lock Status Bitmask* definition below.                                           |
| Lock ID     | 4      | If in `CONSTRUCTION` or `PAIRING` mode, this will be the lock serial number. In `NORMAL` mode, this will be the lock's assigned `unid`. |

**NOTE:** If the **Lock ID** field exceeds 4 bytes in length, the **least 4 significant bytes** shall be transmitted.

These fields are serialized into the byte structure in the following sequence:

```
[1 byte Lock Status][4 byte Lock ID]
```

### Lock Status Bitmask

| Field                | Start Bit | Length | Description                                                                           |
| -------------------- | --------- | ------ | ------------------------------------------------------------------------------------- |
| Mode                 | 0-1       | 2      | Lock mode. 0 = `CONSTRUCTION`, 1 = `PAIRING`, 2 = `NORMAL`.                           |
| Sync Requested       | 2         | 1      | Flag letting host devices know that the lock is requesting a connection and sync.     |
| Battery Low/Critical | 3         | 1      | Flag letting host devices know that the lock currently has a low or critical battery. |
| Tamper               | 4         | 1      | Flag letting host devices know that the lock is currently in tamper state.            |
| RFU                  | 5         | 3      | Reserved for future use.                                                              |

### Advertisement Examples

**Advertising Packet**

This example shows the construction of the BLE advertisement packet for the Lock Reader Module.
The fields encoded use the values from the examples below, namely the final **Lock Payload** field
of `CxEiM0Q=`.

To construct the advertising payload, the base64 encoded **Lock Payload** is represented by the bytes below:

```
0x437845694D30513D
```

Everything is then encoded into the full advertising payload:

```
0x0909437845694D30513D11070242ac120002afa111eda9847599914c
```

**Lock Payload**

This example shows the construction of the lock payload using the **Lock Status** bitmask from the
section below: `0x0B`, and a **Lock ID** field of: `11223344`.

First, we byte encode the payload:

```
0x0B11223344
```

We then base64 encode the byte data for insertion into the BLE advertisement packet:

```
CxEiM0Q=
```

**Lock Status Bitmask**

This example show the lock status bitmask with the following fields set:

| Field                | Value   | Description             |
| -------------------- | ------- | ----------------------- |
| Mode                 | `0b11`  | `NORMAL` mode set.      |
| Sync Requested       | `0b0`   | **No** sync requested.  |
| Battery Low/Critical | `0b1`   | Battery **is critical** |
| Tamper               | `0b0`   | **No** tamper detected. |
| RFU                  | `0b000` | RFU bits unset.         |

The above results in the following bitmask:

```
0b00001011
```

Corresponding to the following hex encoded byte:

```
0x0B
```

## Bonding/Pairing

All WaveLynx devices do not support bonding or pairing of any kind.

## MTU

Once connected, a central device may negotiate the following MTU:

| Device | Supported MTU |
|--------|---------------|
| Lock   | 420 bytes     |

## GATT Profile

This section describes the GATT payload exposed by the lock.

### Services

A single service is contained in the lock's GATT profile to facilitate
the writing of commands and reading of responses. All characteristics
are contained within this service.

|                     |                                        |
|---------------------|----------------------------------------|
| **Name**            | Wavelynx lock service                  |
| **UUID**            | `7599914c-a984-11ed-afa1-0242ac120002` |
| **Characteristics** | `Command`                              |

### Characteristics

A single characteristic is contained within the *Wavelynx Lock Service*
from above.

**Command Characteristic**

All communication with the lock takes place using this characteristic. The lock uses a command-response
messaging pattern which adheres to the following guidelines:

* The central device issues one command at a time to the characteristic through a
  Write Without Response operation.
* The lock responds to the command through a notification to the central device.
* The central device may not issue another command until it has recieved a
  response notification for the previous command.

|                 |                                        |
|-----------------|----------------------------------------|
| **Name**        | Command characteristic                 |
| **UUID**        | `ee8732b3-2d52-409b-9084-70ad31f6c790` |
| **Properties**  | Write Without Response, Notify         |
| **Data Format** | Byte Array                             |
| **Size**        | 420                                    |
