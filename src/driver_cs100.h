/**
 * Copyright (c) 2015 - present LibDriver All rights reserved
 * 
 * The MIT License (MIT)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE. 
 *
 * @file      driver_cs100.h
 * @brief     driver cs100 header file
 * @version   1.0.0
 * @author    Shifeng Li
 * @date      2024-07-30
 *
 * <h3>history</h3>
 * <table>
 * <tr><th>Date        <th>Version  <th>Author      <th>Description
 * <tr><td>2024/07/30  <td>1.0      <td>Shifeng Li  <td>first upload
 * </table>
 */

#ifndef DRIVER_CS100_H
#define DRIVER_CS100_H

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"{
#endif

/**
 * @defgroup cs100_driver cs100 driver function
 * @brief    cs100 driver modules
 * @{
 */

/**
 * @addtogroup cs100_base_driver
 * @{
 */

/**
 * @brief cs100 read retry times definition
 */
#ifndef CS100_READ_RETRY_TIMES
    #define CS100_READ_RETRY_TIMES        3        /**< retry 3 times */
#endif

/**
 * @brief cs100 time structure definition
 */
typedef struct cs100_time_s
{
    uint64_t microsecond;        /**< microsecond */
    uint32_t millisecond;        /**< millisecond */
} cs100_time_t;

/**
 * @brief cs100 handle structure definition
 */
typedef struct cs100_handle_s
{
    uint8_t (*trig_init)(void);                            /**< point to a trig_init function address */
    uint8_t (*trig_deinit)(void);                          /**< point to a trig_deinit function address */
    uint8_t (*trig_write)(uint8_t value);                  /**< point to a trig_write function address */
    uint8_t (*echo_init)(void);                            /**< point to an echo_init function address */
    uint8_t (*echo_deinit)(void);                          /**< point to an echo_deinit function address */
    uint8_t (*echo_read)(uint8_t *value);                  /**< point to an echo_read function address */
    uint8_t (*timestamp_read)(cs100_time_t *time);         /**< point to a timestamp_read function address */
    void (*delay_us)(uint32_t ms);                         /**< point to a delay_us function address */
    void (*delay_ms)(uint32_t ms);                         /**< point to a delay_ms function address */
    void (*debug_print)(const char *const fmt, ...);       /**< point to a debug_print function address */
    uint8_t inited;                                        /**< inited flag */
} cs100_handle_t;

/**
 * @brief cs100 information structure definition
 */
typedef struct cs100_info_s
{
    char chip_name[32];                /**< chip name */
    char manufacturer_name[32];        /**< manufacturer name */
    char interface[8];                 /**< chip interface name */
    float supply_voltage_min_v;        /**< chip min supply voltage */
    float supply_voltage_max_v;        /**< chip max supply voltage */
    float max_current_ma;              /**< chip max current */
    float temperature_min;             /**< chip min operating temperature */
    float temperature_max;             /**< chip max operating temperature */
    uint32_t driver_version;           /**< driver version */
} cs100_info_t;

/**
 * @}
 */

/**
 * @defgroup cs100_link_driver cs100 link driver function
 * @brief    cs100 link driver modules
 * @ingroup  cs100_driver
 * @{
 */

/**
 * @brief     initialize cs100_handle_t structure
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] STRUCTURE is cs100_handle_t
 * @note      none
 */
#define DRIVER_CS100_LINK_INIT(HANDLE, STRUCTURE)      memset(HANDLE, 0, sizeof(STRUCTURE))

/**
 * @brief     link trig_init function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to a trig_init function address
 * @note      none
 */
#define DRIVER_CS100_LINK_TRIG_INIT(HANDLE, FUC)      (HANDLE)->trig_init = FUC

/**
 * @brief     link trig_deinit function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to a trig_deinit function address
 * @note      none
 */
#define DRIVER_CS100_LINK_TRIG_DEINIT(HANDLE, FUC)    (HANDLE)->trig_deinit = FUC

/**
 * @brief     link trig_write function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to a trig_write function address
 * @note      none
 */
#define DRIVER_CS100_LINK_TRIG_WRITE(HANDLE, FUC)     (HANDLE)->trig_write = FUC

/**
 * @brief     link echo_init function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to an echo_init function address
 * @note      none
 */
#define DRIVER_CS100_LINK_ECHO_INIT(HANDLE, FUC)      (HANDLE)->echo_init = FUC

/**
 * @brief     link echo_deinit function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to an echo_deinit function address
 * @note      none
 */
#define DRIVER_CS100_LINK_ECHO_DEINIT(HANDLE, FUC)    (HANDLE)->echo_deinit = FUC

/**
 * @brief     link echo_read function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to an echo_read function address
 * @note      none
 */
#define DRIVER_CS100_LINK_ECHO_WRITE(HANDLE, FUC)     (HANDLE)->echo_read = FUC

/**
 * @brief     link timestamp_read function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to a timestamp_read function address
 * @note      none
 */
#define DRIVER_CS100_LINK_TIMESTAMP_READ(HANDLE, FUC) (HANDLE)->timestamp_read = FUC

/**
 * @brief     link delay_ms function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to a delay_ms function address
 * @note      none
 */
#define DRIVER_CS100_LINK_DELAY_MS(HANDLE, FUC)       (HANDLE)->delay_ms = FUC

/**
 * @brief     link delay_us function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to a delay_us function address
 * @note      none
 */
#define DRIVER_CS100_LINK_DELAY_US(HANDLE, FUC)       (HANDLE)->delay_us = FUC

/**
 * @brief     link debug_print function
 * @param[in] HANDLE points to an cs100 handle structure
 * @param[in] FUC points to a debug_print function address
 * @note      none
 */
#define DRIVER_CS100_LINK_DEBUG_PRINT(HANDLE, FUC)    (HANDLE)->debug_print = FUC

/**
 * @}
 */

/**
 * @defgroup cs100_base_driver cs100 base driver function
 * @brief    cs100 base driver modules
 * @ingroup  cs100_driver
 * @{
 */

/**
 * @brief      get chip's information
 * @param[out] *info points to an cs100 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t cs100_info(cs100_info_t *info);

/**
 * @brief     initialize the chip
 * @param[in] *handle points to an cs100 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 trig or echo init failed
 *            - 2 handle is NULL
 *            - 3 linked functions is NULL
 * @note      none
 */
uint8_t cs100_init(cs100_handle_t *handle);

/**
 * @brief     close the chip
 * @param[in] *handle points to an cs100 handle structure
 * @return    status code
 *            - 0 success
 *            - 1 trig or echo deinit failed
 *            - 2 handle is NULL
 *            - 3 handle is not initialized
 * @note      none
 */
uint8_t cs100_deinit(cs100_handle_t *handle);

/**
 * @brief      read the distance
 * @param[in]  *handle points to an cs100 handle structure
 * @param[out] *time_us points to a us buffer
 * @param[out] *m points to a distance buffer
 * @return     status code
 *             - 0 success
 *             - 1 read failed
 *             - 2 handle is NULL
 *             - 3 handle is not initialized
 * @note       none
 */
uint8_t cs100_read(cs100_handle_t *handle, uint32_t *time_us, float *m);

/**
 * @}
 */

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif
