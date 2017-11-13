################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Drivers/DR_7Seg.c \
../src/Drivers/DR_GPIO.c \
../src/Drivers/DR_LCD.c \
../src/Drivers/DR_RTC.c \
../src/Drivers/DR_Systick.c \
../src/Drivers/DR_Teclado5x1.c \
../src/Drivers/cr_startup_lpc175x_6x.c \
../src/Drivers/crp.c 

OBJS += \
./src/Drivers/DR_7Seg.o \
./src/Drivers/DR_GPIO.o \
./src/Drivers/DR_LCD.o \
./src/Drivers/DR_RTC.o \
./src/Drivers/DR_Systick.o \
./src/Drivers/DR_Teclado5x1.o \
./src/Drivers/cr_startup_lpc175x_6x.o \
./src/Drivers/crp.o 

C_DEPS += \
./src/Drivers/DR_7Seg.d \
./src/Drivers/DR_GPIO.d \
./src/Drivers/DR_LCD.d \
./src/Drivers/DR_RTC.d \
./src/Drivers/DR_Systick.d \
./src/Drivers/DR_Teclado5x1.d \
./src/Drivers/cr_startup_lpc175x_6x.d \
./src/Drivers/crp.d 


# Each subdirectory must supply rules for building sources it contributes
src/Drivers/%.o: ../src/Drivers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\Lucas\Desktop\Git\info2\MenuLCD\0-TPORiegoGit\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


