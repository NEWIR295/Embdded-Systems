################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/BUZZER_DRIVER/buzzer.c 

OBJS += \
./HAL/BUZZER_DRIVER/buzzer.o 

C_DEPS += \
./HAL/BUZZER_DRIVER/buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/BUZZER_DRIVER/%.o: ../HAL/BUZZER_DRIVER/%.c HAL/BUZZER_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

