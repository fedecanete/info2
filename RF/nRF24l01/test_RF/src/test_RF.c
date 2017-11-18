/*
===============================================================================
 Name        : test_RF.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include <cr_section_macros.h>

/**
 * 07-11-17
 * Este programa utiliza una función improvisada "SendReceive" de comunicación SSP para conectarse a
 * otro kit como MASTER.
 *
 * Utiliza una máquina de estados para enviar 4 mensajes, leer lo recibido
 * y ejecutar demoras para la visualización
 ********¡¡ATENCIÓN!!******
 * Para probarlo DESHABILITAR LOOPBACK MODE en FW_InitSSP
 */

#include "Aplicacion.h"

void Aplicacion (void);

//Buffers Expansión 3 y Teclado
volatile uint8_t msgDisplay[DIGITOS];			//!< Buffer de display
volatile uint8_t BufferEntradas;				//Buffer de Entradas Digitales

//Variables para LCD
volatile int DemoraLCD;
volatile uint16_t segundos=0;
volatile int aux=0;
uint8_t bufferLCD[TOPE_BUFFER_LCD];
uint8_t msg[20];
uint8_t ptrLecturaLCD = 0;
uint8_t ptrEscrituraLCD = 0;
uint8_t entero_ascii[6];
uint8_t f_refresh_LCD = 0;


//SSP1
volatile uint8_t Buff_Tx_SSP1[TOPE_SSP1];		//!< Buffer de Transmisión SPI
volatile uint8_t Buff_Rx_SSP1[TOPE_SSP1];		//!< Buffer de Recepción SPI
volatile uint8_t flags_int_ssp1[4];				//Flags de interrupciones
volatile uint8_t SSP1_RxIn_Idx = 0;				//Índices para el manejo de los buffers
volatile uint8_t SSP1_RxOut_Idx = 0;
volatile uint8_t SSP1_TxIn_Idx = 0;
volatile uint8_t SSP1_TxOut_Idx = 0;



int main(void) {

	InicializarKit();

    while (1) {

		Aplicacion();

	}
	return 0;
}
