// Copyright (C) 2011-Infinity Z9 Security. All rights reserved.

/**
 * @file Crc16.h
 * @brief CRC 16 algorithm
 */

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

uint16_t Crc16_updateCrc   (uint16_t current, uint8_t c);
uint16_t Crc16_calculateCRC(const uint8_t *buf, int offset, int len);

#define Crc16_INITIAL_VALUE 0x1d0fU

#ifdef __cplusplus
}
#endif
