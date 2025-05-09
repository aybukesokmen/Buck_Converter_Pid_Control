################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MYLIB/Src/can_receiver.c \
../MYLIB/Src/can_transmitter.c \
../MYLIB/Src/control_pid_regulator.c \
../MYLIB/Src/deviceloop.c \
../MYLIB/Src/f303_Init.c \
../MYLIB/Src/isr.c \
../MYLIB/Src/protocol.c \
../MYLIB/Src/saykal_io.c \
../MYLIB/Src/sensor_converter.c 

OBJS += \
./MYLIB/Src/can_receiver.o \
./MYLIB/Src/can_transmitter.o \
./MYLIB/Src/control_pid_regulator.o \
./MYLIB/Src/deviceloop.o \
./MYLIB/Src/f303_Init.o \
./MYLIB/Src/isr.o \
./MYLIB/Src/protocol.o \
./MYLIB/Src/saykal_io.o \
./MYLIB/Src/sensor_converter.o 

C_DEPS += \
./MYLIB/Src/can_receiver.d \
./MYLIB/Src/can_transmitter.d \
./MYLIB/Src/control_pid_regulator.d \
./MYLIB/Src/deviceloop.d \
./MYLIB/Src/f303_Init.d \
./MYLIB/Src/isr.d \
./MYLIB/Src/protocol.d \
./MYLIB/Src/saykal_io.d \
./MYLIB/Src/sensor_converter.d 


# Each subdirectory must supply rules for building sources it contributes
MYLIB/Src/%.o MYLIB/Src/%.su MYLIB/Src/%.cyclo: ../MYLIB/Src/%.c MYLIB/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F303xE -c -I../Core/Inc -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I../Drivers/CMSIS/Include -I"D:/software/Saykal/repo/Buck_Converter_Pid_Control/buck_converter_f303ret6/MYLIB/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MYLIB-2f-Src

clean-MYLIB-2f-Src:
	-$(RM) ./MYLIB/Src/can_receiver.cyclo ./MYLIB/Src/can_receiver.d ./MYLIB/Src/can_receiver.o ./MYLIB/Src/can_receiver.su ./MYLIB/Src/can_transmitter.cyclo ./MYLIB/Src/can_transmitter.d ./MYLIB/Src/can_transmitter.o ./MYLIB/Src/can_transmitter.su ./MYLIB/Src/control_pid_regulator.cyclo ./MYLIB/Src/control_pid_regulator.d ./MYLIB/Src/control_pid_regulator.o ./MYLIB/Src/control_pid_regulator.su ./MYLIB/Src/deviceloop.cyclo ./MYLIB/Src/deviceloop.d ./MYLIB/Src/deviceloop.o ./MYLIB/Src/deviceloop.su ./MYLIB/Src/f303_Init.cyclo ./MYLIB/Src/f303_Init.d ./MYLIB/Src/f303_Init.o ./MYLIB/Src/f303_Init.su ./MYLIB/Src/isr.cyclo ./MYLIB/Src/isr.d ./MYLIB/Src/isr.o ./MYLIB/Src/isr.su ./MYLIB/Src/protocol.cyclo ./MYLIB/Src/protocol.d ./MYLIB/Src/protocol.o ./MYLIB/Src/protocol.su ./MYLIB/Src/saykal_io.cyclo ./MYLIB/Src/saykal_io.d ./MYLIB/Src/saykal_io.o ./MYLIB/Src/saykal_io.su ./MYLIB/Src/sensor_converter.cyclo ./MYLIB/Src/sensor_converter.d ./MYLIB/Src/sensor_converter.o ./MYLIB/Src/sensor_converter.su

.PHONY: clean-MYLIB-2f-Src

