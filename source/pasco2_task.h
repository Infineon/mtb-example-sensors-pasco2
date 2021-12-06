/******************************************************************************
** File Name:   pasco2_task.h
**
** Description: This file contains the function prototypes and constants used
**   in pasco2_task.c.
**
** Related Document: See README.md
**
** ===========================================================================
** Copyright (C) 2021 Infineon Technologies AG. All rights reserved.
** ===========================================================================
**
** ===========================================================================
** Infineon Technologies AG (INFINEON) is supplying this file for use
** exclusively with Infineon's sensor products. This file can be freely
** distributed within development tools and software supporting such
** products.
**
** THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
** OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
** MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
** INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR DIRECT, INDIRECT,
** INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON
** WHATSOEVER.
** ===========================================================================
*/

#pragma once

/* Header file includes */
#include "cyabs_rtos.h"
#include "cycfg.h"

/* Header file for library */
#include "xensiv_pasco2_mtb.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/

/* Name of the pas co2 task */
#define PASCO2_TASK_NAME "CO2 SENSOR TASK"
/* Stack size for the co2 sensor task */
#define PASCO2_TASK_STACK_SIZE (1024 * 4)
/**< Priority number for the co2 sensor task */
#define PASCO2_TASK_PRIORITY (CY_RTOS_PRIORITY_BELOWNORMAL)

/*******************************************************************************
 * Global Variables
 *******************************************************************************/
extern xensiv_pasco2_t xensiv_pasco2;
extern cyhal_timer_t led_blink_timer;

/*******************************************************************************
 * Functions
 *******************************************************************************/

void pasco2_task(cy_thread_arg_t arg);
void pasco2_enable_internal_logging(bool enable_logging);
void pasco2_display_ppm(bool enable_output);

/* [] END OF FILE */
