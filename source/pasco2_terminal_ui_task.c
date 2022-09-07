/*****************************************************************************
** File name: pasco2_terminal_ui_task.c
**
** Description: This file implements a terminal UI to configure parameters
** for PASCO2 application.
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

/* Header file from system */
#include <ctype.h>
#include <stdlib.h>

/* Header file includes */
#include "cy_retarget_io.h"
#include "cybsp.h"
#include "cyhal.h"

/* Header file for local task */
#include "pasco2_task.h"
#include "pasco2_terminal_ui_task.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/
#define IFX_PASCO2_VALUE_MAXLENGTH 256


/*******************************************************************************
 * Global Variables
 ******************************************************************************/

/*******************************************************************************
 * Function Name: terminal_ui_menu
 *******************************************************************************
 * Summary:
 *   This function prints the available parameters configurable for CO2 sensor.
 *
 * Parameters:
 *   none
 *
 * Return:
 *   none
 ******************************************************************************/
static void terminal_ui_menu(void)
{
    // Print main menu
    printf("Select a setting to configure\r\n");
    printf("'p': Set the measurement period\r\n");
    printf("'i': Print additional diagnostic information if available\r\n");
    printf("\r\n");
}

/*******************************************************************************
 * Function Name: terminal_ui_info
 *******************************************************************************
 * Summary:
 *   This function prints character using which a user can see all available
 *   parameters configurable for CO2 sensor.
 *
 * Parameters:
 *   none
 *
 * Return:
 *   none
 ******************************************************************************/
static void terminal_ui_info(void)
{
    printf("Press '?' to list all CO2 sensor settings\r\n");
}

/*******************************************************************************
 * Function Name: terminal_ui_readline
 *******************************************************************************
 * Summary:
 *   This function reads values entered by a user and prints it.
 *
 * Parameters:
 *   uart_ptr: UART object
 *   line: value to be read
 *   maxlength: maximum number of characters to be read
 *
 * Return:
 *   none
 ******************************************************************************/
static void terminal_ui_readline(void *uart_ptr, char *line, int maxlength)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    if (maxlength <= 0)
    {
        return;
    }
    int i = 0;
    uint8_t rx_value = 0;
    /* Receive character until enter has been pressed */
    while ((rx_value != '\r') && (--maxlength > 0))
    {
        result = cyhal_uart_getc(uart_ptr, &rx_value, 0);
        if (result != CY_RSLT_SUCCESS)
        {
            CY_ASSERT(0);
        }

        result = cyhal_uart_putc(uart_ptr, rx_value);
        if (result != CY_RSLT_SUCCESS)
        {
            CY_ASSERT(0);
        }

        if (isspace(rx_value))
        {
            continue;
        }
        line[i++] = rx_value;
    }

    result = cyhal_uart_putc(uart_ptr, '\n');
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    line[i] = '\0';
}

/*******************************************************************************
 * Function Name: pasco2_terminal_ui_task
 *******************************************************************************
 * Summary:
 *   Continuously checks if a key has been pressed to configure CO2 sensor
 *   parameter. Displays a status message according to the user
 *   input/selection.
 *
 * Parameters:
 *   arg: thread
 *
 * Return:
 *   none
 ******************************************************************************/
void pasco2_terminal_ui_task(cy_thread_arg_t arg)
{
    (void)arg;

    terminal_ui_menu();
    char value[IFX_PASCO2_VALUE_MAXLENGTH];
    uint8_t rx_value = 0;

    for (;;)
    {
        /* Check if a key was pressed */
        if (cyhal_uart_getc(&cy_retarget_io_uart_obj, &rx_value, 0) == CY_RSLT_SUCCESS)
        {
            pasco2_display_ppm(false);

            switch ((char)rx_value)
            {
                // menu
                case '?':
                    terminal_ui_menu();
                    break;
                
                // measurement period
                case 'p':
                {
                    printf("Enter the measurement period [5-4095]s\r\n");
                    terminal_ui_readline(&cy_retarget_io_uart_obj, value, IFX_PASCO2_VALUE_MAXLENGTH);

                    char *end;
                    const uint16_t measurement_period = (uint16_t)strtol(value, &end, 10);
                    if (value != end)
                    {
                        if ((measurement_period < XENSIV_PASCO2_MEAS_RATE_MIN) || (measurement_period > XENSIV_PASCO2_MEAS_RATE_MAX))
                        {
                            printf("CO2 sensor measurement period configuration error, Valid range is [5-4095]s\r\n\r\n");
                        }
                        else
                        {
                            xensiv_pasco2_measurement_config_t meas_config = {
                                .b.op_mode = XENSIV_PASCO2_OP_MODE_IDLE,
                                .b.boc_cfg = XENSIV_PASCO2_BOC_CFG_AUTOMATIC
                            };
                            int32_t status = xensiv_pasco2_set_measurement_config(&xensiv_pasco2, meas_config);

                            status |= xensiv_pasco2_set_measurement_rate(&xensiv_pasco2, measurement_period);

                            meas_config = (xensiv_pasco2_measurement_config_t){
                                .b.op_mode = XENSIV_PASCO2_OP_MODE_CONTINUOUS,
                                .b.boc_cfg = XENSIV_PASCO2_BOC_CFG_AUTOMATIC
                            };
                            status |= xensiv_pasco2_set_measurement_config(&xensiv_pasco2, meas_config);

                            if (status == CY_RSLT_SUCCESS)
                            {
                                printf("CO2 measurement period set to: %d\r\n\r\n", measurement_period);
                            }
                            else
                            {
                                printf("An unexpected error occurred while trying to change the measurement period\r\n\r\n");
                            }
                        }
                    }
                    break;
                }
                
                case 'i':
                    printf("Display additional diagnostic information [y/n]?\r\n");
                    terminal_ui_readline(&cy_retarget_io_uart_obj, value, IFX_PASCO2_VALUE_MAXLENGTH);
                    if (strlen(value) != 1 || (value[0] != 'y' && value[0] != 'n'))
                    {
                        printf("Input error, valid values are [y/n]\r\n\r\n");
                        continue;
                    }
                    pasco2_enable_internal_logging(value[0] == 'y');
                    break;
                
                default:
                    terminal_ui_info();
                    break;
            }

            pasco2_display_ppm(true);
        }
    }
}

/* [] END OF FILE */
