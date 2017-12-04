#include "KitInfo2_BaseBoard.h"
#include "Aplicacion.h"

extern volatile uint8_t TmrRun[];
extern volatile uint8_t Eventos;

//******************************************************************************************
//	Proposito: Lanzamientos de Timers.
//	Parametros:
//                  ev : Numero de Timer
//                  t : valor de Timer.
//	Retorna: void.
//******************************************************************************************
void TmrStart(uint8_t ev,uint8_t t){		//void TmrStart(EVENTO ev,TIEMPO t)
	TICKINT = OFF;
	if(t){
		TmrRun[ev] = t;
		Eventos &= ~((uint8_t)0x01 << ev);
	}
	else {
		TmrRun[ev]=0;
		Eventos &= ~((uint8_t)0x01 << ev);
	}
	TICKINT = ON;
}

//******************************************************************************************
//	Proposito: Apaga todo los timers
//	Parametros: void
//	Retorna: void.
//******************************************************************************************
void TmrClose(void){
	uint8_t i;
	TICKINT = OFF;
	for (i=0 ; i<TIMERS ;  i++)
  		TmrRun[i] = 0;
  	Eventos = 0;
  	TICKINT = ON;
}

//*******************************************************************************************
//	Proposito: Apaga un timer en particular
//	Parametros: void
//	Retorna: void.
//*******************************************************************************************
void TmrStop (uint8_t ev) {
	TICKINT = OFF;
	TmrRun[ev] = 0;
  	Eventos &= ~((uint8_t) 0x01 << ev);
  	TICKINT = ON;
}



//*******************************************************************************************
//	Proposito: Analiza Eventos de timers. No es una primitiva. Es parte o toda la aplicación
//				La ubico en este .c para tener todas las funciones de timers juntas.
//	Parametros: void.
//	Retorna: void.
//*******************************************************************************************
void TmrEvent(void)
{
	/*uint8_t i;
    for(i=0x01 ; i ; i <<= 1)
    {
        switch( Eventos &  i )
        {
			case 0x01:	//venció EVENTO0
				led1_exp1 = !led1_exp1;
				led1_exp1 ? SetPIN (LED1_EXP1, ON): SetPIN (LED1_EXP1, OFF);
				TmrStart(EVENTO0, T0);
  				LIMPIObANDERA;
   	         	break;

            case 0x02:	//venció EVENTO1
				led2_exp1 = !led2_exp1;
				led2_exp1 ? SetPIN (LED2_EXP1, ON): SetPIN (LED2_EXP1, OFF);
				TmrStart(EVENTO1, T1);
            	LIMPIObANDERA;
               	break;

            case 0x04 :	//venció EVENTO2
				led3_exp1 = !led3_exp1;
				led3_exp1 ? SetPIN (LED3_EXP1, ON): SetPIN (LED3_EXP1, OFF);
				TmrStart(EVENTO2, T2);
            	LIMPIObANDERA;
				break;

            case 0x08 : //venció EVENTO3
				led4_exp1 = !led4_exp1;
				led4_exp1 ? SetPIN (LED4_EXP1, ON): SetPIN (LED4_EXP1, OFF);
				TmrStart(EVENTO3, T3);
            	LIMPIObANDERA;
               	break;

            case 0x10: //venció EVENTO4
            	LIMPIObANDERA;
               	break;

            case 0x20:	//venció EVENTO5
            	LIMPIObANDERA;
               	break;

            case 0x40:	//venció EVENTO6
            	LIMPIObANDERA;
               	break;

            case 0x80:	//case 0x80
            	LIMPIObANDERA;
               	break;
	       }
    }*/
}

//******************************************************************************************
//	Proposito: 	Descuento de Timers. No es una primitiva. Es una función de la capa inferior.
//				La ubico en este .c para tener todas las funciones de timers juntas.
//	Parametros:
//                  Ev : Numero de Timer
//	Retorna: void.

void AnalizarTimer(void) {
	uint8_t i;

	for (i=0; i<TIMERS; i++){
		if (TmrRun[ i ])
   		{
   			TmrRun[i]--;
	   		if( !TmrRun[i] ){
	   			Eventos |= ((uint8_t) 0x01 << i) ;
	   		}
		}
	}
}

//******************************************************************************************

