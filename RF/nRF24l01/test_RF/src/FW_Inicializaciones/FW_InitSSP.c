/*
 * FW_InitSSP.c
 *
 *  Created on: 13 de oct. de 2017
 *      Author: fedec
 */


#include "Aplicacion.h"
#include "FW_SSP.h"
volatile uint8_t Dummy;
void Inicializar_SSP1 (void){

	uint8_t i;
	//1.- Activo la alimentacion del dispositivo desde el registro PCONP:
	SSP1_ON;

	//2.- Selecciono el clock del módulo como 100MHz (01: CCLK/1)
	PCLKSEL0 &= ~(3 << PCLK_SSP1);
	PCLKSEL0 |= (01<< PCLK_SSP1);

	//3.- Pines: Todos en función "10"
	SetPINSEL (MOSI1,2);
	SetPINSEL (MISO1,2);
	SetPINSEL (SCK1,2);
	SetPINSEL (SSEL1,2);

	//4.- Prescaler: SSPn Clock Prescale Register - Lo configuro para que divida por 100 (debe ser número par mayor a 2)
	//Entonces trabajará a 1MHz
	SSP1CPSR |= 100;

	//5.- Configuro tamaño de datos (8 bits), modo SPI, bits de control CPOL Y CPHA en el registro CR0 (SSP1CR0)
	SSP1CR0 &= ~(3 << 4); //Modo SPI: 00 en bits 4 y 5 (FRF)
	SSP1CR0 |= 7; //0111: 8-bit transfer
	SSP1CR0 &= ~(3 << 6); //CPOL Y CPHA en 00 (Bits 6 y 7)

	//6.- Configuro modo Master en el registro CR1 (SSP1CR1)
	SSP1CR1 &= ~(1 << CR1_MS); //Modo master: 0 en MS (bit 2)

	//7.- Interrupciones:
	//Por precaución cleareo todos los bits de interrupción
	SSP1IMSC &= ~(1 << RORIM);
	SSP1IMSC &= ~(1 << RTIM);
	SSP1IMSC &= ~(1 << RXIM);
	SSP1IMSC &= ~(1 << TXIM);
	//Configuro para que interrumpa si el RX FIFO está por lo menos medio lleno
	//Registro SSP1IMSC, bit 2
	//SSP1IMSC |= (1 << RXIM);

	//Configuro para que interrumpa si se produjo un Receive Time-out
	//SSP1IMSC |= (1 << RTIM);

	//Interrumpe si Tx FIFO esta por lo menos medio vacío
	//SSP1IMSC |= (1 << TXIM);


	//8.- Se debe limpiar el FIFO (8 bytes) de Rx para que no moleste
	for (i=0; i<8; i++) Dummy = SSP1DR;

	//9.- Vectorizar NVIC
	//ISER0 |= (1 << ISE_SSP1);

	//10.- Habilito el módulo
	SSP1CR1 &= ~(1 << CR1_LBM);
	//SSP1CR1 |= (1 << CR1_LBM); //Loop Back Mode: retroalimento lo que envío (bit 0)
	SSP1CR1 |= (1 << CR1_SSE); //Enable: SSE en 1 (bit 1)


}

