/*
===============================================================================
 Name        : test_rx_v1.c
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
 *03-12-17
 * Este programa es el primero que tiene las funciones de inicializacion para el nRF y
 * las funciones para enviar datos. La parte SPI a través del módulo SSP se realiza con
 * la funcion SendReceiveSSP y un buffer simple.
 * El programa hace una secuencia de textos que antes enviaba por el SPI y mostraba en
 * LCD lo que recibia (haciendo LOOP BACK MODE)
 * Esa parte del código fue deshabilitada para solamente enviar comandos de prueba al nRF
 * La funcion de inicializacion es sin parametros (es decir, tiene cosas por default, como el
 * width del payload) y no se pueden cambiar por fuera de ésta. No se hizo el codigo para
 * todo lo que sea recepcion. Eso lo hago en la proxima version. Tambien hago inicializaciones
 * parametrizadas para que sea más adaptable y menos defaultista.
 */

#include "Aplicacion.h"

void Aplicacion (void);
void uchar_to_ascii(uint8_t valor, char *ascii);

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

