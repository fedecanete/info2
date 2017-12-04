/*
 * FW_nRF.c
 *
 *  Created on: 18 de nov. de 2017
 *      Author: fedec
 */
#include "Aplicacion.h"
volatile uint8_t delay_nRF=0;

/**
 * @brief Configura el módulo nRF24l01 como receptor o transmisor
 * @param mode: Modo de operación. pipe: 0 a 5. en_aack: Habilitar auto retransmisión
 * para el pipe seleccionado. payload: 1-32, cuántos bytes se enviarán en cada transmisión
 *
 */
void nRF_TxRx_Init (uint8_t mode, uint8_t pipe, uint8_t en_aack, uint8_t payload)
{
	if (pipe>5) pipe=5;
	if (payload>32) payload=32;

	delay_nRF = DELAY_50ms; // Allow radio to reach power down if shut down
	while (delay_nRF);

	uint8_t aux[5]; //An axuliary array to send data to RWnRF function

	//1. EN_AA - (enable auto-acknowledgments) - Transmitter gets automatic response from receiver when successfull transmission! (lovely function!)
	//Only works if Transmitter has identical RF_Adress on its channel ex: RX_ADDR_P0=TX_ADDR
	if (en_aack){

		aux[0]=0;
		aux[0]|=(1<<pipe);
		//aux[0]|=(1<<ENAA_P0); //Enable auto ack on data pipe 0 (bit 0 en '1')
		RWnRF (W_REGISTER, EN_AA, aux, 1);
		aux[0]=0;
		aux[0]|=(ARD_WAIT_750US << 4); //Up to 750us delay between every retry (at least 500us at 250kbps and if payload  >5bytes in Mbps,
									   //and if payload >15byte in 2Mbps)
		aux[0]|=MAX_RETRY_15; //Up to 15 Auto Re-transmit tries
		/*** VER NOTA ***/
		RWnRF (W_REGISTER, SETUP_RETR, aux, 1);

	}

	//2. Choose number of enabled data pipes (up to 5)
	aux[0]=0;
	aux[0]|=(1<<pipe);
	//aux[0]|=(1<<ERX_P0); //Enable data pipe 0
	RWnRF (W_REGISTER, EN_RXADDR, aux, 1);

	//3. RF_Address width setup (how many bytes is the receiver address, the more the merrier 1-5)
	aux[0]=AW_5BYTES; //0b0000 0011 = 5 bytes RF_Address
	RWnRF (W_REGISTER, SETUP_AW, aux, 1);

	//4. RF Channel Setup - Choose frequency: 2,4 - 2,527 GHz  1MHz/step
	aux[0]=1; //0b0000 0001 = 2,401GHz (same on Tx and Rx)
	RWnRF (W_REGISTER, RF_CH, aux, 1);

	//5. RF Setup - Choose power mode and data speed.
	aux[0]=0;
	//Dejamos PLL_LOCK (bit 4)en 0 (default)
	//Data rate
	aux[0]|=(1<<RF_DR); //Data rate (bit 3):	'0'= 1Mbps (longer range)
						//						'1'= 2Mbps
	//Power in TX mode
	aux[0]|=(3<<1); /*bits (2:1)="00": -18dBm
								"01" : -12dBm
								"10" : -6dBm
								"11" : 0dBm
	*/
	aux[0]|=(1<<LNA_HCURR); //Setup LNA (Low Noise Amplifier) gain in default value
	RWnRF (W_REGISTER, RF_SETUP, aux, 1);


	//6. Rx RF_Address setup 5 bytes - Set Receiver Address (set RX_ADDR_P0 = TX_ADDR if EN_AA is enabled!)
	uint8_t i;
	for (i=0; i<5;i++)
		aux[i]=0x12; //Una dirección arbitraria: 0x1212121212
	RWnRF (W_REGISTER, RX_ADDR_P0, aux, 5); //Since we chose pipe 0 on EN_EXADDR we give this address to that channel.
	//Here you can give differents addresses to different channels (if they're enabled in EN_RXADDR) to listen on several different transmitters)

	//7. Tx RF_Address Setup 5 bytes - Set Transmitter address (not used in a receiver but can be set anyway)
	for (i=0; i<5; i++)
		aux[i]=0x12; //Same on the Receiver chip and the RX-RF_Address above if EN_AA is enabled!!
	RWnRF (W_REGISTER, TX_ADDR, aux, 5);

	//8. Payload Width Setup (How many bytes to send per transmission) - 1 to 32 bytes
	aux[0]=payload; //"payload" bytes per package (same on receiver and transmitter)
	RWnRF (W_REGISTER, RX_PW_P0, aux, 1);

	//9. CONFIG Register Setup - Encender el módulo y decirle si es Transmisor o Receptor
	aux[0]=0;
	aux[0]|=(1<<MASK_MAX_RT); //(bit 4='1')IRQ interrupt is not triggered if transmission failed
	aux[0]|=(1<<EN_CRC);//Enable CRC
	aux[0]|=(1<<CRCO); //CRC encoding scheme: 2bytes
	aux[0]|=(1<<PWR_UP); //Encender el módulo
	aux[0]|=((!mode) ? 0 : 1<<PRIM_RX); //bit 0: '0'=Transmitter, '1'=Receiver
	RWnRF (W_REGISTER, CONFIG, aux, 1);

	delay_nRF = DELAY_5ms;
	while (delay_nRF);
	//Device needs 1.5ms to reach standby mode (CE=low)
}

/* ***********NOTA**************
 * The the delay has to be greater than 500us if you are in the 250kbps mode,
 * or if the payload is greater than 5bytes when in 1Mbps-mode or a payload
 * greater then 15bytes when in 2Mbps mode. Note that the default value of
 * this is only 250us, and will therefore cause trouble when in 250kbps mode
 * and with bigger payloads!
 *
 */



/*** PARA SETEAR AS RX *****/
/*first delay 50ms, to make sure the nRF is in sleep mode, then send 0x1F (1 en PRIM_RX)
 *to the CONFIG register, than make it wait 50ms again before the first
 *receive-command.*/

void Transmit_Payload (uint8_t *data_buffer, uint8_t width)
{
	RWnRF (FLUSH_TX,0,0,0); //Flushes the TX FIFO from old data
	RWnRF (W_TX_PAYLOAD, 0, data_buffer, width);

	delay_nRF = DELAY_10ms; //Needs a 10ms delay to work after loading the nrf with the payload
	while (delay_nRF);

	SetPIN (pin_CE, 1); //CE='1' to transmit the data
	int i;
	for (i=1500;i>0;i--);//Al least 10us IMPLEMENTAR CON TIMER
	SetPIN (pin_CE, 0);

	delay_nRF = DELAY_10ms;
	while (delay_nRF);

}
//NOTA SOBRE TX MODE
/* Tx mode (ver digrama de estados del manual) se dá cuando hay datos en el Tx FIFO y CE=1
 * PERO:
 * " It is important to never keep the nRF24L01 in TX mode for more than 4ms at a time. If the auto
retransmit is enabled, the nRF24L01 is never in TX mode long enough to disobey this rule."
 * Así que una forma de evitarlo sería no mantener CE en alto por más de 4ms
 * (Que generalmente son 20us)
 *
 */

