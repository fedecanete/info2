/*
 * PR_nRF.c
 *
 *  Created on: 14 de nov. de 2017
 *      Author: fedec
 */
#include "Aplicacion.h"
extern volatile uint8_t delay_nRF;
volatile uint8_t nRF_Status_Reg;


void RWnRF (uint8_t cmd, uint8_t reg, uint8_t *package, uint8_t size)
{
	uint8_t i;

	/* Para los comandos de escritura y lectura de registros, es necesario "adosar"
	 * el registro en cuestión a la instrucción de lectura/escritura
	 */
	SetPIN(pin_CSN,0); //Notifico que comienza secuencia de transmisión

	if (cmd == W_REGISTER)
		//Si se quiere escribir algún registro, necesito adherir la instrucción Write: 001AAAAA
		//En cambio la de lectura es 0x000AAAAA, así que no tengo que adherir nada
		nRF_Status_Reg=SendReceiveSSP (W_REGISTER+reg);
		//Siempre que mando el comando obtengo el Status Register
	else if (cmd == R_REGISTER)
		nRF_Status_Reg=SendReceiveSSP (R_REGISTER+reg);	//Lo pongo a modo de documentación
			//Tal vez hagan falta demoras
	else
		nRF_Status_Reg=SendReceiveSSP (cmd);

	/***IMPORTANTE****/
	/* El siguiente for sólo se realizará si size>0, es decir para instrucciones
	 * que requieran size Data Bytes.
	 * Si la instrucción enviada no necesita Data Bytes (FLUSH_TX, FLUSH_RX, REUSE_TX_PL ó NOP)
	 * entonces al llamar a la función RWnRF SE DEBE poner size en '0'.
	 */

	for (i=0; i<size;i++)
	{
		if (cmd == R_REGISTER || cmd == R_RX_PAYLOAD)
		{
			//Falta ver lo de TX_PAYLOAD
			//Como voy a recibir no me importa lo que mando
			*(package+i)=SendReceiveSSP(NOP);
			//delay?

		}
		else if (cmd == W_REGISTER || cmd == W_TX_PAYLOAD)
		{
			//Lo que envío lo leo del paquete y no me preocupo por lo que recibo (basura)
			SendReceiveSSP(*(package+i));//dont care about return value
			//delay?
		}

	}
	SetPIN(pin_CSN, 1); //vuelve a estado iddle


}



uint8_t nRF_GetReg (uint8_t reg)
{
	uint8_t aux;
	if (reg>=RX_ADDR_P0 && reg<=TX_ADDR) return 0xFF;//Rango no válido para 1 byte
	else RWnRF (R_REGISTER, reg, &aux, 1);
	return aux;

}
void Clear_Status (void)
//After every received/transmitted payload the IRQ's
//in the nRF has to be reset in order to receive/transmit next package
{
	uint8_t aux=0x70; //Clear (1) to bits 6,5 and 4
	RWnRF (W_REGISTER, STATUS, &aux, 1);


}
