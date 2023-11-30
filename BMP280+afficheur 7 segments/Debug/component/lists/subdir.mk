################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../component/lists/generic_list.c 

OBJS += \
./component/lists/generic_list.o 

C_DEPS += \
./component/lists/generic_list.d 


# Each subdirectory must supply rules for building sources it contributes
component/lists/%.o: ../component/lists/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL27Z64VLH4 -DCPU_MKL27Z64VLH4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSERIAL_PORT_TYPE_UART=1 -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/BMP280/utilities" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/BMP280/component/serial_manager" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/BMP280/drivers" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/BMP280/component/uart" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/BMP280/CMSIS" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/BMP280/component/lists" -I"/Users/kameladi/Documents/MCUXpressoIDE_11.2.0/workspace/BMP280/device" -I../board -I../source -I../ -I../drivers -I../device -I../CMSIS -I../component/uart -I../component/serial_manager -I../component/lists -I../utilities -I../board/boards -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


