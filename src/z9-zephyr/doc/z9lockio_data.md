# Z9 Security z9lockio Smart Lock I/O Protocol Enumerated Values and Data Structures

![Z9 Security](z9security.png)

_Copyright &copy; 2015-2024 Z9 Security.
Use of this documentation requires both an active non-disclosure agreement, as well as an active software redistribution agreement, with Z9 Security,
and is subject to the terms of those agreements. Any other use, or disclosure, of this documentation is prohibited._

# Enumerated Values and Data Structures

## `LockCredTechnology` Enumeration Values

Different credential technology types.  Allows LockCred to be specific about which technology type is in use, so that a given bitstream (credBytes) can be restricted to being accepted only over the correct technology.
This way, in particular, a lower-security technology (e.g. Prox) cannot be used to present the bitstream (credBytes) of a higher-security technology (e.g. NFC, Bluetooth).

| Ordinal | Value                   | Description
| ------- | ----------------------- | -----------
| 0       | `ANY`                   | Any
| 1       | `PROX_ANY`              | Any proximity (125khz) technology
| 2       | `BLUETOOTH_ANY`         | Any Bluetooth/BLE technology
| 3       | `NFC_ANY`               | Any NFC technology
| 4       | `DESFIRE_ANY`           | Any DESFire technology
| 5       | `ICLASS_ANY`            | Any iClass technology
| 6       | `BLUETOOTH_WAVELYNX`    | WaveLynx Bluetooth/BLE independent of any Z9 technology
| 7       | `BLUETOOTH_Z9_WAVELYNX` | Z9 Lock Bluetooth/BLE technology for mobile credentials for WaveLynx
| 8       | `NFC_GOOGLE`            | Google NFC technology
| 9       | `NFC_APPLE`             | Apple NFC technology
| 10      | `NFC_WAVELYNX`          | WaveLynx NFC technology
| 11      | `DESFIRE_LEAF`          | Leaf DESFire technology
| 12      | `DESFIRE_UID`           | UID-only DESFire technology
| 13      | `ICLASS_FULL`           | Full iClass technology
| 14      | `ICLASS_UID`            | UID-only iClass technology

## `LockMode` Enumeration Values

Corresponds to Z9/FL=X DoorModeType.

| Ordinal | Value                                       | Description
| ------- | ------------------------------------------- | -----------
| 0       | `NONE`                                      | Used to indicate null or N/A
| 1       | `STATIC_STATE_UNLOCKED`                     | Unlocked - free access
| 2       | `STATIC_STATE_LOCKED`                       | No access
| 3       | `CARD_ONLY`                                 | Card only
| 4       | `CARD_AND_CONFIRMING_PIN`                   | Card and PIN
| 5       | `UNIQUE_PIN_ONLY`                           | PIN only
| 6       | `CARD_ONLY_OR_UNIQUE_PIN`                   | Card or PIN
| 7       | `EMERGENCY_STATIC_STATE_UNLOCKED`           | Emergency Unlocked - free access
| 8       | `EMERGENCY_STATIC_STATE_LOCKED`             | Emergency No access (lockdown)
| 9       | `FIRST_CRED_UNLOCK_CARD_ONLY`               | First Cred Unlock: Card only
| 10      | `FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN` | First Cred Unlock: Card and PIN
| 11      | `FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY`         | First Cred Unlock: PIN only
| 12      | `FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN` | First Cred Unlock: Card or PIN

## `LockEvtCode` Enumeration Values

Event codes for LockEvt.

| Ordinal | Value                                                  | Description
| ------- | ------------------------------------------------------ | -----------
| 0       | `NONE`                                                 | None.
| 1       | `STARTUP`                                              | Z9 Lock startup.
| 2       | `DOOR_ACCESS_GRANTED`                                  | Door access granted.
| 3       | `DOOR_ACCESS_DENIED`                                   | Door access denied - generic
| 4       | `DOOR_ACCESS_DENIED_INACTIVE`                          | Door access denied - inactive credential
| 5       | `DOOR_ACCESS_DENIED_NOT_EFFECTIVE`                     | Door access denied - credential not yet effective
| 6       | `DOOR_ACCESS_DENIED_EXPIRED`                           | Door access denied - credential expired
| 7       | `DOOR_ACCESS_DENIED_OUTSIDE_SCHED`                     | Door access denied - outside of schedule
| 8       | `DOOR_ACCESS_DENIED_UNKNOWN_CRED_NUM`                  | Door access denied - unknown credential number
| 9       | `DOOR_ACCESS_DENIED_UNKNOWN_CRED_UNIQUE_PIN`           | Door access denied - unknown credential unique PIN
| 10      | `DOOR_ACCESS_DENIED_DOOR_MODE_STATIC_LOCKED`           | Door access denied - door mode: static locked (no access)
| 11      | `DOOR_ACCESS_DENIED_DOOR_MODE_DOESNT_ALLOW_CARD`       | Door access denied - door mode doesn't allow card
| 12      | `DOOR_ACCESS_DENIED_DOOR_MODE_DOESNT_ALLOW_UNIQUE_PIN` | Door access denied - door mode doesn't allow unique PIN
| 13      | `DOOR_ACCESS_DENIED_NO_CONFIRMING_PIN_FOR_CRED`        | Door access denied - no confirming PIN for credential.
| 14      | `DOOR_ACCESS_DENIED_INCORRECT_CONFIRMING_PIN`          | Door access denied - incorrect confirming PIN.
| 15      | `DOOR_ACCESS_DENIED_DOOR_MODE_EMERGENCY_STATIC_LOCKED` | Door access denied - door mode: emergency static locked (lockdown)
| 16      | `DOOR_ACCESS_DENIED_DEADBOLT`                          | Door access denied - deadbolt active
| 17      | `DOOR_ACCESS_DENIED_NO_PIN_PRESENTED`                  | Door access denied - no PIN presented
| 18      | `DOOR_ACCESS_DENIED_INCOMPLETE`                        | Door access denied - incomplete access transaction
| 19      | `DOOR_ACCESS_DENIED_DOOR_PRIVACY`                      | Door access denied - privacy mode active
| 20      | `DOOR_FORCED`                                          | Door forced open.
| 21      | `DOOR_NOT_FORCED`                                      | Door not forced.
| 22      | `DOOR_HELD`                                            | Door held open.
| 23      | `DOOR_NOT_HELD`                                        | Door not held.
| 24      | `DOOR_OPENED`                                          | Door opened.
| 25      | `DOOR_CLOSED`                                          | Door closed.
| 26      | `DOOR_LOCKED`                                          | Door locked.
| 27      | `DOOR_UNLOCKED`                                        | Door unlocked.
| 28      | `DOOR_MODE_STATIC_STATE_UNLOCKED`                      | Door mode: Unlocked - free access.
| 29      | `DOOR_MODE_STATIC_STATE_LOCKED`                        | Door mode: No access.
| 30      | `DOOR_MODE_CARD_ONLY`                                  | Door mode: Card only.
| 31      | `DOOR_MODE_CARD_AND_CONFIRMING_PIN`                    | Door mode: Card and PIN.
| 32      | `DOOR_MODE_UNIQUE_PIN_ONLY`                            | Door mode: PIN only.
| 33      | `DOOR_MODE_CARD_ONLY_OR_UNIQUE_PIN`                    | Door mode: Card or PIN.
| 34      | `DOOR_MODE_EMERGENCY_STATIC_STATE_UNLOCKED`            | Door mode: Emergency Unlocked - free access.
| 35      | `DOOR_MODE_EMERGENCY_STATIC_STATE_LOCKED`              | Door mode: Emergency No access (lockdown).
| 36      | `DOOR_MODE_FIRST_CRED_UNLOCK_CARD_ONLY`                | Door mode: First Cred Unlock: Card only.
| 37      | `DOOR_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN`  | Door mode: First Cred Unlock: Card and PIN.
| 38      | `DOOR_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY`          | Door mode: First Cred Unlock: PIN only.
| 39      | `DOOR_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN`  | Door mode: First Cred Unlock: Card or PIN.
| 40      | `EXIT_REQUESTED`                                       | Exit requested.
| 41      | `MOMENTARY_UNLOCK`                                     | Momentary unlock.
| 42      | `DOOR_FORCED_UNMASKED`                                 | Door forced unmasked.
| 43      | `DOOR_FORCED_MASKED`                                   | Door forced masked.
| 44      | `DOOR_HELD_UNMASKED`                                   | Door held unmasked.
| 45      | `DOOR_HELD_MASKED`                                     | Door held masked.
| 46      | `KEY_OVERRIDE`                                         | Access to a door with a physical key which overrides the electronic access control function.
| 47      | `DEADBOLT_ACTIVE`                                      | Mechanical deadbolt activated (projected).
| 48      | `DEADBOLT_INACTIVE`                                    | Mechanical deadbolt deactivate (retracted).
| 49      | `DOOR_HELD_WARNING`                                    | Warning before DOOR_HELD.
| 50      | `BATTERY_OK`                                           | Battery OK.
| 51      | `BATTERY_LOW`                                          | Battery low.
| 52      | `BATTERY_CRITICAL`                                     | Battery critical.
| 53      | `BATTERY_FAIL`                                         | Battery failure - can be recorded just prior to entering failure mode.
| 54      | `BATTERY_LEVEL`                                        | Just the battery level, without any info as to ok/low/critical/fail.
| 55      | `TAMPER_NORMAL`                                        | Tamper normal (not active).
| 56      | `TAMPER`                                               | Tamper active.
| 57      | `SCHED_ACTIVE`                                         | Schedule active.
| 58      | `SCHED_INACTIVE`                                       | Schedule inactive.
| 59      | `DOOR_LOCAL_LOCKED`                                    | Door: door local: Always locked, no access - same as DoorModeStaticState.LOCKED.
| 60      | `DOOR_LOCAL_UNLOCKED`                                  | Door: door local: Always unlocked - same as DoorModeStaticState.UNLOCKED.
| 61      | `DOOR_LOCAL_ACCESS_CONTROLLED`                         | Door: door local: Normally locked (secure) but available for access-controlled entry - same as DoorModeStaticState.ACCESS_CONTROLLED.
| 62      | `DOOR_LOCAL_PRIVACY`                                   | Door: door local: locked in privacy mode, no access except for credentials with the ability to override privacy.
| 63      | `DOOR_LOCAL_ESCAPE_AND_RETURN`                         | Door: door local: unlocked for the purposes of allowing an exiting person to get back in.
| 64      | `EXIT_REQUEST_DENIED`                                  | Exit request denied.
| 65      | `MOMENTARY_UNLOCK_DENIED`                              | Momentary unlock denied.
| 66      | `DOOR_LOCAL_NOT_PRIVACY`                               | Opposite of DOOR_LOCAL_PRIVACY, used when other DOOR_LOCAL_ state types/event codes not in use for a particular door.
| 67      | `IPB_PRESSED`                                          | Interior Push Button (IPB) was pressed.  If the IPB is used to toggle something like privacy mode, this event code gives no indication of which way it was toggled, nor of the effect.  The effect will generally be seen with another event.

