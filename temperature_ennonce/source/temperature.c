
/**
 * @file    BMP180/BMP085 temperature_V4.c
 * @brief   Kame Adi
 */

#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL27Z644.h"
#include "fsl_debug_console.h"
#include "fsl_i2c.h"
#include "bmp180.h"

/*Adress of the master peripheral I2C0 */

#define I2C_MASTER_BASEADDR 		I2C0
#define I2C_MASTER_CLK_FREQ         CLOCK_GetFreq(I2C0_CLK_SRC)

/* Implementation of the function delay() */

volatile uint32_t g_systickCounter;

/* Handler of the interruption of the SysTick counter */

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

/*	\Brief: This function is used to delay the execution
 *	\Return : void
 *	\param a 32 bits variable corresponding to the number of milliseconds
*/

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

/*	Brief : The delay routine
 *	\param : delay in ms
*/
void BMP180_delay_msek(u32 msek)
{
	SysTick_DelayTicks(msek);
}

/*----------------------------------------------------------------------------
 struct used to access the bmp180 parameters
 *	bmp180 contains the following fields
 *	Bus write function pointer: BMP180_WR_FUNC_PTR
 *	Bus read function pointer: BMP180_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *	Chip id of the sensor: chip_id
 *	Calibration parameters
 ---------------------------------------------------------------------------*/
struct bmp180_t bmp180;

/* Constant defining the buffer length for I2C communications
*/
#define	I2C_BUFFER_LEN 25


/*	\Brief: This function is used for I2C bus write
 *	\Return : Status of the I2C write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : Contains the data to be written into the register
 *	\param cnt : The no of byte of data to write
 */

int8_t BMP180_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	status_t status;
	s32 iError = 0;
	u8 array[I2C_BUFFER_LEN]= {0};
	u8 stringpos = 0;
	array[0] = reg_addr;

	//Used in the function I2C_MasterTransferBlocking(...)

	i2c_master_transfer_t masterXfer;

	//Allocate memory for the masterXfer variable
	memset(&masterXfer, 0, sizeof(masterXfer));

	masterXfer.slaveAddress   = dev_addr; // Adresse du device BMP180
	masterXfer.direction      = kI2C_Write;
	masterXfer.subaddress     = reg_addr; // adresse du registre à écrire;
	masterXfer.subaddressSize = 1;
	masterXfer.data           = &array[0];
	masterXfer.dataSize       = cnt;
	masterXfer.flags          = kI2C_TransferDefaultFlag;

	// transférer les données de reg_data vers array
	for (stringpos = 0; stringpos < cnt; stringpos++) {
		array[stringpos] = *(reg_data + stringpos);
	}

	status = I2C_MasterTransferBlocking(I2C_MASTER_BASEADDR, &masterXfer);


	if (status == kStatus_Success) {
		iError = 0;
	} else {
		iError = 2;
	}

	PRINTF("Write Status : %d", iError);

	// Appeler la fonction  I2C_MasterTransferBlocking(...) de la librairie fsl_i2c
    // iError = I2C_MasterTransferBlocking(...)

	return (s8)iError;
}

/*	\Brief: This function is used for I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : contains the data read from the sensor
 *	\param cnt : The no of byte of data to be read
 */

s8 BMP180_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	status_t status;
	s32 iError = 0;
	u8 array[I2C_BUFFER_LEN] = {0};
	u8 stringpos = 0;
	array[0] = reg_addr;
	i2c_master_transfer_t masterXfer;

	PRINTF("I2C_BUFFER_LEN : %d\n", I2C_BUFFER_LEN);
	PRINTF("cnt : %d\n", cnt);

	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress   = dev_addr;
	masterXfer.direction      = kI2C_Read;// trouvez la constante définie dans fsl_i2c.h qui correspond
	masterXfer.subaddress     = reg_addr;
	masterXfer.subaddressSize = 1;
	masterXfer.data           = &array[0]; //adresse du tableau array;
	masterXfer.dataSize       = cnt;
	masterXfer.flags          = kI2C_TransferDefaultFlag;

	PRINTF("I2C_MASTER_BASEADDR : %d\n", I2C_MASTER_BASEADDR);

	status = I2C_MasterTransferBlocking(I2C_MASTER_BASEADDR, &masterXfer);

	// transférez les données de array vers regdata

	if (status == kStatus_Success) {
		iError = 0;
	} else {
		iError = 2;
	}

	for (stringpos = 0; stringpos < cnt; stringpos++) {
		*(reg_data + stringpos) = array[stringpos];
	}

	PRINTF("Read Status : %d\n", iError);

	return (s8)iError;
}

