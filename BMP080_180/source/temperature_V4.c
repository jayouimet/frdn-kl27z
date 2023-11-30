
/**
 * @file    temperature_V3.c
 * @brief   Kame Adi
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL27Z644.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_i2c.h"

#include "bmp180.h"

#define I2C_MASTER_BASEADDR I2C0

/* Implementation d'une fonction delay() pour compter des milis */
volatile uint32_t g_systickCounter;

void SysTick_Handler(void)
{
    if (g_systickCounter != 0U)
    {
        g_systickCounter--;
    }
}

void SysTick_DelayTicks(uint32_t n)
{
    g_systickCounter = n;
    while (g_systickCounter != 0U)
    {
    }
}

/*----------------------------------------------------------------------------
 struct bmp180_t parameters can be accessed by using bmp180
 *	bmp180_t having the following parameters
 *	Bus write function pointer: BMP180_WR_FUNC_PTR
 *	Bus read function pointer: BMP180_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *	Chip id of the sensor: chip_id
 *	Calibration parameters
 ---------------------------------------------------------------------------*/
struct bmp180_t bmp180;
#define	I2C_BUFFER_LEN 25

/*---------------------------------------------------------------------------
** The following functions are used for reading and writing of
** sensor data using I2C or SPI communication
----------------------------------------------------------------------------*/

/*	\Brief: The function is used as I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read
 */
s8 BMP180_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*	\Brief: The function is used as SPI bus write
 *	\Return : Status of the SPI write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */

s8 BMP180_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*
 * \Brief: I2C init routine
*/
s8 I2C_routine(void);

/*	Brief : The delay routine
 *	\param : delay in ms
*/
void BMP180_delay_msek(u32 msek)
{
	SysTick_DelayTicks(msek);
}

/*--------------------------------------------------------------------------
*	The following function is used to map the I2C bus read, write, delay and
*	device address with global structure bmp180_t
*
*  By using bmp180 the following structure parameter can be accessed
*	Bus write function pointer: BMP180_WR_FUNC_PTR
*	Bus read function pointer: BMP180_RD_FUNC_PTR
*	Delay function pointer: delay_msec
*	I2C address: dev_addr
*--------------------------------------------------------------------------*/

s8 I2C_routine(void) {
	bmp180.bus_write = BMP180_I2C_bus_write;
	bmp180.bus_read = BMP180_I2C_bus_read;
	bmp180.dev_addr = BMP180_I2C_ADDR;
	bmp180.delay_msec = BMP180_delay_msek;

	return 0;
}

/*	\Brief: The function is used as I2C bus write
 *	\Return : Status of the I2C write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */

s8 BMP180_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	status_t status;

	s32 iError = 0;
	u8 array[I2C_BUFFER_LEN]= {0};
	u8 stringpos = 0;
	array[0] = reg_addr;

	i2c_master_transfer_t masterXfer;
    memset(&masterXfer, 0, sizeof(masterXfer));

	masterXfer.slaveAddress   = dev_addr;
	masterXfer.direction      = kI2C_Write;
	masterXfer.subaddress     = reg_addr;
	masterXfer.subaddressSize = 1;
	masterXfer.data           = &array[0];
	masterXfer.dataSize       = cnt;
	masterXfer.flags          = kI2C_TransferDefaultFlag;

	for (stringpos = 0; stringpos < cnt; stringpos++) {
			array[stringpos] = *(reg_data + stringpos);
		}

	status = I2C_MasterTransferBlocking(I2C_MASTER_BASEADDR, &masterXfer);

	if (status == kStatus_Success)
	{
		iError = 0;
	}
	else
	{
			iError = 2;  // Doit être revu ....
	}

	return (s8)iError;
}


/*	\Brief: The function is used as I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
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

	memset(&masterXfer, 0, sizeof(masterXfer));
	masterXfer.slaveAddress   = dev_addr;
	masterXfer.direction      = kI2C_Read;
	masterXfer.subaddress     = reg_addr;
	masterXfer.subaddressSize = 1;
	masterXfer.data           = &array[0];
	masterXfer.dataSize       = cnt;
	masterXfer.flags          = kI2C_TransferDefaultFlag;

	status = I2C_MasterTransferBlocking(I2C_MASTER_BASEADDR, &masterXfer);

	if (status == kStatus_Success)
		{
			iError = 0;
		}
		else
		{
				iError = 2;  // Doit être revu ....
		}

	for (stringpos = 0; stringpos < cnt; stringpos++) {
		*(reg_data + stringpos) = array[stringpos];
	}

	return (s8)iError;
}


/*----------------------------------------------------------------------------*/
/* This function reads the sensor data
 *	\param: None
 *	\return: communication result
 */
s32 bmp180_data_read(void)
{
 /* result of communication results*/
	s32 com_rslt = E_BMP_COMM_RES;
	u16 v_uncomp_temp_u16 = 0;
	u32 v_uncomp_press_u32 = 0;


/*--------------------------------------------------------------------------
 *  This function used to assign the value/reference of
 *	the following parameters
 *	I2C address
 *	Bus Write
 *	Bus read
 *	Chip id
 *	Calibration values
-------------------------------------------------------------------------*/
	com_rslt = bmp180_init(&bmp180);

/************************* END INITIALIZATION *************************/
/*------------------------------------------------------------------*
************************* START CALIPRATION ********
*---------------------------------------------------------------------*/
	/*  This function used to read the calibration values of following
	 *	these values are used to calculate the true pressure and temperature
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
	 *		MD			0xBE	0xBF	0 to 7*/
	com_rslt += bmp180_get_calib_param();
/*------------------------------------------------------------------*
************************* END CALIPRATION ********
*---------------------------------------------------------------------*/
/************************* START READ UNCOMPENSATED TEMPERATURE AND PRESSURE********/


	if (com_rslt!=0)
	{
		PRINTF("Erreur d'initialisation du capteur\n");
	}
	/*	This API is used to read the
	*	uncompensated temperature(ut) value*/
	v_uncomp_temp_u16 = bmp180_get_uncomp_temperature();


	/*	This API is used to read the
	*	uncompensated pressure(ut) value*/
	//v_uncomp_press_u32 = bmp180_get_uncomp_pressure();

/************************* END READ UNCOMPENSATED TEMPERATURE AND PRESSURE********/


/************************* START READ TRUE TEMPERATURE AND PRESSURE********/
/****************************************************************************
 *	This API is used to read the
 *	true temperature(t) value input
 *	parameter as uncompensated temperature(ut)
 *
 ***************************************************************************/
	com_rslt = bmp180_get_temperature(v_uncomp_temp_u16);

/****************************************************************************
 *	This API is used to read the
 *	true pressure(p) value
 *	input parameter as uncompensated pressure(up)
 *
 ***************************************************************************/
	//com_rslt += bmp180_get_pressure(v_uncomp_press_u32);

/************************* END READ TRUE TEMPERATURE AND PRESSURE********/
return com_rslt;
}


int main(void) {

    int32_t temperature;

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
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    I2C_routine();

    /* Set systick reload value to generate 1ms interrupt */
       if (SysTick_Config(SystemCoreClock / 1000U))
       {
    	   PRINTF("Echec dans l'initialisation du systick\n");
       }

    I2C_MasterInit(I2C_MASTER_BASEADDR, &config, CLOCK_GetFreq(I2C0_CLK_SRC));

    while(1)
    {
    temperature = bmp180_data_read()/10;
    printf("temperature = %d \n", temperature);
    SysTick_DelayTicks(1000);
    }
    return 0 ;
}

