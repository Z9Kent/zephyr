// Z9LockIO_keyExchange.h

#include "z9lockio_ble.h"
#include "Z9LockIOProtocol_Current.h"

#include <KernelCharacterBuffer.h>
#pragma once

using namespace z9;
//using namespace z9::protocols;
//using z9::protocols::z9lockio::getFormatter;

extern LockBundleHeader lastHeader;

// Entrypoint for received message
void Z9LockIO_bundleHeader(KCB& kcb, uint8_t key);

// create message for transmission
KCB *Z9LockIO_createBundleHeader(uint8_t discriminator, 
                                bool opaque = true, bool toIntermediate = false, uint8_t count = 1);

// finish creating bundle: sizes + encryption
void Z9LockIO_sendBundle(KCB&);