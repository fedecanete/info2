/*
 * FW_nRF.h
 *
 *  Created on: 14 de nov. de 2017
 *      Author: fedec
 */

#ifndef FW_NRF_H_
#define FW_NRF_H_

//Función que inicializa los pines del nRF24l01
void Init_nRF(void);
//Función que configura el nRF como transmisor
void nRF_TxRx_Init (uint8_t, uint8_t, uint8_t, uint8_t);
//Función que envía (transmite por RF) un vector de chars con los datos
void Transmit_Payload (uint8_t*, uint8_t);
//Función que lee y escribe el nRF
void RWnRF (uint8_t cmd, uint8_t reg, uint8_t *package, uint8_t size);
uint8_t nRF_GetReg (uint8_t);
void Clear_Status (void);
#endif /* FW_NRF_H_ */