## `LockDevActionType` Enumeration Values

An explicit action for the lock (device) to take.

| Ordinal | Value                                                     | Description
| ------- | --------------------------------------------------------- | -----------
| 0       | `NONE`                                                    | None.
| 1       | `MOMENTARY_UNLOCK`                                        | Momentary unlock.
| 2       | `RESET_LOCK_MODE`                                         | Cancel overridden lock mode to default/scheduled.
| 3       | `SET_LOCK_MODE_STATIC_STATE_UNLOCKED`                     | Unlocked - free access.
| 4       | `SET_LOCK_MODE_STATIC_STATE_LOCKED`                       | No access.
| 5       | `SET_LOCK_MODE_CARD_ONLY`                                 | Card only.
| 6       | `SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN`                   | Card and PIN.
| 7       | `SET_LOCK_MODE_UNIQUE_PIN_ONLY`                           | PIN only.
| 8       | `SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN`                   | Card or PIN.
| 9       | `SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED`           | Emergency Unlocked - free access.
| 10      | `SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED`             | Emergency No access (lockdown).
| 11      | `SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY`               | First Cred Unlock: Card only.
| 12      | `SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN` | First Cred Unlock: Card and PIN.
| 13      | `SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY`         | First Cred Unlock: PIN only.
| 14      | `SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN` | First Cred Unlock: Card or PIN.

## `LockFunction` Enumeration Values

Industry-standard lock functions.

| Ordinal | Value       | Description
| ------- | ----------- | -----------
| 0       | `NONE`      | None
| 1       | `OFFICE`    | IPB toggles static unlock.  Credential toggles static unlock.  Press and hold IPB enters privacy mode.
| 2       | `APARTMENT` | IPB unlocks and leaves unlocked.  Exiting unlocks and leaves unlocked.
| 3       | `CLASSROOM` | AKA "storeroom" or "standard" mode.  IPB activates lockdown (emergency static state locked).  IPB has to be pressed 2x for 3sec.  10sec push cancels any 3sec pushes.
| 4       | `PRIVACY`   | IPB activates privacy mode.

## `LockHostGrantFallbackMode` Enumeration Values

Host grant fallback mode - in the case of host grant timeout or unreachable.

| Ordinal | Value            | Description
| ------- | ---------------- | -----------
| 0       | `NONE`           | None
| 1       | `DENY`           | Deny access
| 2       | `LOCAL_DECISION` | Local decision

## `LockHostGrantInitiationMode` Enumeration Values

If host grant is enabled, more specifically, when it is to be initiated.

| Ordinal | Value          | Description
| ------- | -------------- | -----------
| 0       | `NEVER`        | Never initiate (equivalent to enabled=false)
| 1       | `UNKNOWN_CRED` | Initiate on unknown credential presented
| 2       | `ALWAYS`       | Always initiate

## `LockIdentificationType` Enumeration Values

Type used for LockIdentification.

| Ordinal | Value                  | Description
| ------- | ---------------------- | -----------
| 0       | `NONE`                 | None
| 1       | `LOCK`                 | Z9 Lock
| 2       | `HUB_CONTROLLER`       | Hub-controller
| 3       | `MOBILE`               | Mobile device
| 4       | `AUTHORITATIVE_SOURCE` | Authoritative source (Z9/FL=X cloud server)

## `LockFileCategory` Enumeration Values

File category for push/pull files.

| Ordinal | Value             | Description
| ------- | ----------------- | -----------
| 0       | `NONE`            | None
| 1       | `SOFTWARE_UPDATE` | Software (firmware) updates
| 2       | `KEYS`            | Encryption keys and certificates
| 3       | `LICENSE`         | Base license and feature licenses
| 4       | `DIAGNOSTICS`     | Diagnostic logs

## `LockFileIdentifier` Enumeration Values

File identifier for push/pull files.

| Ordinal | Value     | Description
| ------- | --------- | -----------
| 0       | `NONE`    | None
| 1       | `DEFAULT` | Default for the category

## `LockHostGrantReqType` Enumeration Values

Type used for LockHostGrantReq.

| Ordinal | Value       | Description
| ------- | ----------- | -----------
| 0       | `NONE`      | None
| 1       | `CRED_READ` | Credential/card read

## `LockPolicyPriority` Enumeration Values

The priority level for (the assertions of a) policy. Policies for more important levels take precedence over less important levels.

| Ordinal | Value             | Description
| ------- | ----------------- | -----------
| 0       | `DEFAULT`         | e.g. the default configured for a device
| 1       | `SCHEDULE`        | e.g. a scheduled door mode
| 2       | `POLICY_OVERRIDE` | e.g. a policy which links inputs to outputs
| 3       | `MANUAL_OVERRIDE` | a manually executed command
| 4       | `EMERGENCY`       | emergency

## `LockDate` Data Structure

Represents a calendar date (month day year).

Maximum serialized length: 4 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `year`                                     | 16-bit unsigned integer            | year
| 1 byte                           | `month`                                    | unsigned byte                      | Month of year, 1-12.
| 1 byte                           | `day`                                      | unsigned byte                      | Day of month, 1-31.

## `LockTimeOfDay_ToMinute` Data Structure

Wall clock time of day, to the minute.

Maximum serialized length: 2 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `hour`                                     | unsigned byte                      | Hour of day, 0-23.
| 1 byte                           | `minute`                                   | unsigned byte                      | Minute of hour, 0-59

## `LockTimeOfDay_ToQuarterHour` Data Structure

Wall clock time of day, to the 15 minute interval.

Maximum serialized length: 1 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `quarterHour`                              | unsigned byte                      | Time of day down to the quarter hour.  0 is midnight, 1 is 0:15, etc.

