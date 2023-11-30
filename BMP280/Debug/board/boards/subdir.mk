################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../board/boards/board.c \
../board/boards/clock_config.c \
../board/boards/peripherals.c \
../board/boards/pin_mux.c 

C_DEPS += \
./board/boards/board.d \
./board/boards/clock_config.d \
./board/boards/peripherals.d \
./board/boards/pin_mux.d 

OBJS += \
./board/boards/board.o \
./board/boards/clock_config.o \
./board/boards/peripherals.o \
./board/boards/pin_mux.o 


# Each subdirectory must supply rules for building sources it contributes
board/boards/%.o: ../board/boards/%.c board/boards/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL27Z64VLH4 -DCPU_MKL27Z64VLH4_cm0plus -DFSL_RTOS_BM -DSDK_OS_BAREMETAL -DSDK_DEBUGCONSOLE=0 -DPRINTF_FLOAT_ENABLE=1 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -DSERIAL_PORT_TYPE_UART=1 -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\utilities" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\component\serial_manager" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\drivers" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\component\uart" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\CMSIS" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\component\lists" -I"D:\Universite\UQO\Automne 2023\Systemes embarques\Projet\frdn-kl27z\BMP280\device" -I../board -I../source -I../ -I../drivers -I../device -I../CMSIS -I../component/uart -I../component/serial_manager -I../component/lists -I../utilities -I../board/boards -O0 -fno-common -g3 -Wall -c -ffunction-sections -fdata-sections -ffreestanding -fno-builtin -fmerge-constants -fmacro-prefix-map="$(<D)/"= -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-board-2f-boards

clean-board-2f-boards:
	-$(RM) ./board/boards/board.d ./board/boards/board.o ./board/boards/clock_config.d ./board/boards/clock_config.o ./board/boards/peripherals.d ./board/boards/peripherals.o ./board/boards/pin_mux.d ./board/boards/pin_mux.o

.PHONY: clean-board-2f-boards

