/********************************************************************
 * Module : UART
 *
 * File Name : uart.c
 *
 * Description : Source file for UART module
 *
 * Author: Ahmed Yasser
 *******************************************************************/
#include "std_types.h"
#include <avr/io.h>
#include "common_macros.h"
#include "uart.h"
/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(uint32 baud_rate, const UART_Config *config_ptr)
{
	uint16 ubrr_value = 0;
	/*Write this bit one to double the transfer rate for asynchronous communication */
	UCSRA = (1<<U2X);


	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * UCSZ2 = 0 For 8-bit data mode
	 * RXB8 & TXB8 not used for 8-bit data mode
	 ***********************************************************************/
	UCSRB = (1<<RXEN) | (1<<TXEN);

	/************************** UCSRC Description **************************
	 * URSEL   = 1 The URSEL must be one when writing the UCSRC
	 * UMSEL   = 0 Asynchronous Operation
	 * UPM1:0  = 00 Disable parity bit
	 * USBS    = 0 One stop bit
	 * UCSZ1:0 = 11 For 8-bit data mode
	 * UCPOL   = 0 Used with the Synchronous operation only
	 ***********************************************************************/
	UCSRC = (1<<URSEL);
	UCSRC = ( UCSRC & 0xCF ) | ((config_ptr -> parity_mode ) <<UPM0);
	UCSRC = ( UCSRC & 0xF7 ) | ((config_ptr -> stop_bit ) <<USBS);
	UCSRC = ( UCSRC & 0xF9 ) | ((config_ptr -> size ) <<UCSZ0);


		/* Calculate the UBRR register value */
	ubrr_value = (uint16)(((F_CPU / (baud_rate * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}





/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
}





/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte()
{
	while(BIT_IS_CLEAR(UCSRA,RXC)); /* RXC flag is set when the UART receive data so wait until this flag is set to one */
	SET_BIT(UCSRA,RXC); /* Clear the TXC flag*/
	return UDR;   /*Read the received data from the Rx buffer (UDR)*/


}




/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const char *str)
{
	uint8 i = 0;
	while(str[i] !="\0")
	{
		UART_sendByte(str[i]);
		i++;
	}

}






/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *str)
{
	uint8 i = 0;

	/* Receive the first byte */
	str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(str[i] != '#')
	{
		i++;
		str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	str[i] = '\0';
}
