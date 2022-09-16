/********************************************************************
 * Module : UART
 *
 * File Name : uart.h
 *
 * Description : Header file for UART module
 *
 * Author: Ahmed Yasser
 *******************************************************************/

#ifndef UART_H_
#define UART_H_


/***************************************************
 * 					Deceleration                   *
 ***************************************************/
typedef enum
{
 one_bit, two_bit
}Stop_bit_select;

typedef enum
{
five_bit , six_bit , seven_bit ,eight_bit
}Character_size;

typedef enum
{
Disabled,Reserved,Even_Parity,Odd_Parity
}Parity_mode;


typedef struct{
Stop_bit_select  stop_bit;
Character_size	 size;
Parity_mode	     parity_mode;
}UART_Config;





/***************************************************
 * 				Function Prototype                 *
 ***************************************************/
void UART_init(uint32 baud_rate, const UART_Config *config_ptr);

void UART_sendByte(const uint8 data);

uint8 UART_recieveByte();

void UART_receiveString(uint8 *str);

void UART_sendString(const char *str);


#endif /* UART_H_ */
