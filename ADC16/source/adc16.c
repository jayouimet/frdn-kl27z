/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2018 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_adc16.h"

#include "pin_mux.h"
#include "clock_config.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define ADC16_CHANNEL_GROUP 0U
#define ADC16_USER_CHANNEL  1U /* PTE16, A0-ADC0_SE1, J4-2 on FRDM-KL27Z. */


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
const uint32_t g_Adc16_12bitFullRange = 65536; //4096U;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Main function
 */
int main(void)
{
    adc16_config_t adc16Config;
    adc16_channel_config_t adc16ChannelConfig;
    uint32_t rawValue;
    float voltage;

    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\nExemple d'utilisation du convertisseur Analogique digital 16 bits.\r\n");

    /*
     * adc16Config.referenceVoltageSource = kADC16_ReferenceVoltageSourceVref;
     * adc16Config.clockSource = kADC16_ClockSourceAsynchronousClock;
     * adc16Config.enableAsynchronousClock = true;
     * adc16Config.clockDivider = kADC16_ClockDivider8;
     * adc16Config.resolution = kADC16_ResolutionSE12Bit;
     * adc16Config.longSampleMode = kADC16_LongSampleDisabled;
     * adc16Config.enableHighSpeed = false;
     * adc16Config.enableLowPower = false;
     * adc16Config.enableContinuousConversion = false;
     */
    ADC16_GetDefaultConfig(&adc16Config);
    //adc16Config.referenceVoltageSource = kADC16_ReferenceVoltageSourceValt;
    adc16Config.resolution = kADC16_Resolution16Bit;
    ADC16_Init(ADC0, &adc16Config);
    ADC16_EnableHardwareTrigger(ADC0, false); /* Make sure the software trigger is used. */

    if (kStatus_Success == ADC16_DoAutoCalibration(ADC0))
    {
        PRINTF("ADC16_DoAutoCalibration() Done.\r\n");
    }
    else
    {
        PRINTF("ADC16_DoAutoCalibration() Failed.\r\n");
    }

    PRINTF("ADC Full Range: %d\r\n", g_Adc16_12bitFullRange);
    PRINTF("Press any key to get user channel's ADC value ...\r\n");

    adc16ChannelConfig.channelNumber                        = ADC16_USER_CHANNEL;
    adc16ChannelConfig.enableInterruptOnConversionCompleted = false;
    adc16ChannelConfig.enableDifferentialConversion = false;

    while (1)
    {
        ADC16_SetChannelConfig(ADC0, ADC16_CHANNEL_GROUP, &adc16ChannelConfig);
        while (0U == (kADC16_ChannelConversionDoneFlag &
                      ADC16_GetChannelStatusFlags(ADC0, ADC16_CHANNEL_GROUP)))
        {
        }
        rawValue = ADC16_GetChannelConversionValue(ADC0, ADC16_CHANNEL_GROUP);
        voltage = ((float)rawValue/65535) * 3.3;

        PRINTF("Valeur brute : %6d ..... Tension (V) : %.2f\r\n", rawValue, voltage);
    }
}
