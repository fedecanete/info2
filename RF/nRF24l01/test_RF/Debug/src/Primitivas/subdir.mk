################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Primitivas/KitInfo2PR_Teclado.c \
../src/Primitivas/PR_7Seg.c \
../src/Primitivas/PR_SSP1.c \
../src/Primitivas/PR_Timers.c \
../src/Primitivas/PR_nRF.c 

OBJS += \
./src/Primitivas/KitInfo2PR_Teclado.o \
./src/Primitivas/PR_7Seg.o \
./src/Primitivas/PR_SSP1.o \
./src/Primitivas/PR_Timers.o \
./src/Primitivas/PR_nRF.o 

C_DEPS += \
./src/Primitivas/KitInfo2PR_Teclado.d \
./src/Primitivas/PR_7Seg.d \
./src/Primitivas/PR_SSP1.d \
./src/Primitivas/PR_Timers.d \
./src/Primitivas/PR_nRF.d 


# Each subdirectory must supply rules for building sources it contributes
src/Primitivas/%.o: ../src/Primitivas/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Repositorio\info2\RF\nRF24l01\test_RF\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


