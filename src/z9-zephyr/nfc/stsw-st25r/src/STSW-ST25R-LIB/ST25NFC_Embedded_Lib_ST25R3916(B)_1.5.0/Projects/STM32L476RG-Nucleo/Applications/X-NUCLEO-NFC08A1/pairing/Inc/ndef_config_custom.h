/******************************************************************************
  * @attention
  *
  * COPYRIGHT 2020 STMicroelectronics, all rights reserved
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
******************************************************************************/

/*
 *      PROJECT:   NDEF firmware
 *      Revision:
 *      LANGUAGE:  ISO C99
 */

/*! \file
 *
 *  \author
 *
 *  \brief NDEF custom config header file
 *
 * This file allows to select which NDEF features to use.
 *
 * \addtogroup NDEF
 * @{
 *
 */

#ifndef NDEF_CONFIG_CUSTOM_H
#define NDEF_CONFIG_CUSTOM_H


/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */


/*
 ******************************************************************************
 * GLOBAL DEFINES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * NDEF FEATURES CONFIGURATION
 ******************************************************************************
 */


#define NDEF_FEATURE_FULL_API                  true       /*!< Support Write, Format, Check Presence, set Read-only in addition to the Read feature */

#define NDEF_TYPE_BLUETOOTH_SUPPORT            true       /*!< Support Bluetooth types                     */
#define NDEF_TYPE_WIFI_SUPPORT                 true       /*!< Support Wifi type                           */

#endif

/**
  * @}
  *
  */
