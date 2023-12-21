/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PORT_LCFG_.h
 *       Module:  Port configuration module
 *
 *********************************************************************************************************************/
#ifndef PORT_LCFG_H_
#define PORT_LCFG_H_

/**********************************************************************************************
PORTA_PIN0 ---> #0    PORTB _PIN0 ---> #8         PORTC_PIN0 ---> #16       PORTD_PIN0 ---> #24  
PORTA_PIN1 ---> #1    PORTB _PIN1 ---> #9         PORTC_PIN1 ---> #17       PORTD_PIN1 ---> #25
PORTA_PIN2 ---> #2    PORTB _PIN2 ---> #10        PORTC_PIN2 ---> #18       PORTD_PIN2 ---> #26
PORTA_PIN3 ---> #3    PORTB _PIN3 ---> #11        PORTC_PIN3 ---> #19       PORTD_PIN3 ---> #27
PORTA_PIN4 ---> #4    PORTB _PIN4 ---> #12        PORTC_PIN4 ---> #20       PORTD_PIN4 ---> #28
PORTA_PIN5 ---> #5    PORTB _PIN5 ---> #13        PORTC_PIN5 ---> #21       PORTD_PIN5 ---> #29
PORTA_PIN6 ---> #6    PORTB _PIN6 ---> #14        PORTC_PIN6 ---> #22       PORTD_PIN6 ---> #30
PORTA_PIN7 ---> #7    PORTB _PIN7 ---> #15        PORTC_PIN7 ---> #23       PORTD_PIN7 ---> #31
**********************************************************************************************/


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "std_types.h"
#include "LCD_Cfg.h"
#include "BUZZ_Cfg.h"
#include "SERVO_MOTOR_Cfg.h"
#include "LED_Cfg.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define  DEFINED_PINS                10
#define  NUMBER_OF_EACH_PORT_PINS    8

#define PORTA_PIN0 0    
#define PORTA_PIN1 1
#define PORTA_PIN2 2
#define PORTA_PIN3 3 
#define PORTA_PIN4 4
#define PORTA_PIN5 5 
#define PORTA_PIN6 6 
#define PORTA_PIN7 7 
#define PORTB_PIN0 8 
#define PORTB_PIN1 9 
#define PORTB_PIN2 10 
#define PORTB_PIN3 11
#define PORTB_PIN4 12
#define PORTB_PIN5 13
#define PORTB_PIN6 14
#define PORTB_PIN7 15
#define PORTC_PIN0 16
#define PORTC_PIN1 17
#define	PORTC_PIN2 18
#define	PORTC_PIN3 19
#define	PORTC_PIN4 20
#define	PORTC_PIN5 21
#define	PORTC_PIN6 22
#define	PORTC_PIN7 23
#define	PORTD_PIN0 24
#define	PORTD_PIN1 25
#define	PORTD_PIN2 26
#define	PORTD_PIN3 27
#define	PORTD_PIN4 28
#define	PORTD_PIN5 29
#define	PORTD_PIN6 30
#define	PORTD_PIN7 31


/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

typedef enum
{
	PIN_INPUT = 0,
	PIN_OUTPUT
}PIN_DIRECTION;

typedef struct
{
	uint8 PIN_NUM ;
	PIN_DIRECTION PIN_DIR ;
}PIN_PARAMETERS;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const PIN_PARAMETERS PORT_Initialization[DEFINED_PINS];
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/


 
#endif /* PORT_LCFG _H_ */

/**********************************************************************************************************************
 *  END OF FILE: PORT_LCFG_.h
 *********************************************************************************************************************/





