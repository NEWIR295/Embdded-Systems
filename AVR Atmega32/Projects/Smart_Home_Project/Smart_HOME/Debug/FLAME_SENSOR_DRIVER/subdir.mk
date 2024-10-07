################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FLAME_SENSOR_DRIVER/flame_sensor.c 

OBJS += \
./FLAME_SENSOR_DRIVER/flame_sensor.o 

C_DEPS += \
./FLAME_SENSOR_DRIVER/flame_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
FLAME_SENSOR_DRIVER/%.o: ../FLAME_SENSOR_DRIVER/%.c FLAME_SENSOR_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


