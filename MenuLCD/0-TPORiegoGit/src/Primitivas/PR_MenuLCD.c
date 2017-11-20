/**
 * \file PR_MenuLCD.c
 * \brief Primitiva del LCD
 */

/*!
*	\fn Menu_LCD (uint8_t TeclaPulsada)
*	\brief Función que permite utilizar el LCD a modo de menú.
*	\details Esta función recoge los datos de humedad y temperatura para mostrarlos en un LCD de
*				manera interactiva mediante diferentes pantallas (escrituras) en el LCD, las
*				cuales pueden ser recorridas mediante las teclas pulsadas en el teclado 5x1.
*				Además se permite la configuración de horas automáticas de riego, de la hora, la
*				fecha y valores críticos.
*	\author Lucas
*	\date 07.11.2017
*	\param TeclaPulsada Nos dice la tecla que fue pulsada.
*/

#include "Aplicacion.h"

<<<<<<< HEAD
extern volatile uint8_t Humedad_T;
extern volatile uint8_t	Temperatura;
extern volatile uint8_t Humedad;
=======
extern volatile uint8_t flag_IntMinutos;
extern volatile uint8_t Temperatura;
extern volatile uint8_t Humedad_A;
extern volatile uint8_t Humedad_T;
>>>>>>> 2edd432577076170eb85b31bfef12c9d077279d8

