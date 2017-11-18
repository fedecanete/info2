/**
 	\file KitInfo2FW_Teclado.c
 	\brief Driver Driver de teclado
 	\details Expansion 4
 	\author Ing. Marcelo Trujillo
 	\date 2012.04.25
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
   uint8_t cont = 0; //no es necesario inicializarla

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
	uint8_t i;
	// Escanea Columna 0
	SetPIN(COL0,OFF);
	SetPIN(COL1,ON);
	for(i = 0; i < 0x10; i++);						// Si repetimos SetPIN no alcanzamos a demorar lo suficinte
	if (GetPIN(FILA0,ACTIVO_BAJO)) return SW4;
	if (GetPIN(FILA1,ACTIVO_BAJO)) return SW1;
	if (GetPIN(FILA2,ACTIVO_BAJO)) return SW3;
	if (GetPIN(FILA3,ACTIVO_BAJO)) return SW2;

	// Escanea Columna 1
	SetPIN(COL0,ON);
	SetPIN(COL1,OFF);
	for(i = 0; i < 0x10; i++);						// Si repetimos SetPIN no alcanzamos a demorar lo suficinte
	if (GetPIN(FILA0,ACTIVO_BAJO)) return SW5;		// El problema de no demorar se manifiesta acá, da siempre SW4 sin demora
	if (GetPIN(FILA1,ACTIVO_BAJO)) return SW8;
	if (GetPIN(FILA2,ACTIVO_BAJO)) return SW6;
	if (GetPIN(FILA3,ACTIVO_BAJO)) return SW7;

	return NO_KEY;

}
