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

extern volatile uint8_t nRF_Status_Reg;

volatile char hello[]="Hello";
volatile char hallo[]="Hallo";
volatile char holis[]="Holis";
volatile char master[]="Soy Master";
volatile char *msg_ptr=hello;
volatile uint8_t start=1;
volatile uint8_t led_blink=0;
volatile uint8_t msj=0;
volatile uint8_t delay=0;

volatile uint8_t msg_cad[2]={0,'\0'};
volatile uint8_t estado = REPOSO;

void Aplicacion(void) {

		uint8_t i,test;
		Display (segundos);
		switch(estado){

		case REPOSO:
						if (start){
							start=0;
							segundos=0;
							delay=T_3SEG;
							DisplayLCD("---> Ready <----",0,0);//msg, renglon, offset
							DisplayLCD("                ",1,0);
							LED_ROJO_ON;
							led_blink=0;
						}else if(!delay){
							estado = ENVIAR;
							start=1;
							LED_ROJO_OFF;
						}
						break;

		case ENVIAR:
						if (start){
							start=0;
							delay=T_5SEG;
							led_blink=1;
							DisplayLCD("Enviando:       ",0,0);
							DisplayLCD (msg_ptr,0,10); //Muestro lo que mandé

						}
						Transmit_Payload (msg_ptr, 5);
						Clear_Status();
						if(!delay){
							estado = CAMBIAR_MSJ;
							start=1;
							led_blink=0;
							LED_VERDE_OFF;
							DisplayLCD("                ",1,0);
							delay=T_5SEG;
						}
						break;

		case CAMBIAR_MSJ:
							if (start){
								test=nRF_GetReg(FIFO_STATUS);
								DisplayLCD("FIFO_r:        ",0,0);
								for (i=0;i<8;i++){

									msg_cad[0]= (test & (1<<i)) ? '1' : '0';
									DisplayLCD (msg_cad,0,15-i);
								}
								DisplayLCD("Status:",1,0);
								for (i=0;i<8;i++){

									msg_cad[0]= (nRF_Status_Reg & (1<<i)) ? '1' : '0';
									DisplayLCD (msg_cad,1,15-i);
								}
								start=0;
								switch (msj){
								case 2: msg_ptr=hallo;
										break;
								case 0: msg_ptr=holis;
										break;
								case 1: msg_ptr=hello;
										break;
								}
								msj++;
								msj%=3;

							}else if (!delay){
								if (msj==2)estado = REPOSO;
								else estado = ENVIAR;
								DisplayLCD("                ",1,0);
								start=1;
							}
						break;

		default:
						break;
	}

}
