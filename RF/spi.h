/*
 * spi.h
 *
 *  Created on: 12 de oct. de 2017
 *      Author: fedec
 */

#ifndef SPI_H_
#define SPI_H_


#include "RegsLPC1769.h"
//!< /////////////		SPI		///////////////////////////
//!< Tipo de dato específico para manejar el SPI
typedef struct {
	union {
		__RW uint32_t _S0SPCR;
		struct {
			__RW uint32_t _RESERVED1 :2;
			__RW uint32_t _BITENABLE :1;
			__RW uint32_t _CPHA :1;
			__RW uint32_t _CPOL :1;
			__RW uint32_t _MSTR :1;
			__RW uint32_t _LSBF :1;
			__RW uint32_t _SPIE :1;
			__RW uint32_t _BITS :4;
			__RW uint32_t _RESERVED2 :20;
		} spibits;
	};
	__RW uint32_t _S0SPSR;
	__RW uint32_t _S0SPDR;
	__R uint32_t _S0SPCCR;
} spi_t;

//!< 0x40020000: Primeros 4 registros del módulo SPI
#define 	DIR_SPI		( (spi_t *) 0x40020000 )

	#define		S0SPCR		DIR_SPI->_S0SPCR
		#define		BITENABLE	DIR_SPI->spibits._BITENABLE
		#define		CPHA		DIR_SPI->spibits._CPHA
		#define		CPOL		DIR_SPI->spibits._CPOL
		#define		MSTR		DIR_SPI->spibits._MSTR
		#define		LSBF		DIR_SPI->spibits._LSBF
		#define		SPIE		DIR_SPI->spibits._SPIE
		#define		BITS		DIR_SPI->spibits._BITS
	#define		S0SPSR		DIR_SPI->_S0SPSR
	#define		S0SPDR		DIR_SPI->_S0SPDR
	#define		S0SPSR		DIR_SPI->_S0SPCCR


//REGISTRO NO CONTIGUO
#define S0SPINT (*((__RW uint32_t *)0x4002001C))

//Bits de SPI Status Register (S0SPSR)
#define ABRT 3
#define MODF 4
#define ROVR 5
#define WCOL 6
#define S0SPSR_SPIF 7

#define S0SPINT_SPIF 7 //Único bit de S0SPINT





#endif /* SPI_H_ */
