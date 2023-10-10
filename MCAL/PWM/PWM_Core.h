/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PWM_Core.h 
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef PWM_CORE_H_
#define PWM_CORE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "PWM_Cfg.h"
#include "BIT_Math.h"
#include "MCU.h"
#include "std_types.h"

#ifndef F_CPU
#define F_CPU 16000000U
#endif
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define	PWM_ENABLE 1U
#define	PWM_DISABLE 0U

#define	PWM_FAST 0U
#define	PWM_PHASE_CORRECT 1U
	
#define	PWM_NONINVERTED 1U
#define	PWM_INVERTED 0U

#define PWM_PRESC1 1U		
#define PWM_PRESC8 8U
#define PWM_PRESC32 32U
#define PWM_PRESC64 64U	
#define PWM_PRESC128 128U
#define PWM_PRESC256 256U		
#define PWM_PRESC1024 1024U



/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define SET_PWM0_FAST_MODE() TCCR0_bits.WGM00=1;TCCR0_bits.WGM01=1
#define SET_PWM0_PHASE_CORRECT_MODE() TCCR0_bits.WGM00=1;TCCR0_bits.WGM01=0

#define SET_PWM0_INVERTED_MODE() TCCR0_bits.COM=3
#define SET_PWM0_NON_INVERTED_MODE() TCCR0_bits.COM=2

#define PWM0_SET_PRESCALER_1() (TCCR0_bits.CS=1)
#define PWM0_SET_PRESCALER_8() (TCCR0_bits.CS=2)
#define PWM0_SET_PRESCALER_64() (TCCR0_bits.CS=3)
#define PWM0_SET_PRESCALER_256() (TCCR0_bits.CS=4)
#define PWM0_SET_PRESCALER_1024() (TCCR0_bits.CS=5)

#define SET_PWM1_FAST_MODE() TCCR1_bits.WGM13=1;TCCR1_bits.WGM12=1;TCCR1_bits.WGM11=1;TCCR1_bits.WGM10=0
#define SET_PWM1_PHASE_CORRECT_MODE() TCCR1_bits.WGM13=1;TCCR1_bits.WGM12=0;TCCR1_bits.WGM11=1;TCCR1_bits.WGM10=0

#define SET_PWM1_INVERTED_MODE() TCCR1_bits.COM1A=3
#define SET_PWM1_NON_INVERTED_MODE() TCCR1_bits.COM1A=2

#define PWM1_SET_PRESCALER_8() (TCCR1_bits.CS=2)
#define PWM1_SET_PRESCALER_64() (TCCR1_bits.CS=3)
#define PWM1_SET_PRESCALER_256() (TCCR1_bits.CS=4)
#define PWM1_SET_PRESCALER_1024() (TCCR1_bits.CS=5)




/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void PWM_Init(void);
void PWM0_Generate(uint8 Duty_Cycle);
void PWM1_Generate(uint8 Duty_Cycle , uint16 Frequency);
 
#endif /* PWM_CORE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: PWM_Core.h 
 *********************************************************************************************************************/





