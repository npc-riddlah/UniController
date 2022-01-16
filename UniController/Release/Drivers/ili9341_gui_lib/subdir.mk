################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/ili9341_gui_lib/ili9341_gui_lib.c 

OBJS += \
./Drivers/ili9341_gui_lib/ili9341_gui_lib.o 

C_DEPS += \
./Drivers/ili9341_gui_lib/ili9341_gui_lib.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/ili9341_gui_lib/%.o: ../Drivers/ili9341_gui_lib/%.c Drivers/ili9341_gui_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-ili9341_gui_lib

clean-Drivers-2f-ili9341_gui_lib:
	-$(RM) ./Drivers/ili9341_gui_lib/ili9341_gui_lib.d ./Drivers/ili9341_gui_lib/ili9341_gui_lib.o

.PHONY: clean-Drivers-2f-ili9341_gui_lib

