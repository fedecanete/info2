/*
 * FW_nRF.h
 *
 *  Created on: 14 de nov. de 2017
 *      Author: fedec
 */

#ifndef FW_NRF_H_
#define FW_NRF_H_

#define DEFAULT_PAYLOAD_WIDTH 5

//Función que inicializa los pines del nRF24l01
void Init_HW_nRF(void);
//Función que configura el nRF como transmisor o receptor
void nRF_TxRx_Init (uint8_t, uint8_t, uint8_t, uint8_t,uint8_t);
//Cambia el modo (Rx o Tx) si ya está inicializado
void Set_Device_Mode (uint8_t);
//Función que envía (transmite por RF) un vector de chars con los datos
void Transmit_Payload (uint8_t*, uint8_t);
//Función que habilita la recepción
void Listen (void);
//Función que lee y escribe registros del nRF
void RWnRF (uint8_t cmd, uint8_t reg, uint8_t *package, uint8_t size);
//Función que lee registros de 1 byte
uint8_t nRF_GetReg (uint8_t);
//Función que limpia flags para poder seguir operando
void Clear_Status (void);
//Función que verifica si hay transmisiones RF en el mismo canal (que interfieren)
uint8_t Monitor_Air(void);
//Función que notifica la presencia de datos para leer
uint8_t Rx_Data_Ready(void);
#endif /* FW_NRF_H_ */
