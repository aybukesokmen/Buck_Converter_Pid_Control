################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MYLIB/Src/adc_reader.c \
../MYLIB/Src/can_transmitter.c \
../MYLIB/Src/control_pid_regulator.c \
../MYLIB/Src/pwm_output_driver.c \
../MYLIB/Src/sensor_converter.c \
../MYLIB/Src/system_health_monitor.c 

OBJS += \
./MYLIB/Src/adc_reader.o \
./MYLIB/Src/can_transmitter.o \
./MYLIB/Src/control_pid_regulator.o \
./MYLIB/Src/pwm_output_driver.o \
./MYLIB/Src/sensor_converter.o \
./MYLIB/Src/system_health_monitor.o 

C_DEPS += \
./MYLIB/Src/adc_reader.d \
./MYLIB/Src/can_transmitter.d \
./MYLIB/Src/control_pid_regulator.d \
./MYLIB/Src/pwm_output_driver.d \
./MYLIB/Src/sensor_converter.d \
./MYLIB/Src/system_health_monitor.d 


# Each subdirectory must supply rules for building sources it contributes
MYLIB/Src/%.o MYLIB/Src/%.su MYLIB/Src/%.cyclo: ../MYLIB/Src/%.c MYLIB/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/haydar.gungor/Desktop/Aybuke/Yeni klasör (2)/repo/Buck_Converter_Pid_Control/buck_converter_hal_library/MYLIB/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MYLIB-2f-Src

clean-MYLIB-2f-Src:
	-$(RM) ./MYLIB/Src/adc_reader.cyclo ./MYLIB/Src/adc_reader.d ./MYLIB/Src/adc_reader.o ./MYLIB/Src/adc_reader.su ./MYLIB/Src/can_transmitter.cyclo ./MYLIB/Src/can_transmitter.d ./MYLIB/Src/can_transmitter.o ./MYLIB/Src/can_transmitter.su ./MYLIB/Src/control_pid_regulator.cyclo ./MYLIB/Src/control_pid_regulator.d ./MYLIB/Src/control_pid_regulator.o ./MYLIB/Src/control_pid_regulator.su ./MYLIB/Src/pwm_output_driver.cyclo ./MYLIB/Src/pwm_output_driver.d ./MYLIB/Src/pwm_output_driver.o ./MYLIB/Src/pwm_output_driver.su ./MYLIB/Src/sensor_converter.cyclo ./MYLIB/Src/sensor_converter.d ./MYLIB/Src/sensor_converter.o ./MYLIB/Src/sensor_converter.su ./MYLIB/Src/system_health_monitor.cyclo ./MYLIB/Src/system_health_monitor.d ./MYLIB/Src/system_health_monitor.o ./MYLIB/Src/system_health_monitor.su

.PHONY: clean-MYLIB-2f-Src

