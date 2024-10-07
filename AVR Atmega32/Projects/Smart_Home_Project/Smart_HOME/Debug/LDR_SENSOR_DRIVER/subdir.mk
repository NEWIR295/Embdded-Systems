################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../LDR_SENSOR_DRIVER/ldr_sensor.c 

OBJS += \
./LDR_SENSOR_DRIVER/ldr_sensor.o 

C_DEPS += \
./LDR_SENSOR_DRIVER/ldr_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
LDR_SENSOR_DRIVER/%.o: ../LDR_SENSOR_DRIVER/%.c LDR_SENSOR_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


