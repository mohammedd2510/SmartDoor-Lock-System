/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  DIO_Core.c
 *        \brief  has the functions implementation of DIO Module
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "DIO_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
volatile static uint8* Output_Registers[]={&GPIOA_OUTPUT_REGISTER,&GPIOB_OUTPUT_REGISTER,&GPIOC_OUTPUT_REGISTER,&GPIOD_OUTPUT_REGISTER};
volatile static uint8* Input_Registers[]={&GPIOA_INPUT_REGISTER,&GPIOB_INPUT_REGISTER,&GPIOC_INPUT_REGISTER,&GPIOD_INPUT_REGISTER};
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

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
* \Syntax          : void DIO_WriteChannel(uint8 Pin_Num,PIN_VALUE_t Pin_value)      
* \Description     : write logic on a specific pin                                     
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : void                                 
*******************************************************************************/
void DIO_WriteChannel(uint8 Pin_Num,PIN_VALUE_t Pin_value){
	uint8 Port=0 ,Pin=0;
	Port=Pin_Num/(NUMBER_OF_EACH_PORT_PINS);
	Pin=Pin_Num % (NUMBER_OF_EACH_PORT_PINS);
	switch(Pin_value){
		case PIN_HIGH :
			SET_BIT(*Output_Registers[Port],Pin);
			break;
		case PIN_LOW :
			CLR_BIT(*Output_Registers[Port],Pin);
			break;
		default:
			break;
	}	
}
/******************************************************************************
* \Syntax          : void DIO_ReadChannel(uint8 Pin_Num,PIN_VALUE_t *Pin_value)
* \Description     : Read logic from a specific pin
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void DIO_ReadChannel(uint8 Pin_Num,PIN_VALUE_t *Pin_value){
	uint8 Port=0 ,Pin=0;
	Port=Pin_Num/(NUMBER_OF_EACH_PORT_PINS);
	Pin=Pin_Num % (NUMBER_OF_EACH_PORT_PINS);
	*Pin_value=GET_BIT(*Input_Registers[Port],Pin);
	
}
/******************************************************************************
* \Syntax          : void DIO_FlipChannel(uint8 Pin_Num)
* \Description     : Toggle logic of a specific pin
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void DIO_FlipChannel(uint8 Pin_Num){
		uint8 Port=0 ,Pin=0;
		Port=Pin_Num/(NUMBER_OF_EACH_PORT_PINS);
		Pin=Pin_Num % (NUMBER_OF_EACH_PORT_PINS);
		Toggle_BIT(*Output_Registers[Port],Pin);
}
/******************************************************************************
* \Syntax          : void DIO_WritePort(uint8 Pin_Num,uint8 Port_value)
* \Description     : write logic on a specific port
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void DIO_WritePort(uint8 Pin_Num,uint8 Port_value){
	uint8 Port=0;
	Port=Pin_Num/(NUMBER_OF_EACH_PORT_PINS);
	*Output_Registers[Port]=Port_value;
}
/******************************************************************************
* \Syntax          : void DIO_ReadPort(uint8 Pin_Num,uint8* Port_value)
* \Description     : Read logic from a specific port
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void DIO_ReadPort(uint8 Pin_Num,uint8* Port_value){
	uint8 Port=0;
	Port=Pin_Num/(NUMBER_OF_EACH_PORT_PINS);
	*Port_value=*Input_Registers[Port];
}
/******************************************************************************
* \Syntax          :void DIO_ReadOutputPort(uint8 Pin_Num,uint8* Port_value)
* \Description     : Read logic from a output register
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : void
*******************************************************************************/
void DIO_ReadOutputPort(uint8 Pin_Num,uint8* Port_value){
	uint8 Port=0;
	Port=Pin_Num/(NUMBER_OF_EACH_PORT_PINS);
	*Port_value=*Output_Registers[Port];
}



/**********************************************************************************************************************
 *  END OF FILE: DIO_Core.c
 *********************************************************************************************************************/
