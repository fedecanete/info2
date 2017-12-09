/*
 * FW_nRF.c
 *
 *  Created on: 18 de nov. de 2017
 *      Author: fedec
 */
#include "Aplicacion.h"
//SSP1
extern volatile uint8_t Buff_Tx_SSP1[TOPE_SSP1];		//!< Buffer de Transmisión SPI
extern volatile uint8_t Buff_Rx_SSP1[TOPE_SSP1];		//!< Buffer de Recepción SPI
extern volatile uint8_t flags_int_ssp1[4];				//Flags de interrupciones
extern volatile uint8_t SSP1_RxIn_Idx;				//Índices para el manejo de los buffers
extern volatile uint8_t SSP1_RxOut_Idx;
extern volatile uint8_t SSP1_TxIn_Idx;
extern volatile uint8_t SSP1_TxOut_Idx;

extern volatile uint8_t humedad_t;
extern volatile uint8_t temperatura;
extern volatile uint8_t humedad_amb;
extern volatile uint8_t motor;


volatile uint8_t delay_nRF=0;
volatile uint8_t listen_delay=0; //ESTA VARIABLE DEBE INCREMENTARSE CON EL SYSTICK
volatile uint8_t enable_listen=0; //La activa el main y se deshabilita al recibir/time_out
volatile uint8_t data_avialable=1;//Flag para avisar que se escribio el SPIRxBuff
volatile uint8_t Buff_RF[DEFAULT_PAYLOAD_WIDTH];	//!< Buffer de Recepción para el transceptor RF (1 payload)

/**
 * @brief Configura el módulo nRF24l01 como receptor o transmisor, inicializando sus pines.
 * @param mode: Modo de operación. pipe: 0 a 5. en_aack: Habilitar auto retransmisión
 * para el pipe seleccionado. payload: 1-32, cuántos bytes se enviarán en cada transmisión
 *
 */
void nRF_TxRx_Init (uint8_t mode, uint8_t pipe, uint8_t en_aack, uint8_t payload,
								uint8_t channel)
{
	if (pipe>5) pipe=5;
	if (payload>32) payload=32;
	if (channel>127)channel=127;

	Init_HW_nRF();

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
	aux[0]=channel; //0b0000 0001 = 2,401GHz (same on Tx and Rx)
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
	aux[0]|=(((!mode) ? 0 : 1)<<PRIM_RX); //bit 0: '0'=Transmitter, '1'=Receiver
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


/**
 * @brief Configura como receptor o transmisor si ya está inicializado
 * @param mode: Modo de operación receptor (1) o transmisor (0).
 * Toma el valor actual del CONFIG y actualiza el bit 0 (PRIM_RX)
 */
void Set_Device_Mode (uint8_t mode){

	uint8_t config;
	config = nRF_GetReg (CONFIG);
	config &= ~(1<<PRIM_RX);
	config |= (mode<<PRIM_RX);
	RWnRF (W_REGISTER,CONFIG,&config,1);
}



void Transmit_Payload (uint8_t *data_buffer, uint8_t width)
{
	RWnRF (FLUSH_TX,0,0,0); //Flushes the TX FIFO from old data
	RWnRF (W_TX_PAYLOAD, 0, data_buffer, width);

	delay_nRF = DELAY_10ms; //Needs a 10ms delay to work after loading the nrf with the payload
	while (delay_nRF);

	SetPIN (pin_CE, 1); //CE='1' to transmit the data
	uint8_t i;
	for (i=200;i>0;i--);//Al least 10us (así es más o menos 20us)
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

void Listen (void)
{
	//listen_delay debe INCREMENTARSE con el Systick
	uint8_t i, aux_reg, aux_buff[5];
	if (!listen_delay) {
		SetPIN(pin_CE, 1); //Si es la primera vez, le da el pulso para que escuche
		enable_listen=1;
	}
	if (listen_delay==LISTEN_MAX_TIME){
		SetPIN(pin_CE, 0);
		listen_delay=0;
		enable_listen=0;

	}
	//Me fijo si ha datos
	if (Rx_Data_Ready()){
		//Dejo de escuchar
		SetPIN(pin_CE, 0);
		//Retiro Payload y lo guardo en el buffer global
		RWnRF (R_RX_PAYLOAD, 0, Buff_RF, DEFAULT_PAYLOAD_WIDTH);
 //Payload: #SENSOR - HUM_T - TEMP - HUM_AMB - MOTOR
		//Podríamos hacer que las variales globales sean vectores y sus
		//subíndices representen cada sensor

	/****
	 * ESTOY ASUMIENDO QUE LOS DATOS LLEGAN SIN ERRORES
	 *
	 */
		humedad_t=Buff_RF[1];
		temperatura=Buff_RF[2];
		humedad_amb=Buff_RF[3];
		motor=Buff_RF[4];

		listen_delay=0; //Reinicio la cuenta para la demora
		enable_listen=0; //Deshabilito a que cuente
		data_avialable=1; //Aviso que llegaron datos

	}else data_avialable=0;


}
uint8_t Monitor_Air(void){

	uint8_t signal;
	signal = nRF_GetReg(CD);
	return signal; //0: No hay señales en el mismo canal. 1: Hay señales.
}
uint8_t Rx_Data_Ready (void){

	uint8_t status, fifo_status;
	status = nRF_GetReg(STATUS);
	if (status & (1<<RX_DR)){ //Se produjo interrupción por RX FIFO Data Ready

		status|=(1<<RX_DR);//Escribo '1' para borrar el flag
		RWnRF (W_REGISTER,STATUS,&status,1);
		return 1;

	}
	fifo_status = nRF_GetReg(FIFO_STATUS);
	if (!(fifo_status & (1<<RX_EMPTY))){
		//Not empty -> Data in RX FIFO
		return 1;

	}else return 0;

}

