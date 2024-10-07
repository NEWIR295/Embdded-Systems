################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/buttons.c \
../src/gpio.c \
../src/interrupts.c \
../src/main.c \
../src/sevenSegment.c 

OBJS += \
./src/buttons.o \
./src/gpio.o \
./src/interrupts.o \
./src/main.o \
./src/sevenSegment.o 

C_DEPS += \
./src/buttons.d \
./src/gpio.d \
./src/interrupts.d \
./src/main.d \
./src/sevenSegment.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


