################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/US_DRIVER/us.c 

OBJS += \
./HAL/US_DRIVER/us.o 

C_DEPS += \
./HAL/US_DRIVER/us.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/US_DRIVER/%.o: ../HAL/US_DRIVER/%.c HAL/US_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


