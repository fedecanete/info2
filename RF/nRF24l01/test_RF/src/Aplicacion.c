/*
 * Aplicacion.c
 *
 *  Created on: 13 de oct. de 2017
 *      Author: fedec
 */

#include "Aplicacion.h"

//Varaibles auxiliares para manejo del LCD
extern uint8_t entero_ascii[];
extern uint8_t f_refresh_LCD;
extern volatile uint16_t segundos;
extern volatile int aux;

//Maquinaria de Timers
volatile uint8_t TmrRun[TIMERS];
volatile uint8_t Eventos = 0;

//SSP1
extern volatile uint8_t Buff_Tx_SSP1[TOPE_SSP1];		//!< Buffer de Transmisión SPI
extern volatile uint8_t Buff_Rx_SSP1[TOPE_SSP1];		//!< Buffer de Recepción SPI
extern volatile uint8_t f_ssp1_status[4];				//!< Flags de estado del SSP1 (actualizables por SSP_Status()
extern volatile uint8_t SSP1_RxIn_Idx;					//!< Índice Primitiva Rx
extern volatile uint8_t SSP1_RxOut_Idx;					//!< Índice Firmware Rx
extern volatile uint8_t SSP1_TxIn_Idx;					//!< Índice Primitiva Tx
extern volatile uint8_t SSP1_TxOut_Idx;					//!< Índice Firmware Tx
extern volatile uint32_t interrupciones;				//!< Contador de interrupciones. Sólo de uso experimental
extern volatile uint8_t SSP1_status;					//!< Not used

extern volatile uint8_t nRF_Status_Reg;

volatile char hello[]="Hello";
volatile char master[]="Soy Master";
volatile char olakease[]="ola ke ase";
volatile char hola[]="Hola";
volatile char *msg_ptr=master;
volatile uint8_t start=1;
volatile uint8_t led_blink=0;
volatile uint8_t msj=0;

volatile uint8_t msg_cad[2]={0,'\0'};
volatile uint8_t full_word=0, llenar_buffer=1;;
volatile uint8_t estado = REPOSO;