## `LockTimeOfDay_ToSecond` Data Structure

Wall clock time of day, to the second.

Maximum serialized length: 3 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `hour`                                     | unsigned byte                      | Hour of day, 0-23.
| 1 byte                           | `minute`                                   | unsigned byte                      | Minute of hour, 0-59
| 1 byte                           | `second`                                   | unsigned byte                      | Second of minute, 0-59

## `LockDateTime_ToMinute` Data Structure

A local date/time with resolution down to the minute.

Maximum serialized length: 6 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `year`                                     | 16-bit unsigned integer            | year
| 1 byte                           | `month`                                    | unsigned byte                      | Month of year, 1-12.
| 1 byte                           | `day`                                      | unsigned byte                      | Day of month, 1-31.
| 1 byte                           | `hour`                                     | unsigned byte                      | Hour of day, 0-23.
| 1 byte                           | `minute`                                   | unsigned byte                      | Minute of hour, 0-59

## `LockDateTime_ToSecond` Data Structure

A local date/time down to the second.

Maximum serialized length: 7 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `year`                                     | 16-bit unsigned integer            | year
| 1 byte                           | `month`                                    | unsigned byte                      | Month of year, 1-12.
| 1 byte                           | `day`                                      | unsigned byte                      | Day of month, 1-31.
| 1 byte                           | `hour`                                     | unsigned byte                      | Hour of day, 0-23.
| 1 byte                           | `minute`                                   | unsigned byte                      | Minute of hour, 0-59
| 1 byte                           | `second`                                   | unsigned byte                      | Second of minute, 0-59

## `LockEvtContent` Data Structure

Base class for content contained within LockEvt.


| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `contentType`                              | byte                               | Content type discriminator.
| variable                         |                                            |                                    | discriminator-specific content

## `LockEvtDelta` Data Structure

Specifies the delta to the default processing of a LockEvt for a given LockEvtCode (do not suppress, not priority).

Maximum serialized length: 2 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `suppress`                                 | boolean                            | if true, the associated LockEvtCode is suppressed entirely.
| 1 byte                           | `priority`                                 | boolean                            | if true, the associated LockEvtCode is flagged as priority=true in LockEvtModifiers

## `LockEvtModifiers` Data Structure

Flags/modifiers for a LockEvt.

Maximum serialized length: 7 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `priority`                                 | boolean                            | If true, this is considered a priority event.
| 1 byte                           | `hostGrant`                                | boolean                            | If true, the decision was made by the controller.  If both hostGrant and mobileGrant are false, the decision was made by the lock itself.
| 1 byte                           | `mobileGrant`                              | boolean                            | If true, the decision was made by a mobile device (credential not needed to be in db).  If both hostGrant and mobileGrant are false, the decision was made by the lock itself.
| 1 byte                           | `usedCard`                                 | boolean                            | For access events - if true, card was used/presented.
| 1 byte                           | `usedPin`                                  | boolean                            | For access events - if true, PIN was used/presented.
| 1 byte                           | `emergency`                                | boolean                            | For access events, if the emergency modifier is set on the credential.
| 1 byte                           | `doublePresentation`                       | boolean                            | double credential presentation.

## `LockDstTransition` Data Structure

The specification of when a daylight savings transition occurs.  Follows the Posix conventions.

Maximum serialized length: 4 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `month`                                    | unsigned byte                      | Month where the transition happens, from 1 to 12.
| 1 byte                           | `nth`                                      | unsigned byte                      | nth occurrance of dayOfWeek in the month, where n is 1-4, or 5 meaning the last such day in the month.
| 1 byte                           | `dayOfWeek`                                | unsigned byte                      | Day of week, 0-6, with 0 indicating Sunday.
| 1 byte                           | `hour`                                     | unsigned byte                      | Hour of day when transition happens, 0-23.

## `LockAccessModifiers` Data Structure

Modifiers which affect the processing of a LockCred obtaining access.

Maximum serialized length: 8 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `extDoorTime`                              | boolean                            | If true, use extended door times.
| 1 byte                           | `administrator`                            | boolean                            | If true, able to configure/manipulate Z9 Lock in administrator mode.
| 1 byte                           | `privacyExempt`                            | boolean                            | If true, able to access Z9 Lock in privacy mode.
| 1 byte                           | `staticStateLockedExempt`                  | boolean                            | If true, able to access Z9 Lock in static state locked mode.
| 1 byte                           | `emergencyStaticStateLockedExempt`         | boolean                            | If true, able to access Z9 Lock in emergency static state locked mode.
| 1 byte                           | `emergency`                                | boolean                            | If true, set the emergency=true on LockEvtModifiers.
| 1 byte                           | `firstCredUnlock`                          | boolean                            | If true, able to trigger first cred unlock, if the Z9 Lock is in a first-unlocks mode.
| 1 byte                           | `pinUnique`                                | boolean                            | Not really an access modifier, but put here for efficiency purposes.

## `LockCredActions` Data Structure

Actions to be taken on presentation of a LockCred.

Maximum serialized length: 9 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `access`                                   | boolean                            | Access
| 1 byte                           | `setLockMode_STATIC_STATE_UNLOCKED`        | boolean                            | Set the lock mode to static state unlocked.
| 1 byte                           | `setLockMode_EMERGENCY_STATIC_STATE_UNLOCKED` | boolean                            | Set the lock mode to emergency static state unlocked.
| 1 byte                           | `setLockMode_STATIC_STATE_LOCKED`          | boolean                            | Set the lock mode to static state locked.
| 1 byte                           | `setLockMode_EMERGENCY_STATIC_STATE_LOCKED` | boolean                            | Set the lock mode to emergency static state locked.
| 1 byte                           | `cancelLockMode_STATIC_STATE_UNLOCKED`     | boolean                            | Cancel the lock mode static state unlocked.
| 1 byte                           | `cancelLockMode_EMERGENCY_STATIC_STATE_UNLOCKED` | boolean                            | Cancel the lock mode emergency static state unlocked.
| 1 byte                           | `cancelLockMode_STATIC_STATE_LOCKED`       | boolean                            | Cancel the lock mode static state locked.
| 1 byte                           | `cancelLockMode_EMERGENCY_STATIC_STATE_LOCKED` | boolean                            | Cancel the lock mode emergency static state locked.

## `LockDevActionPermissions` Data Structure

Permissions indicating which LockDevActionType are allowed, by a LockCred explicit action from a mobile credential, for example.

Maximum serialized length: 14 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `allow_MOMENTARY_UNLOCK`                   | boolean                            | Momentary unlock.
| 1 byte                           | `allow_RESET_LOCK_MODE`                    | boolean                            | Cancel overridden lock mode to default/scheduled.
| 1 byte                           | `allow_SET_LOCK_MODE_STATIC_STATE_UNLOCKED` | boolean                            | Unlocked - free access.
| 1 byte                           | `allow_SET_LOCK_MODE_STATIC_STATE_LOCKED`  | boolean                            | No access.
| 1 byte                           | `allow_SET_LOCK_MODE_CARD_ONLY`            | boolean                            | Card only.
| 1 byte                           | `allow_SET_LOCK_MODE_CARD_AND_CONFIRMING_PIN` | boolean                            | Card and PIN.
| 1 byte                           | `allow_SET_LOCK_MODE_UNIQUE_PIN_ONLY`      | boolean                            | PIN only.
| 1 byte                           | `allow_SET_LOCK_MODE_CARD_ONLY_OR_UNIQUE_PIN` | boolean                            | Card or PIN.
| 1 byte                           | `allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_UNLOCKED` | boolean                            | Emergency Unlocked - free access.
| 1 byte                           | `allow_SET_LOCK_MODE_EMERGENCY_STATIC_STATE_LOCKED` | boolean                            | Emergency No access (lockdown).
| 1 byte                           | `allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY` | boolean                            | First Cred Unlock: Card only.
| 1 byte                           | `allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_AND_CONFIRMING_PIN` | boolean                            | First Cred Unlock: Card and PIN.
| 1 byte                           | `allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_UNIQUE_PIN_ONLY` | boolean                            | First Cred Unlock: PIN only.
| 1 byte                           | `allow_SET_LOCK_MODE_FIRST_CRED_UNLOCK_CARD_ONLY_OR_UNIQUE_PIN` | boolean                            | First Cred Unlock: Card or PIN.

## `LockCredTechnologies` Data Structure

