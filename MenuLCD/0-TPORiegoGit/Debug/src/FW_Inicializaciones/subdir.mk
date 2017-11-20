################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FW_Inicializaciones/FW_InicDisplays7seg.c \
../src/FW_Inicializaciones/FW_InicLCD.c \
../src/FW_Inicializaciones/FW_InicRTC.c \
../src/FW_Inicializaciones/FW_InicSysTick.c \
../src/FW_Inicializaciones/FW_InicTeclado5x1.c \
../src/FW_Inicializaciones/FW_InitBaseBoard.c \
../src/FW_Inicializaciones/FW_InitOscilador.c 

OBJS += \
./src/FW_Inicializaciones/FW_InicDisplays7seg.o \
./src/FW_Inicializaciones/FW_InicLCD.o \
./src/FW_Inicializaciones/FW_InicRTC.o \
./src/FW_Inicializaciones/FW_InicSysTick.o \
./src/FW_Inicializaciones/FW_InicTeclado5x1.o \
./src/FW_Inicializaciones/FW_InitBaseBoard.o \
./src/FW_Inicializaciones/FW_InitOscilador.o 

C_DEPS += \
./src/FW_Inicializaciones/FW_InicDisplays7seg.d \
./src/FW_Inicializaciones/FW_InicLCD.d \
./src/FW_Inicializaciones/FW_InicRTC.d \
./src/FW_Inicializaciones/FW_InicSysTick.d \
./src/FW_Inicializaciones/FW_InicTeclado5x1.d \
./src/FW_Inicializaciones/FW_InitBaseBoard.d \
./src/FW_Inicializaciones/FW_InitOscilador.d 


# Each subdirectory must supply rules for building sources it contributes
src/FW_Inicializaciones/%.o: ../src/FW_Inicializaciones/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"E:\Arturo\UTN\2017\Info2\Info2_git\info2\MenuLCD\0-TPORiegoGit\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


