################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/fsl_adc16.c \
../drivers/fsl_clock.c \
../drivers/fsl_common.c \
../drivers/fsl_gpio.c \
../drivers/fsl_lpuart.c \
../drivers/fsl_smc.c \
../drivers/fsl_uart.c 

OBJS += \
./drivers/fsl_adc16.o \
./drivers/fsl_clock.o \
./drivers/fsl_common.o \
./drivers/fsl_gpio.o \
./drivers/fsl_lpuart.o \
./drivers/fsl_smc.o \
./drivers/fsl_uart.o 

C_DEPS += \
./drivers/fsl_adc16.d \
./drivers/fsl_clock.d \
./drivers/fsl_common.d \
./drivers/fsl_gpio.d \
./drivers/fsl_lpuart.d \
./drivers/fsl_smc.d \
./drivers/fsl_uart.d 


# Each subdirectory must supply rules for building sources it contributes
drivers/%.o: ../drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -std=gnu99 -D__REDLIB__ -DCPU_MKL27Z64VLH4 -DCPU_MKL27Z64VLH4_cm0plus -DFRDM_KL27Z -DFREEDOM -DSERIAL_PORT_TYPE_UART=1 -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/board" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/source" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/drivers" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/device" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/CMSIS" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/utilities" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/component/serial_manager" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/component/lists" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/ADC16/component/uart" -O0 -fno-common -g3 -Wall -c  -ffunction-sections  -fdata-sections  -ffreestanding  -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


