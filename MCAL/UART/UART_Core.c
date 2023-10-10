/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  UART_Core.c 
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "UART_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint8 RECEIVE_STATUS_FLAG;
uint8 TX_STATUS_FLAG;
uint8 TX_Cnt=-0;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType FunctionName(AnyType parameterName)        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void UART_Init(void){
uint8 BaudRate_Value_l = 0;

#if (UART_PARITY_STATE ==  ENABLE)
#if (UART_PARITY_TYPE ==   PARITY_ODD)
SET_UART_PARITY_ODD();
#elif (UART_PARITY_TYPE ==   PARITY_EVEN)
SET_UART_PARITY_EVEN();
#endif /*if (UART_POLARITY_TYPE ==   POLARITY_ODD)*/
#endif /*if (UART_POLARITY_STATE ==  ENABLE)*/

#if (UART_DATA_BYTES   ==    UART_DATA_BYTES_5)
SET_UART_DATA_BYTES_5();
#elif (UART_DATA_BYTES   ==    UART_DATA_BYTES_6)
SET_UART_DATA_BYTES_6();
#elif (UART_DATA_BYTES   ==    UART_DATA_BYTES_7)
SET_UART_DATA_BYTES_7();
#elif (UART_DATA_BYTES   ==    UART_DATA_BYTES_8)
SET_UART_DATA_BYTES_8();
#endif /*if (UART_DATA_BYTES   ==    UART_DATA_BYTES_5)*/

#if (UART_INTERRUPT_STATE ==  ENABLE)
SET_UART_INTERRUPT_ENABLE();
#elif (UART_INTERRUPT_STATE ==  DISABLE)
SET_UART_INTERRUPT_DISABLE();
#endif

SET_UART_TX_ENABLE();
SET_UART_RX_ENABLE();

BaudRate_Value_l = ((160000U) / (UART_BAUD_RATE * 16U)) - 1;
UBRRL =  BaudRate_Value_l ;
}
void UART_InitiateTx(void){
	SET_UART_TX_INTERRUPT_ENABLE();
	TX_STATUS_FLAG=1;
	TX_Cnt=0;
}
void UART_SendData(char*TX_MESSAGE){
 if(TX_MESSAGE[TX_Cnt] == '\0'){
	 TX_Cnt=0;
	 TX_STATUS_FLAG=0;
	 SET_UART_TX_INTERRUPT_DISABLE();
 }	
 if (TX_STATUS_FLAG ==1)
 {
	 UDR=TX_MESSAGE[TX_Cnt];
	 TX_STATUS_FLAG=0;
 }
}

void UART_ReceiveData(uint8*RX_MESSAGE){
	static uint8 REC_COUNTER=0;
	RX_MESSAGE[REC_COUNTER]=UDR;
	if(RX_MESSAGE[REC_COUNTER]==UART_RECEIVE_DELIMITER){
		RECEIVE_STATUS_FLAG=1;
		REC_COUNTER=0;
	}
	else REC_COUNTER++;
}
uint8 UART_ReceiveStatus(void){
	uint8 Rec_Status_l=0;
	if (RECEIVE_STATUS_FLAG==1)
	{
		RECEIVE_STATUS_FLAG=0;
		Rec_Status_l=1;
	}
	return Rec_Status_l;
}
void UART_SendChar(uint8 TX_MESSAGE){
	if (TX_STATUS_FLAG ==1)
	{
		UDR=TX_MESSAGE;
		TX_STATUS_FLAG=0;
	}
}
uint8 UART_SendCharStatus(void){
	uint8 SendChar_Status_l=0;
	if (TX_STATUS_FLAG==1)
	{
		TX_STATUS_FLAG=0;
		SendChar_Status_l=1;
	}
	return SendChar_Status_l;
}
void UART_ReceiveChar(uint8*RX_MESSAGE){
		*RX_MESSAGE=UDR;
		RECEIVE_STATUS_FLAG=1;
}
/**********************************************************************************************************************
 *  END OF FILE: UART_Core.c 
 *********************************************************************************************************************/
