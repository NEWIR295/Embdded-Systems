################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/GPIO_Driver/GPIO/gpio.c 

OBJS += \
./MCAL/GPIO_Driver/GPIO/gpio.o 

C_DEPS += \
./MCAL/GPIO_Driver/GPIO/gpio.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/GPIO_Driver/GPIO/%.o: ../MCAL/GPIO_Driver/GPIO/%.c MCAL/GPIO_Driver/GPIO/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


