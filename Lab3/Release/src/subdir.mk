################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/ADC.c \
../src/DAC.c \
../src/PID.c \
../src/Periph.c \
../src/SPI.c \
../src/USART.c \
../src/arm.c \
../src/button.c \
../src/main.c \
../src/motors.c \
../src/pot.c \
../src/sensors.c 

OBJS += \
./src/ADC.o \
./src/DAC.o \
./src/PID.o \
./src/Periph.o \
./src/SPI.o \
./src/USART.o \
./src/arm.o \
./src/button.o \
./src/main.o \
./src/motors.o \
./src/pot.o \
./src/sensors.o 

C_DEPS += \
./src/ADC.d \
./src/DAC.d \
./src/PID.d \
./src/Periph.d \
./src/SPI.d \
./src/USART.d \
./src/arm.d \
./src/button.d \
./src/main.d \
./src/motors.d \
./src/pot.d \
./src/sensors.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"C:\Users\bdknox\git\rbelib\RBELib\include" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega644p -DF_CPU=18432000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


