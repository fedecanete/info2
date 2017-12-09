/*
 * FW_SPP.h
 *
 *  Created on: 13 de oct. de 2017
 *      Author: fedec
 */

#ifndef FW_SSP_H_
#define FW_SSP_H_

#include "Aplicacion.h"

#define SSP1_ON PCONP|=1<<PCSSP1
#define FULL 1
#define OK 0
#define WARNING 2
#define EMPTY 0
#define SENT 1
#define SEND_DENIED 2

#define START_TRANSMISSION SSP1DR=Buff_Tx_SSP1[SSP1_TxOut_Idx]
#define ENABLE_SSP1_INT ISER0|=(1 << ISE_SSP1)

#define RXFIFO_NOT_EMPTY f_ssp1_status[RNE]

void Inicializar_SSP1 (void);
void SSP_Status (void);

//Firmware
void ReceiveSSP1 (void);
void SendSSP1 (void);
uint8_t SendReceiveSSP (uint8_t);
void Start_Transmission (void);
//Primitivas

uint8_t WriteTx (uint8_t);
uint8_t ReadRx (void);
void EmptyRxFIFO (void);

#endif /* FW_SSP_H_ */
