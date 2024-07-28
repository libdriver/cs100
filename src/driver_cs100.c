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
 * @file      driver_cs100.c
 * @brief     driver cs100 source file
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

#include "driver_cs100.h"

/**
 * @brief chip information definition
 */
#define CHIP_NAME                 "angoSense CS100"        /**< chip name */
#define MANUFACTURER_NAME         "angoSense"              /**< manufacturer name */
#define SUPPLY_VOLTAGE_MIN        3.0f                     /**< chip min supply voltage */
#define SUPPLY_VOLTAGE_MAX        5.5f                     /**< chip max supply voltage */
#define MAX_CURRENT               5.3f                     /**< chip max current */
#define TEMPERATURE_MIN           -40.0f                   /**< chip min operating temperature */
#define TEMPERATURE_MAX           85.0f                    /**< chip max operating temperature */
#define DRIVER_VERSION            1000                     /**< driver version */

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
uint8_t cs100_init(cs100_handle_t *handle)
{
    if (handle == NULL)                                                  /* check handle */
    {
        return 2;                                                        /* return error */
    }
    if (handle->debug_print == NULL)                                     /* check debug_print */
    {
        return 3;                                                        /* return error */
    }
    if (handle->trig_init == NULL)                                       /* check trig_init */
    {
        handle->debug_print("cs100: trig_init is null.\n");              /* trig_init is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->trig_deinit == NULL)                                     /* check trig_deinit */
    {
        handle->debug_print("cs100: trig_deinit is null.\n");            /* trig_deinit is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->trig_write == NULL)                                      /* check trig_write */
    {
        handle->debug_print("cs100: trig_write is null.\n");             /* trig_write is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->echo_init == NULL)                                       /* check echo_init */
    {
        handle->debug_print("cs100: echo_init is null.\n");              /* echo_init is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->echo_deinit == NULL)                                     /* check echo_deinit */
    {
        handle->debug_print("cs100: echo_deinit is null.\n");            /* echo_deinit is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->echo_read == NULL)                                       /* check echo_read */
    {
        handle->debug_print("cs100: echo_read is null.\n");              /* echo_read is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->delay_us == NULL)                                        /* check delay_us */
    {
        handle->debug_print("cs100: delay_us is null.\n");               /* delay_us is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->delay_ms == NULL)                                        /* check delay_ms */
    {
        handle->debug_print("cs100: delay_ms is null.\n");               /* delay_ms is null */
       
        return 3;                                                        /* return error */
    }
    if (handle->timestamp_read == NULL)                                  /* check timestamp_read */
    {
        handle->debug_print("cs100: timestamp_read is null.\n");         /* timestamp_read is null */
       
        return 3;                                                        /* return error */
    }
    
    if (handle->trig_init() != 0)                                        /* initialize trig */
    {
        handle->debug_print("cs100: trig init failed.\n");               /* trig init failed */
       
        return 1;                                                        /* return error */
    }
    if (handle->echo_init() != 0)                                        /* initialize echo */
    {
        handle->debug_print("cs100: echo failed.\n");                    /* return error */
        (void)handle->trig_deinit();                                     /* deinit trig */
        
        return 1;                                                        /* return error */
    }
    handle->inited = 1;                                                  /* flag finish initialization */

    return 0;                                                            /* success return 0 */
}

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
uint8_t cs100_deinit(cs100_handle_t *handle)
{
    if (handle == NULL)                                              /* check handle */
    {
        return 2;                                                    /* return error */
    }
    if (handle->inited != 1)                                         /* check handle initialization */
    {
        return 3;                                                    /* return error */
    }
    
    if (handle->echo_deinit() != 0)                                  /* echo deinit */
    {
        handle->debug_print("cs100: echo deinit failed.\n");         /* echo deinit failed */
        
        return 1;                                                    /* return error */
    }   
    if (handle->trig_deinit() != 0)                                  /* trig deinit */
    {
        handle->debug_print("cs100: trig deinit failed.\n");         /* trig deinit failed */
        
        return 1;                                                    /* return error */
    } 
    handle->inited = 0;                                              /* flag close */
    
    return 0;                                                        /* success return 0 */
}

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
uint8_t cs100_read(cs100_handle_t *handle, uint32_t *time_us, float *m)
{
    uint8_t res, value;
    cs100_time_t time_start;
    cs100_time_t time_stop;
    uint32_t timeout;
    uint8_t retry = CS100_READ_RETRY_TIMES;
    
    if (handle == NULL)                                                               /* check handle */
    {
        return 2;                                                                     /* return error */
    }
    if (handle->inited != 1)                                                          /* check handle initialization */
    {
        return 3;                                                                     /* return error */
    }
    
    while (1)                                                                         /* loop */
    {
        res = handle->trig_write(1);                                                  /* write trig 1 */
        if (res != 0)                                                                 /* check result */
        {
            handle->debug_print("cs100: trig write failed.\n");                       /* trig write failed */
           
            return 1;                                                                 /* return error */
        }
        handle->delay_us(20);                                                         /* delay 20 us */
        res = handle->trig_write(0);                                                  /* write trig 0 */
        if (res != 0)                                                                 /* check result */
        {
            handle->debug_print("cs100: trig write failed.\n");                       /* trig write failed */
           
            return 1;                                                                 /* return error */
        }
        value = 0;                                                                    /* reset value */
        timeout = 1000 * 5000;                                                        /* set timeout */
        while (value == 0)                                                            /* wait 5 s */
        {
            res = handle->echo_read((uint8_t *)&value);                               /* read echo data */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("cs100: echo read failed.\n");                    /* echo read failed */
               
                return 1;                                                             /* return error */
            }
            handle->delay_us(1);                                                      /* delay 1 us */
            timeout--;                                                                /* timeout-- */
            if (timeout == 0)                                                         /* if timeout */
            {
                handle->debug_print("cs100: no response.\n");                         /* no response */
                
                return 1;                                                             /* return error */
            }
        }
        res = handle->timestamp_read((cs100_time_t *)&time_start);                    /* read timestamp */
        if (res != 0)                                                                 /* check result */
        {
            handle->debug_print("cs100: read timestamp failed.\n");                   /* read timestamp failed */
           
            return 1;                                                                 /* return error */
        }
        value = 1;                                                                    /* reset value */
        timeout = 1000 * 5000;                                                        /* wait 5 s */
        while (value != 0)                                                            /* check value */
        {
            res = handle->echo_read((uint8_t *)&value);                               /* read echo data */
            if (res != 0)                                                             /* check result */
            {
                handle->debug_print("cs100: echo read failed.\n");                    /* echo read failed */
               
                return 1;                                                             /* return error */
            }
            handle->delay_us(1);                                                      /* delay 1 us */
            timeout--;                                                                /* timeout-- */
            if (timeout == 0)                                                         /* if timeout */
            {
                handle->debug_print("cs100: no response.\n");                         /* no response */
               
                return 1;                                                             /* return error */
            }
        }
        res = handle->timestamp_read((cs100_time_t *)&time_stop);                     /* read timestamp */
        if (res != 0)                                                                 /* check result */
        {
            handle->debug_print("cs100: read timestamp failed.\n");                   /* read timestamp failed */
           
            return 1;                                                                 /* return error */
        }
        if (time_stop.millisecond < time_start.millisecond)                           /* check timestamp */
        {
            handle->debug_print("cs100: millisecond timestamp invalid.\n");           /* millisecond timestamp is invalid */
           
            return 1;                                                                 /* return error */
        }
        *time_us = (uint32_t)((time_stop.millisecond - time_start.millisecond) * 1000
                   +(int32_t)(time_stop.microsecond - time_start.microsecond));       /* get time */
        if ((*time_us) > 150 * 1000)                                                  /* check time */
        {
            if (retry != 0)                                                           /* check remain retry times */
            {
                retry--;                                                              /* retry times-- */
                handle->delay_ms(150 + rand()%100);                                   /* delay rand time */
            }
            else
            {
                handle->debug_print("cs100: no remain retry times.\n");               /* no remain retry times */
                
                return 1;                                                             /* return error */
            }
        }
        else
        {
            break;                                                                    /* successful */
        }
    }
    *m = 340.0f / 2.0f * (float)(*time_us) / 1000000.0f;                              /* calculate distance */

    return 0;                                                                         /* success return 0 */
}

/**
 * @brief      get chip's information
 * @param[out] *info points to an cs100 info structure
 * @return     status code
 *             - 0 success
 *             - 2 handle is NULL
 * @note       none
 */
uint8_t cs100_info(cs100_info_t *info)
{
    if (info == NULL)                                               /* check handle */
    {
        return 2;                                                   /* return error */
    }
    
    memset(info, 0, sizeof(cs100_info_t));                          /* initialize cs100 info structure */
    strncpy(info->chip_name, CHIP_NAME, 32);                        /* copy chip name */
    strncpy(info->manufacturer_name, MANUFACTURER_NAME, 32);        /* copy manufacturer name */
    strncpy(info->interface, "GPIO", 8);                            /* copy interface name */
    info->supply_voltage_min_v = SUPPLY_VOLTAGE_MIN;                /* set minimal supply voltage */
    info->supply_voltage_max_v = SUPPLY_VOLTAGE_MAX;                /* set maximum supply voltage */
    info->max_current_ma = MAX_CURRENT;                             /* set maximum current */
    info->temperature_max = TEMPERATURE_MAX;                        /* set minimal temperature */
    info->temperature_min = TEMPERATURE_MIN;                        /* set maximum temperature */
    info->driver_version = DRIVER_VERSION;                          /* set driver version */
    
    return 0;                                                       /* success return 0 */
}