void Aplicacion(void) {


		uint8_t i=0,j=0, status, test_reg[5]={1,2,3,4,5};
		Display (segundos);
		switch(estado){

		case REPOSO:
						if (start){
							start=0;
							segundos=0;
							TmrStart(EVENTO0, T_5SEG);
							DisplayLCD("Ready           ",0,0);//msg, renglon, offset
							DisplayLCD("                ",1,0);
							LED_ROJO_ON;
							led_blink=0;
						}else if(Eventos & (1 << EVENTO0)){
							Eventos &= ~(1 << EVENTO0);
							estado = ENVIAR;
							start=1;
							LED_ROJO_OFF;
						}
						break;

		case ENVIAR:
						if (start){
							start=0;
							TmrStart(EVENTO0, T_3SEG);
							led_blink=1;
							DisplayLCD("Tx:             ",0,0);
							RWnRF (W_REGISTER, TX_ADDR, &test_reg, 5);
//							SetPIN (pin_CSN, 0);
//							status=SendReceiveSSP (R_REGISTER + TX_ADDR);
//							for (j=0;j<5;j++)
//								test_reg[j]=SendReceiveSSP(NOP);
//							SetPIN (pin_CSN, 1);
							EmptyRxFIFO();
							RWnRF (R_REGISTER, RX_ADDR_P1, &test_reg, 5);
							RWnRF (R_REGISTER, TX_ADDR, &test_reg, 5);
							RWnRF (NOP, 0, 0, 0);


//							do{
//								Buff_Rx_SSP1[SSP1_RxOut_Idx]=SendByte(*(msg_ptr+i));
//								SSP1_RxOut_Idx++;
//								SSP1_RxOut_Idx %= TOPE_SSP1;
//								i++;
//							}while (*(msg_ptr+i)!= '\0');
							DisplayLCD (msg_ptr,0,4); //Muestro lo que mandé

						}else if(Eventos & (1 << EVENTO0)){
							Eventos &= ~(1 << EVENTO0);
							estado = RECIBIR;
							start=1;
							led_blink=0;
							LED_VERDE_OFF;
							DisplayLCD("                ",0,0);
						}

		case RECIBIR:
						DisplayLCD("Rx:",1,0);
						EmptyRxFIFO(); //REEMPLAZAR CAD POR BUFFER DE CADENA GENERICO
						i=0;
						do {
							msg_cad[0]=ReadRx();
							DisplayLCD (msg_cad,1,4+i); //Muestro lo que recibí
							i++;

						}while (msg_cad[0]!= '\0' && msg_cad[0]!=EMPTY );
						estado=CAMBIAR_MSJ;
						start=1;
						break;

		case CAMBIAR_MSJ:

						if (start){
							start=0;
							TmrStart(EVENTO0, T_3SEG);
							switch (msj){
							case 2: msg_ptr=master;
									break;
							case 0: msg_ptr=hola;
									break;
							case 1: msg_ptr=hello;
									break;
//							case 2: msg_ptr=olakease;
//									break;
							}
							msj++;
							msj%=3;

						}else if(Eventos & (1 << EVENTO0)){
							Eventos &= ~(1 << EVENTO0);
							DisplayLCD("                ",1,0);
							if (msj==2)estado = REPOSO;
							else estado = ENVIAR;
							start=1;
						}
						break;

		default:
						break;
	}


//		Display (segundos);
//		//Conversor(segundos);
//		//f_refresh_LCD se activará cada 100mS
//		if (f_refresh_LCD){
//
//
//			//DisplayLCD (entero_ascii,1,0);
//			SetPIN (RGBB,0);
//			SetPIN (RGBG,0);
//
//			if (segundos==2) {
//				DisplayLCD("Ready           ",0,0);//msg, renglon, offset
//				DisplayLCD("                ",1,0);
//
//			}
//
//			if (segundos==3) {
//				DisplayLCD ("               ",0,0);
//
//			}
//			if (segundos==4) DisplayLCD ("Iniciando      ",0,0);
//
//			if (segundos ==5){
//
//				DisplayLCD ("Tx: ",0,0);//mensaje, renglon, offset
//				DisplayLCD ("Rx: ",1,0);
//				msg_ptr=hello_msg;
//			}
//
//			if (segundos>=5){
//
//				//Lleno el buffer de transmisión y muestro lo que preparo para enviar
//				//(eventualy se enviará)
//				if (llenar_buffer){
//
//					ENABLE_SSP1_INT;
//					i=0;
//					do{
//						status= WriteTx(*(msg_ptr+i));
//						msg_cad[0]=*(msg_ptr+i);
//						DisplayLCD (msg_cad,0,4+i); //Muestro lo que mandé
//						i++;
//
//					}while (*(msg_ptr+i)!= '\0' && status!=FULL );
//
//					//Al salir de la transmisión:
//					//A VECES LA INTERRUPCION NO TERMINA DE VACIAR EL RX FIFO
//					EmptyRxFIFO();
//					full_word=1;
//                     llenar_buffer=0;
//
//				}
//
//
//				if (full_word){ //pregunto si terminó de completarse la recepción y el llenado del buffer rx
//					i=0;
//					full_word=0;
//					SetPIN (RGBG,1); //Indico con LED verde el fin de recepción
//					SetPIN (RGBB,0);
//					do {
//						msg_cad[0]=ReadRx();
//						DisplayLCD (msg_cad,1,4+i); //Muestro lo que recibí
//						i++;
//
//					}while (msg_cad[0]!= '\0' && msg_cad[0]!=EMPTY );
//					llenar_buffer=1;
//
//
//				}
//
//
//			}
//			if (segundos==10)msg_ptr=ans;
//
//		}
//		f_refresh_LCD = 0;
//

//		for (i=0;i<TOPE_SSP1; i++)Buff_Rx_SSP1[i]=0;
//		msg_ptr=ans;
//		i=0;
//
//		do{
//						status= WriteTx(*(msg_ptr+i));
//						i++;
//				}while (*(msg_ptr+i)!= '\0' && status!=FULL );
//		EmptyRxFIFO();
//
//
//		interrupciones=0;


}
