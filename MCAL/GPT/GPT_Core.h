/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  GPT_Core.h 
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef GPT_CORE_H_
#define GPT_CORE_H_

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "MCU.h"
#include "std_types.h"
#include "BIT_Math.h"
#include "GPT_Cfg.h"
#ifndef F_CPU
#define F_CPU 16000000U
#endif
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define NO_CLK_SRC 0U
#define PRESCALER_OFF 1U
#define PRESCALER_8 8U
#define PRESCALER_32 32U
#define PRESCALER_64 64U
#define PRESCALER_128 128U
#define PRESCALER_256 256U
#define PRESCALER_1024 1024U
#define EXT_CLK_T0_FALLING_EDGE 6
#define EXT_CLK_T0_RISING_EDGE 7

#define TIMER0_NORMAL_MODE 0
#define TIMER0_CTC_MODE 2


#define TIMER1_NORMAL_MODE 0
#define TIMER1_CTC_MODE 2


#define INTERRUPT_ENABLED 1
#define INTERRUPT_DISABLED 0

#define TIMER_ENABLE 1
#define TIMER_DISABLE 0

#define  TIMER0_COUNTING_REG_CAPACITY 255U
#define  TIMER1_COUNTING_REG_CAPACITY 65535U
#define  TIMER2_COUNTING_REG_CAPACITY 255U




/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/
#define TIMER0_SET_NO_CLK_SRC() (TCCR0_bits.CS=0)
#define TIMER0_SET_PRESCALER_OFF() (TCCR0_bits.CS=1)
#define TIMER0_SET_PRESCALER_8() (TCCR0_bits.CS=2)
#define TIMER0_SET_PRESCALER_64() (TCCR0_bits.CS=3)
#define TIMER0_SET_PRESCALER_256 () (TCCR0_bits.CS=4)
#define TIMER0_SET_PRESCALER_1024() (TCCR0_bits.CS=5)
#define TIMER0_SET_EXT_CLK_T0_FALLING_EDGE() (TCCR0_bits.CS=6)
#define TIMER0_SET_EXT_CLK_T0_RISING_EDGE()  (TCCR0_bits.CS=7)

#define TIMER1_SET_NO_CLK_SRC() (TCCR1_bits.CS=0)
#define TIMER1_SET_PRESCALER_OFF() (TCCR1_bits.CS=1)
#define TIMER1_SET_PRESCALER_8() (TCCR1_bits.CS=2)
#define TIMER1_SET_PRESCALER_64() (TCCR1_bits.CS=3)
#define TIMER1_SET_PRESCALER_256 () (TCCR1_bits.CS=4)
#define TIMER1_SET_PRESCALER_1024() (TCCR1_bits.CS=5)
#define TIMER1_SET_EXT_CLK_T0_FALLING_EDGE() (TCCR1_bits.CS=6)
#define TIMER1_SET_EXT_CLK_T0_RISING_EDGE()  (TCCR1_bits.CS=7)


#define SET_TIMER0_NORMAL_MODE() TCCR0_bits.WGM00=0;TCCR0_bits.WGM01=0

#define SET_TIMER0_CTC_MODE() TCCR0_bits.WGM00=0;TCCR0_bits.WGM01=1



#define SET_TIMER1_NORMAL_MODE() TCCR1_bits.WGM13=0;TCCR1_bits.WGM12=0;TCCR1_bits.WGM11=0;TCCR1_bits.WGM10=0
#define SET_TIMER1_CTC_MODE() TCCR1_bits.WGM13=0;TCCR1_bits.WGM12=1;TCCR1_bits.WGM11=0;TCCR1_bits.WGM10=0


#define SET_TIMER0_OVF_INTERRUPT_ENABLE() TIMSK_bits.TOIE0=INTERRUPT_ENABLED
#define SET_TIMER0_OVF_INTERRUPT_DISABLE() TIMSK_bits.TOIE0=INTERRUPT_DISABLED
#define SET_TIMER0_CTC_INTERRUPT_ENABLE() TIMSK_bits.OCIE0=INTERRUPT_ENABLED
#define SET_TIMER0_CTC_INTERRUPT_DISABLE() TIMSK_bits.OCIE0=INTERRUPT_DISABLED

#define SET_TIMER1_OVF_INTERRUPT_ENABLE() TIMSK_bits.TOIE1=INTERRUPT_ENABLED
#define SET_TIMER1_OVF_INTERRUPT_DISABLE() TIMSK_bits.TOIE1=INTERRUPT_DISABLED
#define SET_TIMER1_CTC_INTERRUPT_ENABLE() TIMSK_bits.OCIE1A=INTERRUPT_ENABLED
#define SET_TIMER1_CTC_INTERRUPT_DISABLE() TIMSK_bits.OCIE1A=INTERRUPT_DISABLED


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern volatile uint32 Timer0_Total_num_ovfs;
extern volatile uint32 Timer0_Init_Value;
extern volatile uint32 Timer0_Total_num_compare_match;
extern volatile uint32 Timer0_compare_Reg_init;
extern volatile uint32 Timer1_Total_num_compare_match;
extern volatile uint32 Timer1_compare_Reg_init;
extern volatile uint32 Timer1_OVF_Cnt;
extern volatile uint32 Timer1_Total_num_ovfs;
extern volatile uint32 Timer1_Init_Value;
extern uint16 Timer1_Prescaler_value;
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
void GPT_SetTime(void);

void GPT_Init(void);

 
#endif /* GPT_CORE_H_ */

/**********************************************************************************************************************
 *  END OF FILE: GPT_Core.h 
 *********************************************************************************************************************/





