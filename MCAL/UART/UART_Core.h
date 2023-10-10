/*
 * UART_Core.h
 *
 * Created: 2/28/2023 7:25:54 AM
 *  Author: Ali
 */ 

/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <Write File Name>
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef UART_CORE_H_
#define UART_CORE_H_


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCU.h"
#include "std_types.h"
#include "BIT_Math.h"
#include "UART_Cfg.h"
#include "LCD_Core.h"
#ifndef F_CPU
#define F_CPU 16000000U
#endif
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/


#define ENABLE   1
#define DISABLE  0

#define PARITY_ODD  1
#define PARITY_EVEN 0

#define	UART_DATA_BYTES_5  0
#define UART_DATA_BYTES_6  1
#define	UART_DATA_BYTES_7  2
#define UART_DATA_BYTES_8  3
#define UART_DATA_BYTES_9  4


		
/**********************************************************************************************************************
 *  GLOBUART_DATA_BYTES_8AL FUNCTION MACROS
 *********************************************************************************************************************/

#define SET_UART_PARITY_ODD()  UCSRC |= 0XD0
#define SET_UART_PARITY_EVEN() UCSRC |= 0XA0

#define SET_UART_DATA_BYTES_5() UCSRC |= 0X80
#define SET_UART_DATA_BYTES_6() UCSRC |= 0X82
#define SET_UART_DATA_BYTES_7() UCSRC |= 0X84
#define SET_UART_DATA_BYTES_8() UCSRC |= 0X86


#define SET_UART_INTERRUPT_ENABLE() UCSRB_bits._RXCIE=1;UCSRB_bits._TXCIE=1
#define SET_UART_INTERRUPT_DISABLE() UCSRB_bits._RXCIE=0;UCSRB_bits._TXCIE=0

#define SET_UART_TX_INTERRUPT_ENABLE() UCSRB_bits._TXCIE=1
#define SET_UART_TX_INTERRUPT_DISABLE() UCSRB_bits._TXCIE=0

#define SET_UART_TX_ENABLE() UCSRB_bits._TXEN=1
#define SET_UART_RX_ENABLE() UCSRB_bits._RXEN=1
#define SET_UART_RX_DISABLE() UCSRB_bits._RXEN=0


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
 extern uint8 TX_STATUS_FLAG;
 extern uint8 TX_Cnt;
 extern uint8 RECEIVE_STATUS_FLAG;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

void UART_Init(void);

void UART_InitiateTx(void);

void UART_SendMessage(char*TX_MESSAGE);

void UART_ReceiveMessage(uint8*RX_MESSAGE);

void UART_SendChar(uint8 TX_MESSAGE);

void UART_ReceiveChar(uint8*RX_MESSAGE);

uint8 UART_ReceiveStatus(void);

uint8 UART_SendCharStatus(void);

#endif /* UART_CORE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: Std_Types.h
 *********************************************************************************************************************/

