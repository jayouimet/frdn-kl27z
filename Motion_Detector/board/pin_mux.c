/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v6.0
processor: MKL27Z64xxx4
package_id: MKL27Z64VLH4
mcu_data: ksdk2_0
processor_version: 6.0.1
board: FRDM-KL27Z
pin_labels:
- {pin_num: '50', pin_signal: PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/CMP0_OUT, label: 'J2[12]/D13-SPI0_SCK', identifier: SPI0_SCK;MD}
- {pin_num: '57', pin_signal: PTD0/SPI0_PCS0/TPM0_CH0/FXIO0_D0, label: 'J1[1]', identifier: MD}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '23', peripheral: LPUART0, signal: RX, pin_signal: PTA1/LPUART0_RX/TPM2_CH0}
  - {pin_num: '24', peripheral: LPUART0, signal: TX, pin_signal: PTA2/LPUART0_TX/TPM2_CH1}
  - {pin_num: '44', peripheral: GPIOC, signal: 'GPIO, 1', pin_signal: ADC0_SE15/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0, slew_rate: slow, pull_select: up, pull_enable: enable}
  - {pin_num: '41', peripheral: GPIOB, signal: 'GPIO, 18', pin_signal: PTB18/TPM2_CH0}
  - {pin_num: '28', peripheral: GPIOA, signal: 'GPIO, 12', pin_signal: PTA12/TPM1_CH0}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);

    /* PORTA1 (pin 23) is configured as LPUART0_RX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART0_RX_PORT, BOARD_INITPINS_DEBUG_UART0_RX_PIN, kPORT_MuxAlt2);

    /* PORTA12 (pin 28) is configured as PTA12 */
    PORT_SetPinMux(BOARD_INITPINS_TPM1_CH0_PORT, BOARD_INITPINS_TPM1_CH0_PIN, kPORT_MuxAsGpio);

    /* PORTA2 (pin 24) is configured as LPUART0_TX */
    PORT_SetPinMux(BOARD_INITPINS_DEBUG_UART0_TX_PORT, BOARD_INITPINS_DEBUG_UART0_TX_PIN, kPORT_MuxAlt2);

    /* PORTB18 (pin 41) is configured as PTB18 */
    PORT_SetPinMux(BOARD_INITPINS_LED_RED_PORT, BOARD_INITPINS_LED_RED_PIN, kPORT_MuxAsGpio);

    const port_pin_config_t SW3 = {/* Internal pull-up resistor is enabled */
                                   kPORT_PullUp,
                                   /* Slow slew rate is configured */
                                   kPORT_SlowSlewRate,
                                   /* Passive filter is disabled */
                                   kPORT_PassiveFilterDisable,
                                   /* Low drive strength is configured */
                                   kPORT_LowDriveStrength,
                                   /* Pin is configured as PTC1 */
                                   kPORT_MuxAsGpio};
    /* PORTC1 (pin 44) is configured as PTC1 */
    PORT_SetPinConfig(BOARD_INITPINS_SW3_PORT, BOARD_INITPINS_SW3_PIN, &SW3);

    SIM->SOPT5 = ((SIM->SOPT5 &
                   /* Mask bits to zero which are setting */
                   (~(SIM_SOPT5_LPUART0TXSRC_MASK | SIM_SOPT5_LPUART0RXSRC_MASK)))

                  /* LPUART0 Transmit Data Source Select: LPUART0_TX pin. */
                  | SIM_SOPT5_LPUART0TXSRC(SOPT5_LPUART0TXSRC_LPUART_TX)

                  /* LPUART0 Receive Data Source Select: LPUART_RX pin. */
                  | SIM_SOPT5_LPUART0RXSRC(SOPT5_LPUART0RXSRC_LPUART_RX));
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
