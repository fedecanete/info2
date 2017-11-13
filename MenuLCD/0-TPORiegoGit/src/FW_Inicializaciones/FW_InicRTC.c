
#include "Aplicacion.h"

/**
 * \fn 		void Inic_RTC(void)
 * \brief 	Inicializacion del RTC
 * \details
 * \author 	GOS
 * \date   	2014.05.06
 * \param 	[in] void
 * \return 	void
 * */
void Inic_RTC(void)
{
	RTCILR = 0x00;				// Limpio Flags
	RTCCIIR = 0x00;				// Deshabilito interrupciones
	RTCAMR = 0xFF;				// Enmascaro comparador de alarmas
	RTCCALIBRATION = 0x00;		// Inicializa registro de calibración
	RTCCCR = 0x01;				// Arranca contador

	RTC_HabilitarIntContador (RTC_INTERRUPCION_MIN);
}
