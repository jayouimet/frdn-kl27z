################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/affichage.c \
../source/bmp280.c \
../source/mtb.c \
../source/semihost_hardfault.c \
../source/temperature.c 

C_DEPS += \
./source/affichage.d \
./source/bmp280.d \
./source/mtb.d \
./source/semihost_hardfault.d \
./source/temperature.d 

OBJS += \
./source/affichage.o \
./source/bmp280.o \
./source/mtb.o \
./source/semihost_hardfault.o \
./source/temperature.o 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c source/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL27Z64VLH4 -DCPU_MKL27Z64VLH4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSERIAL_PORT_TYPE_UART=1 -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\utilities" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\component\serial_manager" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\drivers" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\component\uart" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\CMSIS" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\component\lists" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\device" -I../board -I../source -I../ -I../drivers -I../device -I../CMSIS -I../component/uart -I../component/serial_manager -I../component/lists -I../utilities -I../board/boards -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-source

clean-source:
	-$(RM) ./source/affichage.d ./source/affichage.o ./source/bmp280.d ./source/bmp280.o ./source/mtb.d ./source/mtb.o ./source/semihost_hardfault.d ./source/semihost_hardfault.o ./source/temperature.d ./source/temperature.o

.PHONY: clean-source

