
#include "fsl_debug_console.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_common.h"
#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"



/* Variable bouléenne qui indique si le bouton est préssé */
volatile bool g_ButtonPress = false;

static void delay(volatile uint32_t nof) {

  while(nof!=0) {

    __asm("NOP");

    nof--;

  }

}


/*
 * Handler pour l'interruption du détecteur
 *
 */

void PORTA_IRQHandler(void)
{
    /* Effacer le drapeau d'interruption */
    GPIO_PortClearInterruptFlags(GPIOA, 1U << 12);
    /* Changer l'état du boutton. */
    g_ButtonPress = true;

}


int main(void)
{
    /* Défini la structure d'initialisation pour le détecteur de mouvement */
    gpio_pin_config_t detector_config = {
        kGPIO_DigitalInput,
        0,
    };

    /* Défini la structure d'initialisation du pin en sortie de la LED */
    gpio_pin_config_t led_config  = {
        kGPIO_DigitalOutput,
        1,
    };


    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    PRINTF("\r\n INF1633 - Detection de mouvement\r\n");

    /* Activer l'interruption pour le pin 12 du port A*/

    PORT_SetPinInterruptConfig(PORTA, 12, kPORT_InterruptRisingEdge);

    /* Activer le NVIC pour le port A*/

    EnableIRQ(PORTA_IRQn);

    /* Initialiser le GPIO du port A pin 12 */

    GPIO_PinInit(GPIOA, 12, &detector_config);

    /* Initialiser le GPIO pour la LED rouge */

    GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);

    while (1)
    {
        if (g_ButtonPress)
        {
            PRINTF(" Alerte : mouvement detecte \r\n");
            /* Toggle LED. */
            GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 0);
            delay(1000000);
            GPIO_PinWrite(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, 1);
            /* Réinitialiser l’état du bouton poussoir */
            g_ButtonPress = false;
        }
    }
}
