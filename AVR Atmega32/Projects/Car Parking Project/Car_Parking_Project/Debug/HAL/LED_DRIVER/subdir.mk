################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LED_DRIVER/led.c 

OBJS += \
./HAL/LED_DRIVER/led.o 

C_DEPS += \
./HAL/LED_DRIVER/led.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/LED_DRIVER/%.o: ../HAL/LED_DRIVER/%.c HAL/LED_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