Individual flags indicating which LockCredTechnology types are enabled in the LockConfig.

Maximum serialized length: 13 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `enable_PROX`                              | boolean                            | Enable LockCredTechnology: PROX
| 1 byte                           | `enable_BLUETOOTH_ANY`                     | boolean                            | Enable LockCredTechnology: BLUETOOTH_ANY
| 1 byte                           | `enable_NFC_ANY`                           | boolean                            | Enable LockCredTechnology: NFC_ANY
| 1 byte                           | `enable_DESFIRE_ANY`                       | boolean                            | Enable LockCredTechnology: DESFIRE_ANY
| 1 byte                           | `enable_ICLASS_ANY`                        | boolean                            | Enable LockCredTechnology: ICLASS_ANY
| 1 byte                           | `enable_BLUETOOTH_WAVELYNX`                | boolean                            | Enable LockCredTechnology: BLUETOOTH_WAVELYNX
| 1 byte                           | `enable_BLUETOOTH_Z9_WAVELYNX`             | boolean                            | Enable LockCredTechnology: BLUETOOTH_Z9_WAVELYNX
| 1 byte                           | `enable_NFC_GOOGLE`                        | boolean                            | Enable LockCredTechnology: NFC_GOOGLE
| 1 byte                           | `enable_NFC_APPLE`                         | boolean                            | Enable LockCredTechnology: NFC_APPLE
| 1 byte                           | `enable_DESFIRE_LEAF`                      | boolean                            | Enable LockCredTechnology: DESFIRE_LEAF
| 1 byte                           | `enable_DESFIRE_UID`                       | boolean                            | Enable LockCredTechnology: DESFIRE_UID
| 1 byte                           | `enable_ICLASS_FULL`                       | boolean                            | Enable LockCredTechnology: ICLASS_FULL
| 1 byte                           | `enable_ICLASS_UID`                        | boolean                            | Enable LockCredTechnology: ICLASS_UID

## `LockFunctionModifiers` Data Structure

The "standard" lock functions are not as standard as perhaps one would like.  There is a fair amount of variation among lock vendors as to what these functions actually do.  Therefore, we have a set of modifiers which change what the standard LockFunction does.

Maximum serialized length: 3 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `ipbUnlockDuration`                        | unsigned byte                      | If the LockFunction is one where the IPB statically unlocks the door, this is duration in seconds that the static unlock should last.  0 for N/A or indefinite.
| 2 bytes                          | `escapeAndReturnDuration`                  | 16-bit unsigned integer            | If the lock is opened from the inside, it will remain unlocked for this number of seconds, allowing a person to return if there is, say, a dangerous situation outside.  0 indicates no modification to the default behavior.  0xFFFF indicates indefinite unlock, equvalent to the "alternative fire code" (AFC)

## `LockPacketContent` Data Structure

Base class for packet content within LockPacket.


| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `contentType`                              | byte                               | Discriminator for the type of content.
| variable                         |                                            |                                    | discriminator-specific content

## `LockPaginationReq` Data Structure

Pagination specification for LockDbQuery.

Maximum serialized length: 6 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 4 bytes                          | `aboveIndex`                               | 32-bit integer                     | Requesting for records above this index
| 2 bytes                          | `pageSize`                                 | 16-bit unsigned integer            | Page size (maximum records to return)

## `LockEvtContent_None` Data Structure

Placeholder to use when there is no additional event content.

Maximum serialized length: 1 bytes
`LockEvtContent` discriminator: byte: 0

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------

## `LockEvtContent_BatteryLevel` Data Structure

Content for a battery level event: LockEvtCode.BATTERY_LEVEL

Maximum serialized length: 3 bytes
`LockEvtContent` discriminator: byte: 3

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `batteryLevel`                             | 16-bit unsigned integer            | Battery level - 0-100 - interpret as a percentage 0% to 100%.

## `LockEvtContent_CredUnid` Data Structure

Content for any event which involves a LockCred, generally DOOR_ACCESS_GRANTED.

Maximum serialized length: 6 bytes
`LockEvtContent` discriminator: byte: 1

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `credTechnology`                           | `LockCredTechnology` enum          | Technology of the LockCred.
| 4 bytes                          | `credUnid`                                 | 32-bit unsigned integer            | unid of the LockCred.

## `LockEvtContent_SchedOid` Data Structure

Additional lock content for SCHED_ACTIVE and SCHED_INACTIVE events.

Maximum serialized length: 2 bytes
`LockEvtContent` discriminator: byte: 2

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `schedOid`                                 | unsigned byte                      | LockSched oid.

## `LockEvt` Data Structure

An event transaction recorded at a Z9 Lock.  This is often referred to in wireless lock industry parlance as an "audit", but Z9 uses the term "audit" with another meaning.  "Evt" is consistent with other Z9 data modeling.

Maximum serialized length: 21 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 7 bytes                          | `dateTime`                                 | `LockDateTime_ToSecond` structure  | The UTC date and time, down to the second, that the Evt occurred.
| 1 byte                           | `evtCode`                                  | `LockEvtCode` enum                 | The code for the event.
| 7 bytes                          | `modifiers`                                | `LockEvtModifiers` structure       | Flags/modifiers for the event.
| 1 to 6 bytes                     | `content`                                  | `LockEvtContent` structure         | discriminator-based structure - LockEvtCode-specific content.

## `LockStatus` Data Structure

The (potentially real-time) status of a Z9 Lock.

Maximum serialized length: 12 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `mode`                                     | `LockMode` enum                    | Lock mode
| 1 byte                           | `tamper`                                   | boolean                            | Tamper active
| 1 byte                           | `batteryLow`                               | boolean                            | Battery low
| 1 byte                           | `batteryCritical`                          | boolean                            | Battery critical
| 1 byte                           | `unlocked`                                 | boolean                            | Unlocked
| 1 byte                           | `open`                                     | boolean                            | Open
| 1 byte                           | `forced`                                   | boolean                            | Forced open
| 1 byte                           | `held`                                     | boolean                            | Held open
| 1 byte                           | `deadboltExtended`                         | boolean                            | Deadbolt extended
| 1 byte                           | `privacy`                                  | boolean                            | Privacy mode active
| 2 bytes                          | `batteryLevel`                             | 16-bit integer                     | Battery level

## `LockTimeZone` Data Structure

A time zone, including DST transitions.

Maximum serialized length: 12 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `standardOffset`                           | 16-bit integer                     | standard offset in minutes, signed.
| 2 bytes                          | `dstOffset`                                | 16-bit integer                     | DST offset in minutes, signed.
| 4 bytes                          | `standardTransition`                       | `LockDstTransition` structure      | Date formula for when transition to standard occurs.
| 4 bytes                          | `dstTransition`                            | `LockDstTransition` structure      | Date formula for when transition to DST occurs.

## `LockCred` Data Structure

A Z9 Lock credential, for a specific Z9 lock - that is, as stored in a lock, or processed by a lock for a dynamic mobile credential presentation.

Maximum serialized length: 77 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 4 bytes                          | `unid`                                     | 32-bit unsigned integer            | unid of 0 is used to indicate a null/deleted record, when a part of a LockDbChange_Cred.  In a LockCredAuthorization, this should be set to something nonzero, because it will be in any resulting LockEvt.
| 4 bytes                          | `effective`                                | `LockDate` structure               | Local - effective at the beginning of the day
| 4 bytes                          | `expires`                                  | `LockDate` structure               | Local - expires at the end of the day
| 1 byte                           | `technology`                               | `LockCredTechnology` enum          | Credential technology
| 8 bytes                          | `accessModifiers`                          | `LockAccessModifiers` structure    | Access modifiers
| 9 bytes                          | `presentationActions`                      | `LockCredActions` structure        | Action(s) to be taken on (single) presentation of this credential.  Only meaningful for non-mobile credentials, stored in the lock db.
| 9 bytes                          | `doublePresentationActions`                | `LockCredActions` structure        | Action(s) to be taken on double presentation of this credential.  Only meaningful for non-mobile credentials, stored in the lock db.
| 14 bytes                         | `explicitActionPermissions`                | `LockDevActionPermissions` structure | Actions permitted via explicit invocation from a mobile credential.  This is not a default action declaration like presentationActions/doublePresentationActions.
| 1 byte                           | `trimBitsInLastCredByte`                   | byte                               | Number of bits to trim from the last credential byte.
| 1 byte                           | `numCredBytes`                             | unsigned byte                      | element count of next field - Number of credential bytes to follow.
| 0 to 16 elements (0 to 16 bytes) | `credBytes`                                | unsigned byte                      | Credential bytes. Note that credBytes is optional for dynamically presented mobile credentials, in a LockCredAuthorization.
| 4 elements (4 bytes)             | `pinDigitNybbles`                          | unsigned byte                      | 8 maximum pin digits, each digit encoded as 1 nybble.  Nybble 0 of byte 0 is first digit, Nybble 1 of Byte 0 is 2nd digit, etc.  0x6-0xf are used for PIN digits. 0x0 is used for the "end" of the pin digits.  No PIN at all has nybble 0 of byte 0 set to 0x0.  Using nonzero values for meaningful data is consistent with the rest of the data model.
| 2 elements (2 bytes)             | `schedMaskBytes`                           | unsigned byte                      | Schedule mask bytes. bit 0 of byte 0 is for "always", then bit n is for sched with oid n

