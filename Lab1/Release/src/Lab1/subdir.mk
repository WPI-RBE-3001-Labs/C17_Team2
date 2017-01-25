################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Lab1/ADC.c \
../src/Lab1/USARTDebug.c \
../src/Lab1/main.c \
../src/Lab1/squareWave.c 

OBJS += \
./src/Lab1/ADC.o \
./src/Lab1/USARTDebug.o \
./src/Lab1/main.o \
./src/Lab1/squareWave.o 

C_DEPS += \
./src/Lab1/ADC.d \
./src/Lab1/USARTDebug.d \
./src/Lab1/main.d \
./src/Lab1/squareWave.d 


# Each subdirectory must supply rules for building sources it contributes
src/Lab1/%.o: ../src/Lab1/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"R:\RBE3001\rbelib-17.1.0\rbelib-17.1.0\RBELib\include" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=18432000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


