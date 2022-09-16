/********************************************************************
 * Module : LCD
 *
 * File Name : lcd.h
 *
 * Description : Header file for LCD module
 *
 * Author: Ahmed Yasser
 *******************************************************************/

#ifndef LCD_H_
#define LCD_H_
#include "std_types.h"

/*************************************************************************
 * 								Definitions                              *
 ************************************************************************/
/*Register select pin for select data or command 0 --> command    1-->data   Input Pin */
#define RS_PORT_ID    		PORTD_ID
#define RS_PIN_ID			PIN4_ID

/*Read Write control bus for read mode -->High , write mode -->LOW  Input Pin */
#define RW_PORT_ID 			PORTD_ID
#define RW_PIN_ID			PIN5_ID

/* Data Enable Input Pin */
#define EN_PORT_ID		PORTD_ID
#define EN_PIN_ID		PIN6_ID

/*Data bus*/
#define LCD_DATA_PORT		PORTC_ID


/************************************************************************
 * 							LCD commands                                *
 ************************************************************************/
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80

/****************************************************************************
 *  					 	Function Prototype                              *
 ****************************************************************************/

void LCD_sendCommand(uint8 command);
void LCD_init(void);
void LCD_displayCharacter(uint8 data);
void LCD_displayString(const char *str);
void LCD_clearScreen(void);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *Str);
void LCD_intgerToString(int data);


#endif /* LCD_H_ */