/*	\Brief: This function is used to map the I2C bus read, write, delay and
*	device address with a global structure of type bmp180_t
*   By using the variable bmp180 the following structure parameters can be accessed
*	Bus write function pointer: BMP180_WR_FUNC_PTR
*	Bus read function pointer: BMP180_RD_FUNC_PTR
*	Delay function pointer: delay_msec
*	I2C address: dev_addr
*/

void I2C_routine(void) {
	bmp180.bus_write = BMP180_I2C_bus_write;
	bmp180.bus_read = BMP180_I2C_bus_read;
	bmp180.dev_addr = BMP180_I2C_ADDR;
	bmp180.delay_msec = BMP180_delay_msek;
}


/* This function reads the sensor data
 *	\param: None
 *	\return: communication result
 */

s32 bmp180_data_read(void)
{

	s32 com_rslt = E_BMP_COMM_RES;
	u16 v_uncomp_temp_u16 = 0;

 	 /*  This function is used to initialize the bmp180. It retrieves the
 	 *	the following parameters
 	 *	I2C address
 	 *	Bus Write
 	 *	Bus read
 	 *	Chip id
 	 *	Calibration values
   	 */

	// appelez la fonction bmp180_init en lui passant comme paramètre l'adresse de la variable bmp_180;
	com_rslt = bmp180_init(&bmp180);

	/*  This function used to read the calibration values.
	 *	These values are used to calculate the true temperature
	 *	Parameter		MSB		LSB		bit
	 *		AC1			0xAA	0xAB	0 to 7
	 *		AC2			0xAC	0xAD	0 to 7
	 *		AC3			0xAE	0xAF	0 to 7
	 *		AC4			0xB0	0xB1	0 to 7
	 *		AC5			0xB2	0xB3	0 to 7
	 *		AC6			0xB4	0xB5	0 to 7
	 *		B1			0xB6	0xB7	0 to 7
	 *		B2			0xB8	0xB9	0 to 7
	 *		MB			0xBA	0xBB	0 to 7
	 *		MC			0xBC	0xBD	0 to 7
	 *		MD			0xBE	0xBF	0 to 7
	 */

	com_rslt += bmp180_get_calib_param();

		// Si les fonctions d'initialisation et de calibration s'exécutent correctement
		// alors com_rslt doit être égal à zéro sinon affichez un message d'erreur ici ;

	if (com_rslt == 0) {
		PRINTF("bmp180_get_calib_param initialization success \n");
	} else {
		PRINTF("bmp180_get_calib_param initialization failed \n");
	}

   /*
	* This API is used to read the
	*	uncompensated temperature(ut) value
	*/

	v_uncomp_temp_u16 = bmp180_get_uncomp_temperature();

	 /*	This API is used to convert the uncompensated temperature to the
	 *	true temperature
	 */

	com_rslt = bmp180_get_temperature(v_uncomp_temp_u16); // appelez la fonction bmp180_get_temperature avec comme paramètre v_uncomp_temp_u16;

	PRINTF("Temp maybe : %d\n", com_rslt);

	return com_rslt;
}


int main(void) {
    int32_t temperature, temperatureEnt, temperatureDec;

	i2c_master_config_t config = {
		.enableMaster = true,
		.enableStopHold = false,
		.baudRate_Bps = 100000,
		.glitchFilterWidth = 0
	 };

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
    BOARD_InitDebugConsole();

    I2C_routine();

    /* Set systick reload value to generate 1ms interrupt */

   if (SysTick_Config(SystemCoreClock / 1000U))
   {
	   PRINTF("SysTick initialization failed \n");
   }

   // Appeler la fonction d'initialisation du I2C Master du fsl_i2c. Cette fonction prend comme
   // paramètres, dans cet ordre, l'adresse du I2C master, l'adresse de la variable config (déclarée
   // plus haut) et la fréquence d'horloge périphérique qu'on peu obtenir avec CLOCK_GetFreq(I2C0_CLK_SRC)

   I2C_MasterInit(I2C_MASTER_BASEADDR, &config, I2C_MASTER_CLK_FREQ);

   while(1)
   {
	   temperature = bmp180_data_read();
		   // appelez la fonction bmp180_data_read;
	   // la température retournée est en 0.1 degrés celcius
	   // Dans ce cas la valeur 189 retournée correspond à 18.9 degrés
	   // Pour des raisons d'efficacité le printf que nous utilisons ne support pas le type float
	   // Affichez alors la température avec le point décimal sans utiliser les %f (float)

	   // PRINTF(.......);

	   PRINTF("TEST\n");

	   BMP180_delay_msek(1000);
   }
   return 0;
}

