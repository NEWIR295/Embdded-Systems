################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BUZZER_DRIVER/buzzer.c 

OBJS += \
./BUZZER_DRIVER/buzzer.o 

C_DEPS += \
./BUZZER_DRIVER/buzzer.d 


# Each subdirectory must supply rules for building sources it contributes
BUZZER_DRIVER/%.o: ../BUZZER_DRIVER/%.c BUZZER_DRIVER/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