## `LockEvtPolicy` Data Structure

A policy which specifies a LockEvtDelta for a given LockEvtCode.

Maximum serialized length: 3 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `evtCode`                                  | `LockEvtCode` enum                 | LockEvtCode to which this applies.
| 2 bytes                          | `evtDelta`                                 | `LockEvtDelta` structure           | How to modify the processing of the given LockEvtCode.

## `LockHol` Data Structure

A "holiday" or "special day"

Maximum serialized length: 13 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 6 bytes                          | `start`                                    | `LockDateTime_ToMinute` structure  | Start date/time
| 6 bytes                          | `stop`                                     | `LockDateTime_ToMinute` structure  | Stop date/time
| 1 byte                           | `holTypes`                                 | unsigned byte                      | bit mask for which holiday types this holiday is associated with

## `LockSchedElement` Data Structure

An element of a LockSched

Maximum serialized length: 5 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 bytes                          | `start`                                    | `LockTimeOfDay_ToQuarterHour` structure | Time of day this element starts
| 1 bytes                          | `stop`                                     | `LockTimeOfDay_ToQuarterHour` structure | Time of day this element ends
| 1 byte                           | `plusDays`                                 | unsigned byte                      | If the schedule spans midnight, how many days to add to stop
| 1 byte                           | `daysOfWeek`                               | byte                               | Bit 0 is Monday, Bit 6 is Sunday
| 1 byte                           | `holTypes`                                 | unsigned byte                      | 8 holiday types, one bit each.  LSB is HolType 0.

## `LockPolicyAssertion` Data Structure

An assertion that is a part of a LockSchedPolicy, or sent as a part of a LockPolicyAssertionReq.

Maximum serialized length: 7 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `mode`                                     | `LockMode` enum                    | Assert a lock mode.  Note that emergency modes are not valid for scheduling.
| 1 byte                           | `setDoorForcedMasking`                     | boolean                            | Whether to assert door forced masking
| 1 byte                           | `doorForcedMasking`                        | boolean                            | If asserting door forced masking, the value to assert
| 1 byte                           | `setDoorHeldMasking`                       | boolean                            | Whether to assert door held masking
| 1 byte                           | `doorHeldMasking`                          | boolean                            | If asserting door held masking, the value to assert
| 1 byte                           | `setPrivacy`                               | boolean                            | Whether to assert privacy mode
| 1 byte                           | `privacy`                                  | boolean                            | If asserting privacy mode, the value to assert

## `LockSchedElementPolicy` Data Structure

An element of a LockSchedPolicy, corresponding to a LockSchedElement.

Maximum serialized length: 7 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 7 bytes                          | `assertion`                                | `LockPolicyAssertion` structure    | assertion to be applied while the element is active.  Only applies to scheduled lock modes.

## `LockSchedPolicy` Data Structure

A policy which applies to/is triggered by a schedule.  Can either assert that certain things are to be true while the schedule is active, and/or, on transitions to active, take an action.  Additionally, assertions can be done on a per-element basis.  The LockPolicyPriority is implicitly SCHEDULED, for a LockSchedPolicy.

Maximum serialized length: 59 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `schedOid`                                 | unsigned byte                      | The oid (1-based index) of the LockSched
| 1 byte                           | `action`                                   | `LockDevActionType` enum           | action to be executed when element becomes active.  Only applies to scheduled lock modes.
| 1 byte                           | `numElements`                              | byte                               | element count of next field - The number of elements to follow
| 0 to 8 elements (0 to 56 bytes)  | `elements`                                 | array of `LockSchedElementPolicy`  | The elements.  These apply to the corresponding LockSchedLement in the LockSched.

## `LockSched` Data Structure

A schedule.

Maximum serialized length: 57 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 4 bytes                          | `unid`                                     | 32-bit unsigned integer            | unid of 0 is used to indicate a null/deleted record, when a part of a LockDbChange_Sched.  The unid is used in check that the schedule bits in a LockCred correspond to the same LockSched unid between the mobile device and the lock, when the LockCred is part of a LockCredAuthorization
| 6 bytes                          | `effective`                                | `LockDateTime_ToMinute` structure  | When this schedule is effective
| 6 bytes                          | `expires`                                  | `LockDateTime_ToMinute` structure  | When this schedule expires
| 1 byte                           | `numElements`                              | byte                               | element count of next field - Number of elements to follow
| 0 to 8 elements (0 to 40 bytes)  | `elements`                                 | array of `LockSchedElement`        | The schedule elements

## `LockHostGrantConfig` Data Structure

Configuration for host grant.

Maximum serialized length: 3 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `initiationMode`                           | `LockHostGrantInitiationMode` enum | Whether/when to initiate host grant
| 1 byte                           | `timeout`                                  | unsigned byte                      | Timeout in seconds, for getting a response from the host
| 1 byte                           | `fallbackMode`                             | `LockHostGrantFallbackMode` enum   | What to do if the host is unreachable, or times out

## `LockConfig` Data Structure

The configuration of the Z9 Lock.

