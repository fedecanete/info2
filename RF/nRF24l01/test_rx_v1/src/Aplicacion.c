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
volatile uint8_t nro_ascii[3];
volatile uint8_t estado = REPOSO;

extern volatile uint8_t enable_listen; //La activa el main y se deshabilita al recibir/time_out
extern volatile uint8_t data_avialable;//Flag para avisar que se escribio el SPIRxBuff

volatile uint8_t humedad_t=59;
volatile uint8_t temperatura=25;
volatile uint8_t humedad_amb=30;
volatile uint8_t motor=1;

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
							estado = LISTEN;
							start=1;
							LED_ROJO_OFF;
						}
						break;

		case LISTEN:
						if (start){
							start=0;
							delay=T_5SEG;
							LED_AZUL_ON;
							//led_blink=1;
							enable_listen=1;
							DisplayLCD("Escuchando      ",0,0);

						}

						if(!delay){
							estado = STATUS;
							start=1;
							//led_blink=0;
							DisplayLCD("                ",1,0);
							delay=T_10SEG;
							LED_AZUL_OFF;
						}
						break;

		case STATUS:
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
								i=1;

							}
							if (delay==T_5SEG && i==1){

								i=0;
								DisplayLCD("Hum: T:    A:   ",0,0);
								DisplayLCD("Temperatura:    ",1,0);

								uchar_to_ascii(humedad_t, nro_ascii);
								DisplayLCD(nro_ascii,0,7);

								uchar_to_ascii(humedad_amb, nro_ascii);
								DisplayLCD(nro_ascii,0,13);

								uchar_to_ascii(temperatura, nro_ascii);
								DisplayLCD(nro_ascii,1,13);
							}

							if (!delay){
								estado = REPOSO;
								DisplayLCD("                ",1,0);
								start=1;
							}
						break;

		default:
						break;
	}

}


/**
 * void Conversor(uint16_t valor_int)
 * Convierte un entero sin signo en ascii
 *
 * */
void uchar_to_ascii(uint8_t valor, char *ascii){ //SOLO DOS DIGITOS!! Y el último '\0'
	ascii[2]='\0';
	ascii[1] = valor % 10 +48;
	ascii[0] = valor /10 +48;

}

