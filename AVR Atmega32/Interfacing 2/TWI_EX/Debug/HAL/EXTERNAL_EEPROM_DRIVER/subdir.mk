################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/EXTERNAL_EEPROM_DRIVER/external_eeprom.c 

OBJS += \
./HAL/EXTERNAL_EEPROM_DRIVER/external_eeprom.o 

C_DEPS += \
./HAL/EXTERNAL_EEPROM_DRIVER/external_eeprom.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/EXTERNAL_EEPROM_DRIVER/%.o: ../HAL/EXTERNAL_EEPROM_DRIVER/%.c HAL/EXTERNAL_EEPROM_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