Maximum serialized length: 137 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 13 bytes                         | `credTechnologies`                         | `LockCredTechnologies` structure   | Which LockCredTechnology types are enabled
| 1 byte                           | `function`                                 | `LockFunction` enum                | The lock function (office, classroom, etc.
| 3 bytes                          | `functionModifiers`                        | `LockFunctionModifiers` structure  | Modifiers to how the lock function actually behaves
| 1 byte                           | `strikeTime`                               | unsigned byte                      | The strike time (unlock time) in seconds
| 1 byte                           | `extendedStrikeTime`                       | unsigned byte                      | The extended strike time (unlock time) in seconds.  Used for LockCred with the extDoorTime modifier set.
| 1 byte                           | `heldTime`                                 | unsigned byte                      | The held time (propped time) in seconds
| 1 byte                           | `extendedHeldTime`                         | unsigned byte                      | The extended held time (propped time) in seconds.  Used for LockCred with the extDoorTime modifier set.
| 1 byte                           | `defaultDoorForcedMasking`                 | boolean                            | Whether to mask door forced by default
| 1 byte                           | `defaultDoorHeldMasking`                   | boolean                            | Whether to mask door held by default
| 1 byte                           | `defaultLockMode`                          | `LockMode` enum                    | The default LockMode
| 3 bytes                          | `hostGrantConfig`                          | `LockHostGrantConfig` structure    | Host grant configuration - to be able to configure for host (Hub/Controller) grant decision making
| 1 byte                           | `maxPinLength`                             | unsigned byte                      | If nonzero, this can be used to specify a more restrictive max pin length than the device supports.  The purpose of this is to allow auto-pin termination after the max length, rather than space saving.  Maximum value is 8.
| 12 bytes                         | `timeZone`                                 | `LockTimeZone` structure           | Time zone of the lock
| 1 byte                           | `numEvtPolicy`                             | unsigned byte                      | element count of next field - Number of LockEvtPolicy entries to follow
| 0 to 32 elements (0 to 96 bytes) | `evtPolicies`                              | array of `LockEvtPolicy`           | The LockEvtPolicy entries

## `LockEvtIdentifier` Data Structure

Unique identifying information in a LockEvt, used for identifying events to consume.

Maximum serialized length: 8 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 7 bytes                          | `dateTime`                                 | `LockDateTime_ToSecond` structure  | The date and time, down to the second, that the Evt occurred.
| 1 byte                           | `evtCode`                                  | `LockEvtCode` enum                 | The code for the event.

## `LockEvtIdentifierRange` Data Structure

Used to identify a range of LockEvt to consume.

Maximum serialized length: 16 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 8 bytes                          | `start`                                    | `LockEvtIdentifier` structure      | Start of range.
| 8 bytes                          | `stop`                                     | `LockEvtIdentifier` structure      | Stop of range.

## `LockIdentification` Data Structure

Identification from a Z9 Lock, or to a Z9 Lock.

Maximum serialized length: 17 bytes
`LockPacketContent` discriminator: byte: 0

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `protocolVersionMajor`                     | unsigned byte                      | Protocol version: major.
| 1 byte                           | `protocolVersionMinor`                     | unsigned byte                      | Protocol version: minor.
| 1 byte                           | `type`                                     | `LockIdentificationType` enum      | The type of device identifying itself.
| 8 bytes                          | `id`                                       | 64-bit unsigned integer            | The identifier of the device.
| 1 byte                           | `model`                                    | unsigned byte                      | Model. Only applicable when identification is from lock.  0 otherwise.
| 1 byte                           | `brand`                                    | unsigned byte                      | Brand code.
| 1 byte                           | `firmwareVersionMajor`                     | unsigned byte                      | Only applicable when identification is from lock.  0 otherwise.
| 1 byte                           | `firmwareVersionMinor`                     | unsigned byte                      | Only applicable when identification is from lock.  0 otherwise.
| 1 byte                           | `licensed`                                 | boolean                            | True if the lock's Z9 firmware is licensed.  only applicable when identification is from lock.

## `LockIdentificationResult` Data Structure

Result sent to or from a Z9 Lock in response to LockIdentification coming from the opposite direction.

Maximum serialized length: 3 bytes
`LockPacketContent` discriminator: byte: 1

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success.

## `LockDbChange_Config` Data Structure

A database change request, to a Z9 Lock - LockConfig.  This data structure contains all the data of this type, and is considered a "replace" operation, not an "add" or limited "update" operation.  The lock should respond with LockDbChangeResp.

Maximum serialized length: 147 bytes
`LockPacketContent` discriminator: byte: 2

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 8 bytes                          | `requestId`                                | 64-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.  a requestId that is smaller than one already processed by the lock, is to be ignored, because it is out of date.
| 1 byte                           | `updateConfigPresent`                      | byte                               | element count of next field - Whether the updateConfig field is present.
| 0 to 1 elements (0 to 137 bytes) | `updateConfig`                             | array of `LockConfig`              | The Z9 Lock configuration to update.

## `LockDbChangeResp` Data Structure

Response to LockDbChange_*, from a Z9 Lock.

Maximum serialized length: 11 bytes
`LockPacketContent` discriminator: byte: 3

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 8 bytes                          | `requestId`                                | 64-bit integer                     | Matches the requestId of the LockDbChange_*.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.

## `LockEvtControl` Data Structure

Event control request, to a Z9 Lock.

Maximum serialized length: 19 bytes
`LockPacketContent` discriminator: byte: 4

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `priority`                                 | boolean                            | Whether priority events are being requested/consumed, or non-priority.  Applies to both sendOneBatch and consume.
| 1 byte                           | `sendOneBatch`                             | boolean                            | if true, a single batch of events is being requested.
| 16 bytes                         | `consume`                                  | `LockEvtIdentifierRange` structure | if not all zeros, this range of events is to be marked as consumed.

## `LockEvtBatch` Data Structure

A batch of events, from a Z9 Lock, in response to a request to send a batch in LockEvtControl.

Maximum serialized length: 675 bytes
`LockPacketContent` discriminator: byte: 5

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `priority`                                 | boolean                            | if true, this batch contains only priority events - otherwise, only non-priority.
| 1 byte                           | `evtCount`                                 | unsigned byte                      | element count of next field - Number of events to follow.
| 0 to 32 elements (0 to 672 bytes) | `evt`                                      | array of `LockEvt`                 | Events.

## `LockDevStateRecordControl` Data Structure

Request to a Z9 Lock to send its current state.

Maximum serialized length: 1 bytes
`LockPacketContent` discriminator: byte: 6

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------

## `LockDevStateRecord` Data Structure

State of the Z9 Lock, sent by a lock in response to LockDevStateRecordControl.

Maximum serialized length: 13 bytes
`LockPacketContent` discriminator: byte: 7

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 12 bytes                         | `status`                                   | `LockStatus` structure             | Lock status.

## `LockDateTimeConfig` Data Structure

Full date/time with optional time zone information, used when either getting/setting the time on the lock.

Maximum serialized length: 20 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 7 bytes                          | `dateTime`                                 | `LockDateTime_ToSecond` structure  | Date/Time, UTC. All binary 0s is the equivalent of null/not present.
| 1 byte                           | `timeZonePresent`                          | boolean                            | If true, the time zone is present.  This is needed because an all binary 0s LockTimeZone is UTC.
| 12 bytes                         | `timeZone`                                 | `LockTimeZone` structure           | Time zone.

## `LockGetTimeReq` Data Structure

Request to a Z9 Lock to send its current time.

Maximum serialized length: 1 bytes
`LockPacketContent` discriminator: byte: 8

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------

## `LockGetTimeResp` Data Structure

Date/time of the Z9 Lock, sent by the lock in response to LockGetTimeReq.

Maximum serialized length: 21 bytes
`LockPacketContent` discriminator: byte: 9

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 20 bytes                         | `dateTimeConfig`                           | `LockDateTimeConfig` structure     | Date/time of the lock.

## `LockSetTimeReq` Data Structure

Request to a Z9 Lock to set its current time and time zone.  Made by mobile device to lock.  Must be preceded by an admin LockCredAuthorization

Maximum serialized length: 21 bytes
`LockPacketContent` discriminator: byte: 10

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 20 bytes                         | `dateTimeConfig`                           | `LockDateTimeConfig` structure     | The date/time configuration to set.

## `LockSetTimeResp` Data Structure

Sent by the Z9 Lock in response to LockSetTimeReq.

Maximum serialized length: 3 bytes
`LockPacketContent` discriminator: byte: 11

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.

## `LockPullFileChunkReq` Data Structure

Request to a Z9 Lock, to pull a chunk of a file.

Maximum serialized length: 15 bytes
`LockPacketContent` discriminator: byte: 14

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit unsigned integer            | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.
| 1 byte                           | `category`                                 | `LockFileCategory` enum            | File category.
| 1 byte                           | `id`                                       | `LockFileIdentifier` enum          | ID of actual file within category.
| 8 bytes                          | `offset`                                   | 64-bit unsigned integer            | Offset into file.
| 2 bytes                          | `maxLength`                                | 16-bit unsigned integer            | Maximum length of chunk to pull.

## `LockPullFileChunkResp` Data Structure

Z9 Lock's response to LockPullFileChunkReq.

Maximum serialized length: 808 bytes
`LockPacketContent` discriminator: byte: 15

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit unsigned integer            | corresponds to LockPullFileChunkReq.requestId.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.
| 1 byte                           | `eof`                                      | boolean                            | if true, this is the last chunk (EOF).
| 2 bytes                          | `bytesCount`                               | 16-bit integer                     | element count of next field - count of bytes.
| 0 to 800 elements (0 to 800 bytes) | `bytes`                                    | unsigned byte                      | Actual data as byte array.

## `LockPushFileChunkReq` Data Structure

Request to a Z9 Lock, to push a chunk of a file.

Maximum serialized length: 816 bytes
`LockPacketContent` discriminator: byte: 12

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit unsigned integer            | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.
| 1 byte                           | `category`                                 | `LockFileCategory` enum            | File category.
| 1 byte                           | `id`                                       | `LockFileIdentifier` enum          | ID of actual file within category.
| 8 bytes                          | `offset`                                   | 64-bit unsigned integer            | offset within the file.
| 1 byte                           | `eof`                                      | boolean                            | whether this is the last chunk (EOF).
| 2 bytes                          | `bytesCount`                               | 16-bit integer                     | element count of next field - count of bytes.
| 0 to 800 elements (0 to 800 bytes) | `bytes`                                    | unsigned byte                      | Actual data as byte array.

## `LockPushFileChunkResp` Data Structure

Maximum serialized length: 5 bytes
`LockPacketContent` discriminator: byte: 13

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit unsigned integer            | corresponds to LockPushFileChunkReq.requestId.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.

## `LockUpgradeReq` Data Structure

Request to a Z9 Lock to perform a software (firmware) upgrade based on a file that was previously transferred using LockPushFileChunkReq/LockPushFileChunkResp.

Maximum serialized length: 6 bytes
`LockPacketContent` discriminator: byte: 16

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit unsigned integer            | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.
| 1 byte                           | `fileId`                                   | `LockFileIdentifier` enum          | ID of actual file within (UPGRADE) category.
| 2 bytes                          | `rebootDelay`                              | 16-bit unsigned integer            | Reboot delay.

## `LockUpgradeResp` Data Structure

Maximum serialized length: 5 bytes
`LockPacketContent` discriminator: byte: 17

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit unsigned integer            | corresponds to LockPullFileChunkReq.requestId.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.

## `LockDbQuery` Data Structure

A database query request, to a Z9 Lock.

Maximum serialized length: 14 bytes
`LockPacketContent` discriminator: byte: 18

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.
| 1 byte                           | `queryConfig`                              | boolean                            | if true, include LockConfig in response.
| 1 byte                           | `queryHol`                                 | boolean                            | if true, include LockHol in response.
| 1 byte                           | `querySched`                               | boolean                            | if true, include LockSched in response.
| 1 byte                           | `querySchedPolicy`                         | boolean                            | if true, include LockSchedPolicy in response.
| 1 byte                           | `queryCred`                                | boolean                            | if true, include LockCred in response.
| 6 bytes                          | `paginationCred`                           | `LockPaginationReq` structure      | if queryCred is true, specification of which page of data to include in response.

## `LockDbQueryResp_Config` Data Structure

Response to LockDbQuery, from a Z9 Lock - LockConfig.

Maximum serialized length: 143 bytes
`LockPacketContent` discriminator: byte: 19

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | Matches the requestId of the LockDbQuery.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.
| 1 byte                           | `configPresent`                            | byte                               | element count of next field - Whether LockConfig is present.
| 0 to 1 elements (0 to 137 bytes) | `config`                                   | array of `LockConfig`              | LockConfig, if present.

## `LockHostGrantReq` Data Structure

Host grant request from a Z9 Lock - the lock requesting the host to make an access grant/deny decision.

Maximum serialized length: 83 bytes
`LockPacketContent` discriminator: byte: 20

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.
| 1 byte                           | `type`                                     | `LockHostGrantReqType` enum        | The type of request.
| 1 byte                           | `lockMode`                                 | `LockMode` enum                    | The LockMode in effect at the time of the request.
| 1 byte                           | `privacy`                                  | boolean                            | Whether privacy is active at the time of the request.
| 77 bytes                         | `rawCred`                                  | `LockCred` structure               | The raw credential presented.  May not have all properties populated.

## `LockHostGrantResp` Data Structure

Z9 Lock response to LockHostGrantReq.

Maximum serialized length: 83 bytes
`LockPacketContent` discriminator: byte: 21

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | corresponds to LockHostGrantReq.requestId.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.
| 77 bytes                         | `dbCred`                                   | `LockCred` structure               | credential looked up in host's db.
| 1 byte                           | `evtCode`                                  | `LockEvtCode` enum                 | granted/denied response.

## `LockDevActionReq` Data Structure

Request to a Z9 Lock to perform an action.

Maximum serialized length: 7 bytes
`LockPacketContent` discriminator: byte: 22

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.
| 1 byte                           | `actionType`                               | `LockDevActionType` enum           | the action to perform.
| 2 bytes                          | `durationSecs`                             | 16-bit integer                     | If nonzero, the duration in seconds that applies to the action.  Zero indicates indefinite.
| 1 byte                           | `policyPriority`                           | `LockPolicyPriority` enum          | The priority at which the action is applied.

## `LockDevActionResp` Data Structure

Sent by the Z9 Lock in response to LockDevActionReq.

Maximum serialized length: 5 bytes
`LockPacketContent` discriminator: byte: 23

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | Matches the requestId of the LockDevActionReq.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.

## `LockPolicyAssertionReq` Data Structure

Request to a Z9 Lock to assert a policy assertion.

Maximum serialized length: 13 bytes
`LockPacketContent` discriminator: byte: 24

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.
| 1 byte                           | `priority`                                 | `LockPolicyPriority` enum          | The priority at which to assert the assertion.
| 1 byte                           | `state`                                    | boolean                            | True to assert, false to unassert.
| 1 byte                           | `temporary`                                | boolean                            | True if temporary.
| 7 bytes                          | `assertion`                                | `LockPolicyAssertion` structure    | The assertion itself.

## `LockPolicyAssertionResp` Data Structure

Sent by the Z9 Lock in response to LockPolicyAssertionReq.

Maximum serialized length: 5 bytes
`LockPacketContent` discriminator: byte: 25

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | Matches the requestId of the LockPolicyAssertionReq.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.

## `LockConnectionTermination` Data Structure

Graceful connection termination to a Z9 Lock.

Maximum serialized length: 1 bytes
`LockPacketContent` discriminator: byte: 26

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------

## `LockDbChange_Hol` Data Structure

A database change request, to a Z9 Lock - LockHol.  This data structure contains all the data of this type, and is considered a "replace" operation, not an "add" or limited "update" operation.  The lock should respond with LockDbChangeResp.

Maximum serialized length: 426 bytes
`LockPacketContent` discriminator: byte: 27

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 8 bytes                          | `requestId`                                | 64-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.  a requestId that is smaller than one already processed by the lock, is to be ignored, because it is out of date.
| 1 byte                           | `numHol`                                   | unsigned byte                      | element count of next field - Number of holidays to follow.
| 0 to 32 elements (0 to 416 bytes) | `hol`                                      | array of `LockHol`                 | Holidays. Order in this array is the index, or "oid".  First one starts at 1.

## `LockDbChange_Sched` Data Structure

A database change request, to a Z9 Lock - LockSched.  This is always all schedules, full replace.  The lock should respond with LockDbChangeResp.

Maximum serialized length: 865 bytes
`LockPacketContent` discriminator: byte: 28

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 8 bytes                          | `requestId`                                | 64-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.  a requestId that is smaller than one already processed by the lock, is to be ignored, because it is out of date.
| 1 byte                           | `numSched`                                 | unsigned byte                      | element count of next field - Number of schedules to follow.
| 0 to 15 elements (0 to 855 bytes) | `sched`                                    | array of `LockSched`               | Schedules.  Order in this array is the index, or "oid".  First one starts at 1.

## `LockDbChange_SchedPolicy` Data Structure

A database change request, to a Z9 Lock - LockSchedPolicy.  This data structure contains all the data of this type, and is considered a "replace" operation, not an "add" or limited "update" operation.  The lock should respond with LockDbChangeResp.

Maximum serialized length: 482 bytes
`LockPacketContent` discriminator: byte: 29

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 8 bytes                          | `requestId`                                | 64-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.  a requestId that is smaller than one already processed by the lock, is to be ignored, because it is out of date.
| 1 byte                           | `numSchedPolicy`                           | unsigned byte                      | element count of next field - Number of LockSchedPolicy entries to follow.
| 0 to 8 elements (0 to 472 bytes) | `schedPolicy`                              | array of `LockSchedPolicy`         | LockSchedPolicy entries.  Order in this array is the index, or "oid".  First one starts at 1.

## `LockDbChange_Cred` Data Structure

A database change request, to a Z9 Lock - LockCred.  This is not transmitted over NOC, it only comes from a hub/controller in an online configuration.  Unlike other "DbChange_*" data structures, this is not used as a "full replace", but is incremental.  "delete all" is an explicit attribute in this case.  The lock should respond with LockDbChangeResp.

Maximum serialized length: 1243 bytes
`LockPacketContent` discriminator: byte: 30

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 8 bytes                          | `requestId`                                | 64-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.  Unlike the other "DbChange_*" data structures, the requestId is not used to ignore older requests.
| 1 byte                           | `deleteAllCred`                            | boolean                            | delete all LockCred.  Applied before explicit upsert/delete.
| 1 byte                           | `numUpsertOrDeleteCred`                    | unsigned byte                      | element count of next field - Number of upsert/delete LockCred elements to follow.
| 0 to 16 elements (0 to 1232 bytes) | `upsertOrDeleteCred`                       | array of `LockCred`                | Upsert/delete LockCred elements.  Note that a LockCred with only a unid and everything else 0 will be considered a delete.

## `LockDbQueryResp_Hol` Data Structure

Response to LockDbQuery, from a Z9 Lock - LockHol.

Maximum serialized length: 838 bytes
`LockPacketContent` discriminator: byte: 31

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | Matches the requestId of the LockDbQuery.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.
| 1 byte                           | `numHol`                                   | unsigned byte                      | element count of next field - Number of holdays to follow.
| 0 to 64 elements (0 to 832 bytes) | `hol`                                      | array of `LockHol`                 | Holidays.

## `LockDbQueryResp_Sched` Data Structure

Response to LockDbQuery, from a Z9 Lock - LockSched.

Maximum serialized length: 861 bytes
`LockPacketContent` discriminator: byte: 32

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | Matches the requestId of the LockDbQuery.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.
| 1 byte                           | `numSched`                                 | unsigned byte                      | element count of next field - Number of schedules to follow.
| 0 to 15 elements (0 to 855 bytes) | `sched`                                    | array of `LockSched`               | Schedules.

## `LockDbQueryResp_SchedPolicy` Data Structure

Response to LockDbQuery, from a Z9 Lock - LockSchedPolicy.

Maximum serialized length: 478 bytes
`LockPacketContent` discriminator: byte: 33

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | Matches the requestId of the LockDbQuery.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.
| 1 byte                           | `numSchedPolicy`                           | unsigned byte                      | element count of next field - Number of LockSchedPolicy to follow.
| 0 to 8 elements (0 to 472 bytes) | `schedPolicy`                              | array of `LockSchedPolicy`         | LockSchedPolicy.

## `LockDbQueryResp_Cred` Data Structure

Response to LockDbQuery, from a Z9 Lock - LockCred.

Maximum serialized length: 1238 bytes
`LockPacketContent` discriminator: byte: 34

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | Matches the requestId of the LockDbQuery.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.
| 1 byte                           | `numCred`                                  | unsigned byte                      | element count of next field - Number of credentials to follow.
| 0 to 16 elements (0 to 1232 bytes) | `cred`                                     | array of `LockCred`                | Credentials.

## `LockCredAuthorization` Data Structure

A LockCred authorization from the authoritative source, for a dynamic credential presentation.

Maximum serialized length: 172 bytes
`LockPacketContent` discriminator: byte: 35

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 8 bytes                          | `mobileId`                                 | 64-bit unsigned integer            | The id of the mobile device (generally phone).
| 8 bytes                          | `lockId`                                   | 64-bit unsigned integer            | The id of the Z9 Lock.
| 77 bytes                         | `cred`                                     | `LockCred` structure               | The contents of the credential itself.
| 1 byte                           | `numSchedUnids`                            | unsigned byte                      | element count of next field - Number of schedule unids to follow.
| 0 to 15 elements (0 to 60 bytes) | `schedUnids`                               | 32-bit unsigned integer            | Schedule unids.  Allows the lock to correlate the schedule bits in the LockCred with their current unid values to ensure schedule indexes are not misinterpreted due to delayed configuration data.  Index 0 is the first definable schedule (oid=2).
| 1 byte                           | `numSharedSecretBytes`                     | byte                               | element count of next field - Number of shared secret bytes to follow.
| 0 to 16 elements (0 to 16 bytes) | `sharedSecretBytes`                        | unsigned byte                      | Shared secret that matches the shared secret in the GroupedCredentialElement as served up by the authoritative source (cloud) to the mobile device.  This is generated dynamically every time the authoritative source (cloud) serves up a GroupedCredential.  This is used as a shared secret between the mobile device and the lock, for all encrypting requests generated by the mobile device that are using the LockCredAuthorization as the authorization.  This includes LockAccessReq and LockDevActionReq.  128 bits.

## `LockAccessReq` Data Structure

Request to a Z9 Lock for access.

Maximum serialized length: 11 bytes
`LockPacketContent` discriminator: byte: 37

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | request id for this request.  Each request should have a different id (simply incrementing), wrapping around to 0 after reaching the maximum value.
| 8 bytes                          | `mobileId`                                 | 64-bit unsigned integer            | Potentially redundant - id of the mobile device requesting access.

## `LockAccessResp` Data Structure

Sent by the Z9 Lock in response to LockAccessReq.

Maximum serialized length: 6 bytes
`LockPacketContent` discriminator: byte: 38

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `requestId`                                | 16-bit integer                     | Matches the requestId of the LockAccessReq.
| 2 bytes                          | `errorCode`                                | 16-bit integer                     | 0 indicates success, nonzero for error.
| 1 byte                           | `granted`                                  | boolean                            | True if access granted, false if denied.

## `LockPublicKeyExchange` Data Structure

A public key either from the authoritative source, or from a Z9 Lock.

Maximum serialized length: 67 bytes
`LockPacketContent` discriminator: byte: 41

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `numPublicKeyBytes`                        | byte                               | element count of next field - Number of public key bytes to follow.
| 0 to 65 elements (0 to 65 bytes) | `publicKeyBytes`                           | unsigned byte                      | The public key bytes.

## `LockMobileBleChallengeNonce` Data Structure

A BLE challenge nonce, from the Z9 Lock to a mobile device.  This is only needed when using TCP/IP between the lock and the mobile device for virtual testing.

Maximum serialized length: 18 bytes
`LockPacketContent` discriminator: byte: 43

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `numNonceBytes`                            | byte                               | element count of next field - Number of nonce bytes to follow.
| 0 to 16 elements (0 to 16 bytes) | `nonceBytes`                               | unsigned byte                      | The nonce bytes.

## `LockBundleHeader` Data Structure

A bundle consists of a LockBundleHeader, followed by one or more LockPacket.  Note that the LockBundleHeader itself is also contained within a LockPacket.

Maximum serialized length: 37 bytes
`LockPacketContent` discriminator: byte: 40

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 1 byte                           | `origin`                                   | `LockIdentificationType` enum      | The originating source of the packets
| 1 byte                           | `intermediary`                             | `LockIdentificationType` enum      | The device that is actually transmitting the data.  Set to NONE for N/A or intermediary same as source (no intermediary).
| 1 byte                           | `destination`                              | `LockIdentificationType` enum      | The destination for the packets.
| 8 bytes                          | `originId`                                 | 64-bit unsigned integer            | The id of the originating source, 0 for authoritative source, also generally 0 for hub/controller, to indicate default paired hub/controller.
| 8 bytes                          | `intermediaryId`                           | 64-bit unsigned integer            | The id of the intermediary. 0 if N/A.
| 8 bytes                          | `destinationId`                            | 64-bit unsigned integer            | The id of the destination, 0 for authoritative source.  Also 0 in the special case of a bundle containing LockIdentification, where the LockIdentification is the first bundle sent (by the lock) before identity is established.
| 7 bytes                          | `expires`                                  | `LockDateTime_ToSecond` structure  | When this bundle expires, UTC.  0 for never expires, or N/A.
| 1 byte                           | `opaque`                                   | boolean                            | if true, this is an opaque bundle, which means it is followed by LockOpaqueContent packets, encrypted by the origin.
| 1 byte                           | `packetCount`                              | byte                               | The number of LockPacket that follow, excluding the packet containing the header.

## `LockOpaqueContent` Data Structure

Opaque (encoded) content not intended for the intermediate (mobile device) transmitting this between origin and destination.

Maximum serialized length: 1026 bytes
`LockPacketContent` discriminator: byte: 42

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `numOpaqueBytes`                           | 16-bit integer                     | element count of next field - Number of opaque bytes
| 0 to 1023 elements (0 to 1023 bytes) | `opaqueBytes`                              | unsigned byte                      | Opaque (encrypted) bytes

## `LockPacket` Data Structure

A single "packet" to or from a Z9 Lock.

Maximum serialized length: 1247 bytes

| Size                             | Name                                       | Type                               | Description
| -------------------------------- | ------------------------------------------ | ---------------------------------- | -----------
| 2 bytes                          | `headerBytes`                              | 16-bit integer                     | static value: always 31289 - Fixed header bytes for a Z9 Lock packet
| 2 bytes                          | `bytecount`                                | 16-bit integer                     | Total bytecount of the serialized Z9 Lock packet, including the header bytes and bytecount itself.
| 1 to 1243 bytes                  | `content`                                  | `LockPacketContent` structure      | discriminator-based structure - Variable content of the Z9 Lock packet, dependent on the discriminator within the content itself.

