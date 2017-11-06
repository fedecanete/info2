/**
 	\file FW_Teclado5x1.c
 	\brief
 	\details
 	\author
 	\date
*/

#include "Aplicacion.h"

// Buffer de teclado
extern volatile uint8_t buffKey;

void DriverTeclado(void)
{
	uint8_t CodigoActual ;
	CodigoActual = TecladoHW( );
	TecladoSW( CodigoActual );
}


void TecladoSW (uint8_t codAct){
   static uint8_t codAnt = NO_KEY;
   static uint8_t estado = REPOSO;
   static uint8_t cont = 0; //no es necesario inicializarla

   if (codAct == NO_KEY)
   { //mientras NO se oprima tecla SIEMPRE
      codAnt = NO_KEY;	//entraré acá
      estado = REPOSO;
      return;
   }

   if (estado == DETECCION)
   {
      if (codAnt != codAct)
    	  codAnt = codAct;
      else {
    	  estado = CHEQUEO;
    	  cont = CANT_REBOTES;
      }
      return;
   }

   if (estado == CHEQUEO)
   {
      if (codAnt != codAct)
    	  estado = DETECCION;
      else if (cont)
    	  cont--;
      else {
    	  buffKey = codAct;
    	  estado = REPOSO;
    	  codAnt = NO_KEY;
      }
      return;
   }

   if (estado > EMERGENCIA) //por si perdí el control de la var de estado.
      estado = REPOSO;

   else{	//detecté una tecla por primera vez
      estado = DETECCION;
      codAnt = codAct;
   }
}


uint8_t TecladoHW (void)
{
	uint8_t Codigo = NO_KEY;

	if (SW1_PRESS) return 1;
	if (SW2_PRESS) return 2;
	if (SW3_PRESS) return 3;
	if (SW4_PRESS) return 4;
	if (SW5_PRESS) return 5;
    return Codigo;
}
