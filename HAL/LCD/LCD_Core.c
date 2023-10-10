 /**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  LCD_Core.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "LCD_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

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
* \Syntax          : void LCD_Init(void))        
* \Description     : Describe this service                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void LCD_Init(void){
	#if (LCD_MODE==LCD_4BIT_MODE)
	LCD_WriteCommand(0x33);
	LCD_WriteCommand(0x32);
	LCD_WriteCommand(0x28);
	
	LCD_WriteCommand(0x0C);
	LCD_WriteCommand(0x01);
	LCD_WriteCommand(0x06);	
	LCD_WriteCommand(0x02);	
	#endif
}
/******************************************************************************
* \Syntax          : void LCD_WriteCommand(uint8 cmd)        
* \Description     : write command on the LCD                                 
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : parameterName   Parameter Describtion                     
* \Parameters (out): None                                                      
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK                                  
*******************************************************************************/
void LCD_WriteCommand(uint8 cmd){
	uint8 Old_value=0 ,New_Value=0;
	
	DIO_WriteChannel(LCD_RS_PIN,PIN_LOW);
	DIO_WriteChannel(LCD_E_PIN,PIN_LOW);
	#if (LCD_MODE == LCD_4BIT_MODE)
	
	/*DIO_ReadOutputPort(LCD_DATA_PORT,&Old_value);
	New_Value=((cmd>>1)&DATA_MASK)|(Old_value&DATA_PORT_MASK);
	DIO_WritePort(LCD_DATA_PORT,New_Value); */
	
	
	DIO_WriteChannel(LCD_D4_PIN,GET_BIT(cmd,4));
	DIO_WriteChannel(LCD_D5_PIN,GET_BIT(cmd,5));
	DIO_WriteChannel(LCD_D6_PIN,GET_BIT(cmd,6));
	DIO_WriteChannel(LCD_D7_PIN,GET_BIT(cmd,7)); 
	
	
	DIO_WriteChannel(LCD_E_PIN,PIN_HIGH);
	_delay_ms(1);
	DIO_WriteChannel(LCD_E_PIN,PIN_LOW);
	
	
	/*DIO_ReadOutputPort(LCD_DATA_PORT,&Old_value);
	New_Value=((cmd<<3)&DATA_MASK)|(Old_value&DATA_PORT_MASK);
	DIO_WritePort(LCD_DATA_PORT,New_Value); */
	
	DIO_WriteChannel(LCD_D4_PIN,GET_BIT(cmd,0));
	DIO_WriteChannel(LCD_D5_PIN,GET_BIT(cmd,1));
	DIO_WriteChannel(LCD_D6_PIN,GET_BIT(cmd,2));
	DIO_WriteChannel(LCD_D7_PIN,GET_BIT(cmd,3)); 
	
	DIO_WriteChannel(LCD_E_PIN,PIN_HIGH);
	_delay_ms(1);
	DIO_WriteChannel(LCD_E_PIN,PIN_LOW);
	
	_delay_ms(5);
	
	#endif
	
}
/******************************************************************************
* \Syntax          : void LCD_WriteChar(uint8 chr)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void LCD_WriteChar(uint8 chr){
	uint8 Old_value=0 ,New_Value=0;
	
	DIO_WriteChannel(LCD_RS_PIN,PIN_HIGH);
	DIO_WriteChannel(LCD_E_PIN,PIN_LOW);
	#if (LCD_MODE == LCD_4BIT_MODE)
	
	DIO_ReadOutputPort(LCD_DATA_PORT,&Old_value);
	New_Value=((chr>>1)&DATA_MASK)|(Old_value&DATA_PORT_MASK);
	DIO_WritePort(LCD_DATA_PORT,New_Value);
	
	/*
	DIO_WriteChannel(LCD_D4_PIN,GET_BIT(chr,4));
	DIO_WriteChannel(LCD_D5_PIN,GET_BIT(chr,5));
	DIO_WriteChannel(LCD_D6_PIN,GET_BIT(chr,6));
	DIO_WriteChannel(LCD_D7_PIN,GET_BIT(chr,7)); */
	
	
	DIO_WriteChannel(LCD_E_PIN,PIN_HIGH);
	_delay_ms(1);
	DIO_WriteChannel(LCD_E_PIN,PIN_LOW);
	
	
	DIO_ReadOutputPort(LCD_DATA_PORT,&Old_value);
	New_Value=((chr<<3)&DATA_MASK)|(Old_value&DATA_PORT_MASK);
	DIO_WritePort(LCD_DATA_PORT,New_Value);
	/*DIO_WriteChannel(LCD_D4_PIN,GET_BIT(chr,0));
	DIO_WriteChannel(LCD_D5_PIN,GET_BIT(chr,1));
	DIO_WriteChannel(LCD_D6_PIN,GET_BIT(chr,2));
	DIO_WriteChannel(LCD_D7_PIN,GET_BIT(chr,3)); */
	
	DIO_WriteChannel(LCD_E_PIN,PIN_HIGH);
	_delay_ms(1);
	DIO_WriteChannel(LCD_E_PIN,PIN_LOW);
	
	_delay_ms(5);
	
	#endif
	
}
/******************************************************************************
* \Syntax          : void LCD_WriteString(uint8 *chr)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void LCD_WriteString(char *chr){
	uint8 Cnt=0;
	while(chr[Cnt]!='\0'){
		LCD_WriteChar(chr[Cnt]);
		Cnt++;
	}
}
/******************************************************************************
* \Syntax          : void LCD_WriteInteger(uint32 num)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void LCD_WriteInteger(sint32 num){
	/* my method *
	uint32 temp=0;
	uint32 digits=1;
	if(num<0){
		num*=-1;
		LCD_WriteChar('-');
	}
	temp=num;
	while(1){
		temp/=10;
		if(temp==0)break;
		digits*=10;
	}	
	while(digits!=0)
	{
		LCD_WriteChar((num/digits)|(0x30));
		num-=(num/digits)*digits;
		digits/=10;
	}
	************************************************/
	uint32 temp=1;
	if(num==0){
		LCD_WriteChar('0');
	}
	else if(num<0){
		LCD_WriteChar('-');
		num*=-1;
	}
	while(num){
		temp=(temp*10)+(num%10);
		num/=10;
	}
	while(temp!=1){
		LCD_WriteChar((temp%10)+48);
		temp/=10;
	}
}
/******************************************************************************
* \Syntax          : void LCD_Clear(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void LCD_Clear(void){
	LCD_WriteCommand(0x01);
}
/******************************************************************************
* \Syntax          : void LCD_GoTo(uint8 Row,uint8 Col)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void LCD_GoTo(uint8 Row,uint8 Col){
	uint8 arr[2]={0x80,0xC0};
	LCD_WriteCommand(arr[Row]+Col);
}
/******************************************************************************
* \Syntax          : void LCD_Custom_Char_Init(void)
* \Description     : Describe this service
*
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : parameterName   Parameter Describtion
* \Parameters (out): None
* \Return value:   : Std_ReturnType  E_OK
*                                    E_NOT_OK
*******************************************************************************/
void LCD_Custom_Char_Init(void){
	uint8 custom_char_cnt=0, Bytes_cnt=0;
	for (custom_char_cnt=0;custom_char_cnt<CUSTOM_CHAR_NUM;custom_char_cnt++)
	{
		LCD_WriteCommand(0x40+(8*custom_char_cnt));
		for (Bytes_cnt=0;Bytes_cnt<BYTES;Bytes_cnt++)
		{
			LCD_WriteChar(Custom_Chr[custom_char_cnt][Bytes_cnt]);
		}
	}
}
/**********************************************************************************************************************
 *  END OF FILE: LCD_Core.c
 *********************************************************************************************************************/
