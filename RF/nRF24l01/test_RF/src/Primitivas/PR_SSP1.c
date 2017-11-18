/*
 * PR_SSP1.c
 *
 *  Created on: 14 de oct. de 2017
 *      Author: Federico
 */
#include "ssp.h"
#include "FW_SSP.h"
extern volatile uint8_t Buff_Tx_SSP1[TOPE_SSP1];
extern volatile uint8_t Buff_Rx_SSP1[TOPE_SSP1];		//!< Buffer de Recepción SPI
extern volatile uint8_t SSP1_RxIn_Idx;				//Índices para el manejo de los buffers
extern volatile uint8_t SSP1_RxOut_Idx;
extern volatile uint8_t SSP1_TxIn_Idx;
extern volatile uint8_t SSP1_TxOut_Idx;
extern volatile uint8_t SSP1_status;

volatile uint8_t tx_buffer_empty=1;
volatile uint8_t tx_buffer_full=0;

volatile uint8_t f_ssp1_status[4];				//Flags de estado
volatile uint8_t first_time=1;
volatile uint8_t veces=0;


// primitiva que escribe en el buffer de Tx (BufferTx), verificando TOPE e ini-
// ciando la Tx si no hay
// transmisión en curso.

uint8_t WriteTx (uint8_t dato)
{
	if (tx_buffer_full) return FULL;


	Buff_Tx_SSP1[SSP1_TxIn_Idx]=dato;
	SSP1_TxIn_Idx++;
	SSP1_TxIn_Idx%=TOPE_SSP1;

	tx_buffer_empty=0; //si agrego un dato el buffer ya no está vacío
	veces++;

	if (SSP1_TxIn_Idx == SSP1_TxOut_Idx) tx_buffer_full=1;


	if (first_time){

		first_time=0;

		Start_Transmission();

	}else{
		//Habilito interrupciones por transmisión
		SSP1IMSC |= (1 << TXIM);


	}
	if (veces<4)return WARNING;
	else {
		veces=0;
		return OK;
	}



}

uint8_t ReadRx (void)
{
	if(SSP1_RxOut_Idx == SSP1_RxIn_Idx) return EMPTY;
	//Si no está vacío trabaja con los índices lo devuelve
	uint8_t dato= Buff_Rx_SSP1[SSP1_RxIn_Idx];
	SSP1_RxIn_Idx++;
	SSP1_RxIn_Idx%=TOPE_SSP1;
	return dato;
}

void EmptyRxFIFO (void)
{
 /* A veces pasa que los datos que están en el RxFIFO no generan interrupción
  * pero se encuentran sin leer (si guardar)
  */
	SSP_Status();
	if (RXFIFO_NOT_EMPTY){
		do {
			ReceiveSSP1();
			SSP_Status();
		}while (RXFIFO_NOT_EMPTY);

	}



}

