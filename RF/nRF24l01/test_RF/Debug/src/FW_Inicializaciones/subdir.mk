################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/FW_Inicializaciones/FW_InitBaseBoard.c \
../src/FW_Inicializaciones/FW_InitExpansion3.c \
../src/FW_Inicializaciones/FW_InitKit_principal.c \
../src/FW_Inicializaciones/FW_InitOscilador.c \
../src/FW_Inicializaciones/FW_InitSSP.c \
../src/FW_Inicializaciones/FW_Init_nRF.c \
../src/FW_Inicializaciones/cr_startup_lpc176x.c 

OBJS += \
./src/FW_Inicializaciones/FW_InitBaseBoard.o \
./src/FW_Inicializaciones/FW_InitExpansion3.o \
./src/FW_Inicializaciones/FW_InitKit_principal.o \
./src/FW_Inicializaciones/FW_InitOscilador.o \
./src/FW_Inicializaciones/FW_InitSSP.o \
./src/FW_Inicializaciones/FW_Init_nRF.o \
./src/FW_Inicializaciones/cr_startup_lpc176x.o 

C_DEPS += \
./src/FW_Inicializaciones/FW_InitBaseBoard.d \
./src/FW_Inicializaciones/FW_InitExpansion3.d \
./src/FW_Inicializaciones/FW_InitKit_principal.d \
./src/FW_Inicializaciones/FW_InitOscilador.d \
./src/FW_Inicializaciones/FW_InitSSP.d \
./src/FW_Inicializaciones/FW_Init_nRF.d \
./src/FW_Inicializaciones/cr_startup_lpc176x.d 


# Each subdirectory must supply rules for building sources it contributes
src/FW_Inicializaciones/%.o: ../src/FW_Inicializaciones/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__LPC17XX__ -D__REDLIB__ -I"C:\Repositorio\info2\RF\nRF24l01\test_RF\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