void Menu_LCD (uint8_t TeclaPulsada) {

	static uint8_t Pantalla=Pantalla_Menu;		// Contiene la pantalla actual
	static uint8_t PantallaAnt=Pantalla_Menu; 	// Contiene la pantalla anterior
	static uint8_t PosCursor=FLECHA_TIERRA; 	// Contiene el comando para darle una posición al cursor del LCD
	static uint8_t HumedadAAnt=0; 				// Contiene la humedad registrada anteriormente a Humedad_A
	static uint8_t TemperaturaAnt=0; 			// Contiene la temperatura registrada anteriormente a Temperatura
	static uint8_t HumedadTAnt=0; 				// Contiene la humedad registrada anteriormente a Humedad_T

	if (PantallaAnt==Pantalla_Menu && flag_IntMinutos) {
		ActualizarHora(PosCursor);
	}

	if (PantallaAnt==Pantalla_Tierra && HumedadTAnt!=Humedad_T) {
		//Si permanezco en Pantalla_Tierra y cambió Humedad_T:
		ActualizarTierra (Humedad_T);
		HumedadTAnt=Humedad_T; //Actualizo estas variables para no caer siempre en este if
	}

	if (PantallaAnt==Pantalla_Ambiente && (TemperaturaAnt!=Temperatura || HumedadAAnt!=Humedad_A)) {
		//Si permanezco en Pantalla_Ambiente y cambiaron los registros de temperatura o humedad:
		ActualizarAmbiente (Temperatura, Humedad_A);
		TemperaturaAnt=Temperatura;
		HumedadAAnt=Humedad_A;
	}

	if ((TeclaPulsada != NO_KEY) || (Pantalla != PantallaAnt)) {
		/* Si una tecla es pulsada o si hubo un cambio de pantalla:
		 * Utilizo la pantalla actual para pararme en ella y proceder con el menú:
		 */

		switch (Pantalla) {

			case Pantalla_Menu:
				if (Pantalla != PantallaAnt) {
					//Si había otra pantalla anteriormente, entra a este if
					LCD_Menu ();			//Escribe la pantalla Pantalla_Menu
					PantallaAnt=Pantalla;	//Actualizo PantallaAnt
					PosCursor=MuevoCursor(Pantalla, RENUEVO_POS); //Posiciono el cursor convenientemente
					break;
				}
				else if (TeclaPulsada==T_DESPLAZAR) {
					PosCursor=MuevoCursor(Pantalla_Menu, PosCursor); //Muevo el cursor al siguiente lugar permitido.
					break;
				}
				else if (PosCursor==FLECHA_TIERRA && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_Tierra; //Cambio la pantalla a Pantalla_Tierra
					break;
				}
				else if (PosCursor==FLECHA_AMBIENTE && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_Ambiente; //Cambio la pantalla a Pantalla_Ambiente
					break;
				}
				else if (PosCursor==FLECHA_SETTINGS && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_Settings; //Cambio la pantalla a Pantalla_Settings
					break;
				}
				break;
			////////////////////////////////////////////////////////
			case Pantalla_Tierra:
				if (Pantalla != PantallaAnt) {
					LCD_Tierra ();
					PantallaAnt=Pantalla;
					break;
				}
				else if ((TeclaPulsada == T_OK) || (TeclaPulsada == T_LOBBY)){
					Pantalla=Pantalla_Menu;
					break;
				}
				break;
			////////////////////////////////////////////////////////
			case Pantalla_Ambiente:
				if (Pantalla != PantallaAnt) {
					LCD_Ambiente ();
					PantallaAnt=Pantalla;
					break;
				}
				else if ((TeclaPulsada == T_OK) || (TeclaPulsada == T_LOBBY)){
					Pantalla=Pantalla_Menu;
					break;
				}
				break;
			////////////////////////////////////////////////////////
			case Pantalla_Settings:
				if (Pantalla != PantallaAnt) {
					LCD_Settings ();
					PantallaAnt=Pantalla;
					PosCursor=MuevoCursor(Pantalla, RENUEVO_POS);
					break;
				}
				else if (TeclaPulsada==T_DESPLAZAR) {
					PosCursor=MuevoCursor(Pantalla, PosCursor);
					break;
				}
				else if ((PosCursor==FLECHA_ATRAS && TeclaPulsada == T_OK) || (TeclaPulsada == T_LOBBY)) {
					Pantalla=Pantalla_Menu;
					break;
				}
				else if (PosCursor==FLECHA_RIEGO && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_RiegoC;
					break;
				}
				else if (PosCursor==FLECHA_HORAFECHA && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_HoraFechaC;
					break;
				}
				break;
			////////////////////////////////////////////////////////
			case Pantalla_RiegoC:
				if (Pantalla!=PantallaAnt){
					LCD_RiegoC ();
					PantallaAnt=Pantalla;
					PosCursor=MuevoCursor(Pantalla, RENUEVO_POS);
					break;
				}
				else if (TeclaPulsada==T_DESPLAZAR) {
					PosCursor=MuevoCursor (Pantalla, PosCursor);
					break;
				}
				else if (TeclaPulsada==T_LOBBY) {
					Pantalla=Pantalla_Menu;
					break;
				}
				else if (PosCursor==FLECHA_ATRAS && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_Settings;
					break;
				}
				else if (PosCursor==FLECHA_RIEGOAUT && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_HorasAutC;
					break;
				}
				break;
			////////////////////////////////////////////////////////
			case Pantalla_HorasAutC:
				if (Pantalla!=PantallaAnt){
					LCD_HorasAutC ();
					PantallaAnt=Pantalla;
					PosCursor=MuevoCursor(Pantalla, RENUEVO_POS);
					break;
				}
				else if (TeclaPulsada==T_DESPLAZAR) {
					PosCursor=MuevoCursor (Pantalla, PosCursor);
					break;
				}
				else if (TeclaPulsada==T_LOBBY) {
					Pantalla=Pantalla_Menu;
					break;
				}
				else if (PosCursor==FLECHA_ATRAS && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_RiegoC;
					break;
				}
				else if (PosCursor!=FLECHA_ATRAS && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_HoraRiegoC;
					break;
				}
				break;
			////////////////////////////////////////////////////////
			case Pantalla_HoraRiegoC:
				if (Pantalla!=PantallaAnt){
					LCD_HoraRiegoC ();
					PantallaAnt=Pantalla;
					PosCursor=MuevoCursor(Pantalla, RENUEVO_POS);
					break;
				}
				else if (TeclaPulsada==T_DESPLAZAR) {
					PosCursor=MuevoCursor (Pantalla, PosCursor);
					break;
				}
				else if (TeclaPulsada==T_LOBBY) {
					Pantalla=Pantalla_Menu;
					break;
				}
				else if (PosCursor==FLECHA_ATRAS && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_HorasAutC;
					break;
				}
				//if (PantallaAnt==Pantalla_HorasVectC) dependiendo el PosCursor que tenga Configuraré c/ alarma
				break;
			/////////////////////////////////////////////////////////
			case Pantalla_HoraFechaC:
				if (Pantalla!=PantallaAnt){
					LCD_HoraFechaC ();
					PantallaAnt=Pantalla;
					PosCursor=MuevoCursor(Pantalla, RENUEVO_POS);
					break;
				}
				else if (TeclaPulsada==T_DESPLAZAR) {
					PosCursor=MuevoCursor (Pantalla, PosCursor);
					break;
				}
				else if (TeclaPulsada==T_LOBBY) {
					Pantalla=Pantalla_Menu;
					break;
				}
				else if (PosCursor==FLECHA_ATRAS && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_Settings;
					break;
				}
				break;
			////////////////////////////////////////////////////////

			default: break;
		}
	}
}









