/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  I2C_Core.h 
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef I2C_CORE_H_
#define I2C_CORE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "I2C_Cfg.h"
#include "MCU.h"
#include "BIT_Math.h"
#include "std_types.h"

#ifndef F_CPU
#define F_CPU 16000000U
#endif
#include <util/delay.h>
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define I2C_ADDRESS TWAR_bits._TWA

#define START_ACK                0x08 // start has been sent#define REP_START_ACK            0x10 // repeated start#define SLAVE_ADD_AND_WR_ACK     0x18 // Master transmit ( slave address + Write request ) ACK#define SLAVE_ADD_AND_RD_ACK     0x40 // Master transmit ( slave address + Read request ) ACK#define WR_BYTE_ACK              0x28 // Master transmit data ACK#define RD_BYTE_WITH_NACK        0x58 // Master received data with not ACK#define RD_BYTE_WITH_ACK         0x50 //Master received data with ACK#define SLAVE_ADD_RCVD_RD_REQ    0xA8 // means that slave address is received with write req#define SLAVE_ADD_RCVD_WR_REQ    0x60 // means that slave address is received with read req#define SLAVE_DATA_RECEIVED      0x80 // means that read byte request is received#define SLAVE_BYTE_TRANSMITTED   0xC0 // means that write byte request is received

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define I2C_SET_BIT_RATE_400KHZ() TWSR_bits._TWPS=0;TWBR = 0X0C
#define I2C_SET_BIT_RATE_100KHZ() TWSR_bits._TWPS=0;TWBR = 0X028
#define I2C_ENABLE_ACKNOWLEDGE_BIT() TWCR_bits._TWEA=1
#define I2C_ENABLE() TWCR_bits._TWEN=1

#define I2C_START_CONDITION_ROUTINE() TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTA)


#define I2C_START_OPERATION() TWCR=(1<<TWINT)|(1<<TWEN)
#define I2C_READ_ACK_OPERATION() TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA)
#define I2C_WAIT_FOR_OPERATION_FINISH() while(TWCR_bits._TWINT == 0) 
#define I2C_WAIT_FOR_START_OPERATION_STATUS() while(TWSR != START_ACK) 
#define I2C_WAIT_FOR_REPEATED_START_OPERATION_STATUS() while((TWSR & 0XF8) != REP_START_ACK)
#define I2C_WAIT_FOR_ADDRESS_WRITE_OPERATION_STATUS() while((TWSR & 0XF8) != SLAVE_ADD_AND_WR_ACK)
#define I2C_WAIT_FOR_ADDRESS_READ_OPERATION_STATUS() while((TWSR & 0XF8) != SLAVE_ADD_AND_RD_ACK)
#define I2C_WAIT_FOR_DATA_WRITE_OPERATION_STATUS() while((TWSR & 0XF8) != WR_BYTE_ACK)
#define I2C_WAIT_FOR_DATA_READ_OPERATION_STATUS_NACK() while((TWSR & 0XF8) != RD_BYTE_WITH_NACK)
#define I2C_WAIT_FOR_DATA_READ_OPERATION_STATUS_ACK() while((TWSR & 0XF8) != RD_BYTE_WITH_ACK)
#define I2C_STOP_CONDITION_ROUTINE() TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWSTO)
/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
void I2C_MasterInit(void);
void I2C_SlaveInit(void);
void I2C_StartCondition(void);
void I2C_RepeatedStart(void);
void I2C_SendAddress_WriteOperation(uint8 addr);
void I2C_SendAddress_ReadOperation(uint8 addr);
void I2C_WriteByte(uint8 data);
uint8 I2C_ReadByte_NACK(void);
void I2C_StopCondition(void);
uint8 I2C_ReadByte_ACK(void); 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif /* I2C_CORE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: I2C_Core.h 
 *********************************************************************************************************************/





