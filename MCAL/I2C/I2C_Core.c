/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file I2C_Core.c 
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "I2C_Core.h"

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
void I2C_MasterInit(void){
	I2C_SET_BIT_RATE_400KHZ();
	I2C_ENABLE_ACKNOWLEDGE_BIT();
	I2C_ADDRESS = 0X01;
	I2C_ENABLE();
}
void I2C_SlaveInit(void){
	I2C_ADDRESS = 0X01;
	I2C_ENABLE();
}
void I2C_StartCondition(void){
	
	I2C_START_CONDITION_ROUTINE();
	I2C_WAIT_FOR_OPERATION_FINISH();
	I2C_WAIT_FOR_START_OPERATION_STATUS();
	
}
void I2C_RepeatedStart(void){
	I2C_START_CONDITION_ROUTINE();
	I2C_WAIT_FOR_OPERATION_FINISH();
	I2C_WAIT_FOR_REPEATED_START_OPERATION_STATUS();
}
void I2C_SendAddress_WriteOperation(uint8 addr){
	TWDR = (addr << 1);
	I2C_START_OPERATION();
	I2C_WAIT_FOR_OPERATION_FINISH();
	I2C_WAIT_FOR_ADDRESS_WRITE_OPERATION_STATUS();
}
void I2C_SendAddress_ReadOperation(uint8 addr){
	TWDR = (addr << 1) | 0X01;
	I2C_START_OPERATION();
	I2C_WAIT_FOR_OPERATION_FINISH();
	I2C_WAIT_FOR_ADDRESS_READ_OPERATION_STATUS();
}
void I2C_WriteByte(uint8 data){
	TWDR = data;
	I2C_START_OPERATION();
	I2C_WAIT_FOR_OPERATION_FINISH();
	I2C_WAIT_FOR_DATA_WRITE_OPERATION_STATUS();
}
uint8 I2C_ReadByte_NACK(void){
	uint8 Data =0;
	I2C_START_OPERATION();
	I2C_WAIT_FOR_OPERATION_FINISH();
	I2C_WAIT_FOR_DATA_READ_OPERATION_STATUS_NACK();
	Data = TWDR;
	return Data;
}
uint8 I2C_ReadByte_ACK(void){
	uint8 Data =0;
	I2C_READ_ACK_OPERATION();
	I2C_WAIT_FOR_OPERATION_FINISH();
	I2C_WAIT_FOR_DATA_READ_OPERATION_STATUS_ACK();
	Data = TWDR;
	return Data;
}
void I2C_StopCondition(void){
	I2C_STOP_CONDITION_ROUTINE();
}
/**********************************************************************************************************************
 *  END OF FILE: I2C_Core.c 
 *********************************************************************************************************************/
