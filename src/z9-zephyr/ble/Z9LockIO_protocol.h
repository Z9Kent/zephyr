
#include "Z9LockIO_accessReq.h"
#include "Z9LockIO_bundleHeader.h"
#include "Z9LockIO_credAuthorization.h"
#include "Z9LockIO_dbChange.h"
#include "Z9LockIO_eventControl.h"
#include "Z9LockIO_keyExchange.h"
#include "Z9LockIO_opaqueContent.h"

#include <KernelCharacterBuffer.h>
#include <cinttypes>
#include <zephyr/bluetooth/conn.h>

#pragma once

uint64_t read64(uint8_t *p);
uint32_t read32(uint8_t *p);
uint8_t *write64(uint8_t *p, uint64_t value);

void z9lockio_recv(KCB& kcb);