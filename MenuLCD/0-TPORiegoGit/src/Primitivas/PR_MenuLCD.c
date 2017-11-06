/*
 * PR_LCD.c
 *
 *  Created on: 16 de oct. de 2017
 *      Author: Lucas
 */

#include "Aplicacion.h"

void Menu_LCD (uint8_t TeclaPulsada, uint8_t Temperatura, uint8_t Humedad_A, uint8_t Humedad_T) {

	static uint8_t Pantalla=Pantalla_Menu;
	static uint8_t PantallaAnt=Pantalla_Menu;
	static uint8_t PosCursor=FLECHA_TIERRA;
	static uint8_t HumedadAAnt=0;
	static uint8_t TemperaturaAnt=0;
	static uint8_t HumedadTAnt=0;

	//if (PantallaAnt==Pantalla_Menu) -->Actualizacion de Hora/Fecha, RTC, o lo que sea
	if (PantallaAnt==Pantalla_Tierra && HumedadTAnt!=Humedad_T) {
		ActualizarTierra (Humedad_T);
		HumedadTAnt=Humedad_T;
	}

	if (PantallaAnt==Pantalla_Ambiente && (TemperaturaAnt!=Temperatura || HumedadAAnt!=Humedad_A)) {
		ActualizarAmbiente (Temperatura, Humedad_A);
		TemperaturaAnt=Temperatura;
		HumedadAAnt=Humedad_A;
	}

	if ((TeclaPulsada != NO_KEY) || (Pantalla != PantallaAnt)) {

		switch (Pantalla) {

			case Pantalla_Menu:
				if (Pantalla != PantallaAnt) {
					LCD_Menu ();
					PantallaAnt=Pantalla;
					PosCursor=MuevoCursor(Pantalla, RENUEVO_POS);
					break;
				}
				else if (TeclaPulsada==T_DESPLAZAR) {
					PosCursor=MuevoCursor(Pantalla_Menu, PosCursor);
					break;
				}
				else if (PosCursor==FLECHA_TIERRA && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_Tierra;
					break;
				}
				else if (PosCursor==FLECHA_AMBIENTE && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_Ambiente;
					break;
				}
				else if (PosCursor==FLECHA_SETTINGS && TeclaPulsada==T_OK) {
					Pantalla=Pantalla_Settings;
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









