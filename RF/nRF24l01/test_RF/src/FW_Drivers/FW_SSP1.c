/*
 * FW_SSP1.c
 *
 *  Created on: 15 de oct. de 2017
 *      Author: Federico
 */
#include "Aplicacion.h"

extern volatile uint8_t Buff_Tx_SSP1[TOPE_SSP1];		//!< Buffer de Transmisión SPI
extern volatile uint8_t Buff_Rx_SSP1[TOPE_SSP1];		//!< Buffer de Recepción SPI
extern volatile uint8_t f_ssp1_status[4];				//Flags de estado
extern volatile uint8_t SSP1_RxIn_Idx;				//Índices para el manejo de los buffers
extern volatile uint8_t SSP1_RxOut_Idx;
extern volatile uint8_t SSP1_TxIn_Idx;
extern volatile uint8_t SSP1_TxOut_Idx;

extern volatile uint8_t tx_buffer_empty;
extern volatile uint8_t tx_buffer_full;

extern volatile uint8_t first_time;


volatile uint8_t f_ssp1_int[4];					//Flags de interrupciones
volatile uint32_t interrupciones=0;
volatile uint8_t SSP1_status;


//La interrupción llega cuando se está llenando el FIFO de recepción
void SSP1_IRQHandler(void){

//Primero determino la causa de la interrupción (aunque ya la sepa en este caso: RXMIS)
	//**** TODOS ESTOS FLAGS SE PONEN EN 1 SI Y SÓLO SI SU INTERRUPCION CORRESPONDIENTE ESTABA HABILITADA******//

	if (SSP1MIS & (1 << RORMIS)) //Receive Overrun. Si se recibió completamente un frame y el Rx FIFO estaba lleno (HUBO SOBREESCRITURA)
		f_ssp1_int[RORMIS] = 1;

	if (SSP1MIS & (1 << RTMIS)){ //Receive Time-Out. El dato estuvo demasiado tiempo en el Rx FIFO

		f_ssp1_int[RTMIS] = 1;
		SSP1ICR |= (1 << RTIC); //Clear the interrupt condition
	}


	if (SSP1MIS & (1 << TXMIS))  //El Tx FIFO está por lo menos medio vacío = Hay al menos 4 lugares para transmitir

		SendSSP1();


	if (SSP1MIS & (1 << RXMIS)){//El Rx FIFO está por lo menos medio lleno

		ReceiveSSP1();

	}

	interrupciones++;

}

void SendSSP1 (void)
{
	//Primero se fija que haya dato
	if(!tx_buffer_empty){
		//Si entró que sí hay algo para enviar
		Start_Transmission();
		tx_buffer_full=0;
		//Se deshabilita la interrupción por Tx FIFO (porque sino entra siempre y pierde tiempo)
		SSP1IMSC &= ~(1 << TXIM);


		//if (SSP1_TxIn_Idx == SSP1_TxOut_Idx)
		//tx_buffer_empty=1;	//se vació el buffer

	}else {
		//Si está vacío aviso que puedo comenzar la próxima vez


		first_time=1;

	}

}
void Start_Transmission (void)
/**
 * Importante:
 * Como el módulo solo interrumpe cuando se medio llenó el FIFO de recepción,
 * sí o sí estoy obligado a enviar por lo menos 4 datos (el FIFO tiene 8)
 * así me interrumpe cuando lleguen y los puedo guardar
 *
 */
{
	//Debe esperar a que el periférico se desocupe y además el Tx FIFO no esté lleno
		while (SSP1SR & (1<<BSY) || !(SSP1SR & (1<<TNF)));
	//Al escribir en el registro DR (SSP1DR) se inicia automáticamente el proceso de envío.
		SSP1DR = Buff_Tx_SSP1[SSP1_TxOut_Idx];
	//Control de índices
		SSP1_TxOut_Idx++;
		SSP1_TxOut_Idx%=TOPE_SSP1;
	//Espera a que se termine de enviar
		while (SSP1SR & (1<<BSY));

}


void ReceiveSSP1 (void)
{
	//No agrego protección por sobreescritura
	do{
	//Espera a que el módulo se desocupe (BSY='0')
		while (SSP1SR & (1 << BSY));
		Buff_Rx_SSP1[SSP1_RxOut_Idx] = SSP1DR;
		SSP1_RxOut_Idx++;
		SSP1_RxOut_Idx %= TOPE_SSP1;
	}while (SSP1SR & (1 << RNE)); //Mientras me diga que está no vacío

}
/**
 * @brief Envía un char por SPI y recibe otro, guardándolo y notificando
 * @param dato Es el char a enviar al SSP1
 * @return Dato recibido
 * OJO porque esta funcion demora más y sólo puede usarla el MASTER (debido al orden enviar-recibir)
 */
uint8_t SendReceiveSSP (uint8_t dato){

	//Espera a que haya lugar en el transmisor (TNF='0') y a que se
	//desocupe el módulo (BSY='0')
	while (SSP1SR & (1<<BSY) || !(SSP1SR & (1<<TNF)));
	//Transmite el dato

	SSP1DR = dato;
	//Espera a que haya llegado el dato (RNE='1') y el módulo no esté ocupado
	while (SSP1SR & (1<<BSY) || !(SSP1SR & (1 << RNE)));


	return (uint8_t)SSP1DR;

}

void SSP_Status (void)
{
	if (SSP1SR & (1 << TFE)){
		f_ssp1_status[TFE] = 1;
	}
	else {
		f_ssp1_status[TFE] = 0;
	}

	if (SSP1SR & (1 << TNF)){
		f_ssp1_status[TNF] = 1;
	}
	else {
		f_ssp1_status[TNF] = 0;
	}

	if (SSP1SR & (1 << RNE)){
		f_ssp1_status[RNE] = 1;

	}
	else {
		f_ssp1_status[RNE] = 0;
	}

	if (SSP1SR & (1 << RFF)){
		f_ssp1_status[RFF] = 1;

	}
	else {
		f_ssp1_status[RFF] = 0;
	}


}
