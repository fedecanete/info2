/**
 \file		: KitInfo2FW_RTC.h
 \brief     : Header de rutinas de RTC
*/

#ifndef RTC_H_
#define RTC_H_

#include "Aplicacion.h"

typedef struct {
	uint32_t seg;
	uint32_t min;
	uint32_t hora;
	uint32_t dia_mes;
	uint32_t dia_semana;
	uint32_t dia_anio;
	uint32_t mes;
	uint32_t anio;
} RTC_HoraFecha;

// Prototipos
void Inic_RTC(void);
void RTC_HabilitarIntContador (uint32_t);
void RTC_HabilitarRiegoAut (uint8_t, uint8_t);
void RTC_SetHoraFecha (RTC_HoraFecha*);
void RTC_GetHoraFecha (RTC_HoraFecha*);


#define RTC_INTERRUPCION_SEG		0
#define RTC_INTERRUPCION_MIN		1
#define RTC_INTERRUPCION_HORA		2
#define RTC_INTERRUPCION_DIAMES		3
#define RTC_INTERRUPCION_DIASEM		4
#define RTC_INTERRUPCION_DIAANIO	5
#define RTC_INTERRUPCION_MES		6
#define RTC_INTERRUPCION_ANIO		7

#endif /* RTC_H_ */
