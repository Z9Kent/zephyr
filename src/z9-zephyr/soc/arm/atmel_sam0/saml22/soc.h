/* Copyright (c) 2021 Argentum Systems Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _ATMEL_SAML_SOC_H_
#define _ATMEL_SAML_SOC_H_

#ifndef _ASMLANGUAGE

#define DONT_USE_CMSIS_INIT

#if defined(CONFIG_SOC_PART_NUMBER_SAML22G16A)
#include <saml22g16a.h>
#elif defined(CONFIG_SOC_PART_NUMBER_SAML22G17A)
#include <saml22g17a.h>
#elif defined(CONFIG_SOC_PART_NUMBER_SAML22G18A)
#include <saml22g18a.h>
#elif defined(CONFIG_SOC_PART_NUMBER_SAML22J16A)
#include <saml22j16a.h>
#elif defined(CONFIG_SOC_PART_NUMBER_SAML22J17A)
#include <saml22j17a.h>
#elif defined(CONFIG_SOC_PART_NUMBER_SAML22J18A)
#include <saml22j18a.h>
#elif defined(CONFIG_SOC_PART_NUMBER_SAML22N16A)
#include <saml22n16a.h>
#elif defined(CONFIG_SOC_PART_NUMBER_SAML22N17A)
#include <saml22n17a.h>
#elif defined(CONFIG_SOC_PART_NUMBER_SAML22N18A)
#include <saml22n18a.h>
#else
#error Library does not support the specified device.
#endif

#endif /* _ASMLANGUAGE */

#define ADC_SAM0_REFERENCE_ENABLE_PROTECTED

#include "adc_fixup_sam0.h"
#include "../common/soc_port.h"
#include "../common/atmel_sam0_dt.h"

/** Processor Clock (HCLK) Frequency */
#define SOC_ATMEL_SAM0_HCLK_FREQ_HZ ATMEL_SAM0_DT_CPU_CLK_FREQ_HZ

/** Master Clock (MCK) Frequency */
#define SOC_ATMEL_SAM0_MCK_FREQ_HZ SOC_ATMEL_SAM0_HCLK_FREQ_HZ
#define SOC_ATMEL_SAM0_OSC32K_FREQ_HZ 32768
#define SOC_ATMEL_SAM0_XOSC32K_FREQ_HZ 32768
#define SOC_ATMEL_SAM0_OSC16M_FREQ_HZ 16000000
#define SOC_ATMEL_SAM0_GCLK0_FREQ_HZ SOC_ATMEL_SAM0_MCK_FREQ_HZ
#define SOC_ATMEL_SAM0_GCLK3_FREQ_HZ 24000000

#if defined(CONFIG_SOC_ATMEL_SAML_OPENLOOP_AS_MAIN)
#define SOC_ATMEL_SAM0_GCLK1_FREQ_HZ 0
#elif defined(CONFIG_SOC_ATMEL_SAML_OSC32K_AS_MAIN)
#define SOC_ATMEL_SAM0_GCLK1_FREQ_HZ SOC_ATMEL_SAM0_OSC32K_FREQ_HZ
#elif defined(CONFIG_SOC_ATMEL_SAML_XOSC32K_AS_MAIN)
#define SOC_ATMEL_SAM0_GCLK1_FREQ_HZ SOC_ATMEL_SAM0_XOSC32K_FREQ_HZ
#elif defined(CONFIG_SOC_ATMEL_SAML_OSC16M_AS_MAIN)
#define SOC_ATMEL_SAM0_GCLK1_FREQ_HZ SOC_ATMEL_SAM0_OSC16M_FREQ_HZ
#else
#error Unsupported GCLK1 clock source.
#endif

#define SOC_ATMEL_SAM0_APBA_FREQ_HZ SOC_ATMEL_SAM0_MCK_FREQ_HZ
#define SOC_ATMEL_SAM0_APBB_FREQ_HZ SOC_ATMEL_SAM0_MCK_FREQ_HZ
#define SOC_ATMEL_SAM0_APBC_FREQ_HZ SOC_ATMEL_SAM0_MCK_FREQ_HZ

#endif /* _ATMEL_SAML_SOC_H_ */
