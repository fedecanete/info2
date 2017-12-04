################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FW_Drivers/Entradas_FW.c \
../src/FW_Drivers/FW_7Seg.c \
../src/FW_Drivers/FW_GPIO.c \
../src/FW_Drivers/FW_LCD.c \
../src/FW_Drivers/FW_SSP1.c \
../src/FW_Drivers/FW_Systick.c \
../src/FW_Drivers/FW_nRF.c \
../src/FW_Drivers/KitInfo2FW_Teclado.c 

OBJS += \
./src/FW_Drivers/Entradas_FW.o \
./src/FW_Drivers/FW_7Seg.o \
./src/FW_Drivers/FW_GPIO.o \
./src/FW_Drivers/FW_LCD.o \
./src/FW_Drivers/FW_SSP1.o \
./src/FW_Drivers/FW_Systick.o \
./src/FW_Drivers/FW_nRF.o \
./src/FW_Drivers/KitInfo2FW_Teclado.o 

C_DEPS += \
./src/FW_Drivers/Entradas_FW.d \
./src/FW_Drivers/FW_7Seg.d \
./src/FW_Drivers/FW_GPIO.d \
./src/FW_Drivers/FW_LCD.d \
./src/FW_Drivers/FW_SSP1.d \
./src/FW_Drivers/FW_Systick.d \
./src/FW_Drivers/FW_nRF.d \
./src/FW_Drivers/KitInfo2FW_Teclado.d 


# Each subdirectory must supply rules for building sources it contributes
src/FW_Drivers/%.o: ../src/FW_Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Repositorio\info2\RF\nRF24l01\test_RF_v2\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


