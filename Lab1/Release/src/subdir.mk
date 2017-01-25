################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC.c \
../src/USART.c \
../src/button.c \
../src/main.c \
../src/pot.c 

OBJS += \
./src/ADC.o \
./src/USART.o \
./src/button.o \
./src/main.o \
./src/pot.o 

C_DEPS += \
./src/ADC.d \
./src/USART.d \
./src/button.d \
./src/main.d \
./src/pot.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"R:\RBE3001\rbelib-17.1.0\rbelib-17.1.0\RBELib\include" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=18432000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


