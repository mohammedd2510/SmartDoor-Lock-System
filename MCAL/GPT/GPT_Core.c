/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  GPT_Core.c 
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "GPT_Core.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/
uint16 Timer0_Prescaler_value =0;
uint16 Timer1_Prescaler_value =0;
uint16 Timer2_Prescaler_value =0;
volatile uint32 Timer0_Total_num_ovfs;
volatile uint32 Timer0_Init_Value;
volatile uint32 Timer0_Total_num_compare_match;
volatile uint32 Timer0_compare_Reg_init;
volatile uint32 Timer0_TickTime;

volatile uint32 Timer1_Total_num_compare_match;
volatile uint32 Timer1_compare_Reg_init;
volatile uint32 Timer1_OVF_Cnt;
volatile uint32 Timer1_Total_num_ovfs;
volatile uint32 Timer1_Init_Value;
volatile uint32 Timer1_TickTime;
/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
#if (TIMER0_STATE == TIMER_ENABLE)
	static void TIMER0_Prescaler_Select (void);

	static void TIMER0_Mode_Select (void);

	static void TIMER0_Interrupt_Init (void);
#endif

#if (TIMER1_STATE == TIMER_ENABLE)
	static void TIMER1_Prescaler_Select (void);

	static void TIMER1_Mode_Select (void);

	static void TIMER1_Interrupt_Init (void);
#endif

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
#if (TIMER0_STATE == TIMER_ENABLE)
	static void TIMER0_Prescaler_Select (void){
			#if TIMER0_PRESCALER == NO_CLK_SRC
				TIMER0_SET_NO_CLK_SRC();
			#elif TIMER0_PRESCALER == PRESCALER_OFF
				TIMER0_SET_PRESCALER_OFF();
				Timer0_Prescaler_value =PRESCALER_OFF;
			#elif TIMER0_PRESCALER == PRESCALER_8
				TIMER0_SET_PRESCALER_8();
				Timer0_Prescaler_value =PRESCALER_8;
			#elif TIMER0_PRESCALER == PRESCALER_64
				TIMER0_SET_PRESCALER_64();
				Timer0_Prescaler_value =PRESCALER_64;
			#elif TIMER0_PRESCALER == PRESCALER_256
				TIMER0_SET_PRESCALER_256();
				Timer0_Prescaler_value =PRESCALER_256;
			#elif TIMER0_PRESCALER == PRESCALER_1024
				TIMER0_SET_PRESCALER_1024();
				Timer0_Prescaler_value =PRESCALER_1024;
			#elif TIMER0_PRESCALER == EXT_CLK_T0_FALLING_EDGE
				TIMER0_SET_EXT_CLK_T0_FALLING_EDGE();
			#elif TIMER0_PRESCALER == EXT_CLK_T0_RISING_EDGE
				TIMER0_SET_EXT_CLK_T0_RISING_EDGE();
			#endif
	}

	static void TIMER0_Mode_Select (void){
		#if TIMER0_MODE == TIMER0_NORMAL_MODE
		SET_TIMER0_NORMAL_MODE();
		#elif TIMER0_MODE == TIMER0_CTC_MODE
		SET_TIMER0_CTC_MODE();
		#endif
	}

	static void TIMER0_Interrupt_Init (void){
		#if TIMER0_MODE == TIMER0_NORMAL_MODE
			#if TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED
			SET_TIMER0_OVF_INTERRUPT_ENABLE();
			#elif TIMER0_INTERRUPT_STATE == INTERRUPT_DISABLED
			SET_TIMER0_OVF_INTERRUPT_DISABLE();
			#endif
		#elif TIMER0_MODE == TIMER0_CTC_MODE
			#if TIMER0_INTERRUPT_STATE == INTERRUPT_ENABLED
			SET_TIMER0_CTC_INTERRUPT_ENABLE();
			#elif TIMER0_INTERRUPT_STATE == INTERRUPT_DISABLED
			SET_TIMER0_CTC_INTERRUPT_DISABLE();
			#endif
		#endif
	}
#endif
#if (TIMER1_STATE == TIMER_ENABLE)
static void TIMER1_Prescaler_Select (void){
	#if TIMER1_PRESCALER == NO_CLK_SRC
	TIMER1_SET_NO_CLK_SRC();
	#elif TIMER1_PRESCALER == PRESCALER_OFF
	TIMER1_SET_PRESCALER_OFF();
	Timer1_Prescaler_value =PRESCALER_OFF;
	#elif TIMER1_PRESCALER == PRESCALER_8
	TIMER1_SET_PRESCALER_8();
	Timer1_Prescaler_value =PRESCALER_8;
	#elif TIMER1_PRESCALER == PRESCALER_64
	TIMER1_SET_PRESCALER_64();
	Timer1_Prescaler_value =PRESCALER_64;
	#elif TIMER1_PRESCALER == PRESCALER_256
	TIMER1_SET_PRESCALER_256();
	Timer1_Prescaler_value =PRESCALER_256;
	#elif TIMER1_PRESCALER == PRESCALER_1024
	TIMER1_SET_PRESCALER_1024();
	Timer1_Prescaler_value =PRESCALER_1024;
	#elif TIMER1_PRESCALER == EXT_CLK_T0_FALLING_EDGE
	TIMER1_SET_EXT_CLK_T0_FALLING_EDGE();
	#elif TIMER1_PRESCALER == EXT_CLK_T0_RISING_EDGE
	TIMER1_SET_EXT_CLK_T0_RISING_EDGE();
	#endif
}

static void TIMER1_Mode_Select (void){
	#if TIMER1_MODE == TIMER0_NORMAL_MODE
	SET_TIMER1_NORMAL_MODE();
	#elif TIMER1_MODE == TIMER0_CTC_MODE
	SET_TIMER1_CTC_MODE();
	#endif
}

static void TIMER1_Interrupt_Init (void){
	#if (TIMER1_MODE == TIMER1_NORMAL_MODE)
		#if TIMER1_INTERRUPT_STATE == INTERRUPT_ENABLED
		SET_TIMER1_OVF_INTERRUPT_ENABLE();
		#elif TIMER1_INTERRUPT_STATE == INTERRUPT_DISABLED
		SET_TIMER1_OVF_INTERRUPT_DISABLE();
		#endif
	#elif (TIMER1_MODE == TIMER1_CTC_MODE)
		#if TIMER1_INTERRUPT_STATE == INTERRUPT_ENABLED
		SET_TIMER1_CTC_INTERRUPT_ENABLE();
		#elif TIMER1_INTERRUPT_STATE == INTERRUPT_DISABLED
		SET_TIMER1_CTC_INTERRUPT_DISABLE();
		#endif
	#endif
	
}
#endif
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void GPT_SetTime(void)       
* \Description     : Sets the Time that the Enabled Timers will work with                                                                                                                                                  
*******************************************************************************/
void GPT_SetTime(void){
	#if (TIMER0_STATE == TIMER_ENABLE)
	 #if TIMER0_MODE == TIMER0_NORMAL_MODE
	uint32 Timer0_TickTime = ((Timer0_Prescaler_value)/(F_CPU/1000000));
	uint32 Timer0_Time = TIMER0_TIME_MILLI_SEC;
	uint32 Timer0_Total_num_of_ticks= (Timer0_Time*1000)/Timer0_TickTime;
    Timer0_Total_num_ovfs= Timer0_Total_num_of_ticks/256;
	Timer0_Init_Value = 256-(Timer0_Total_num_of_ticks%256);
	TCNT0 = Timer0_Init_Value;
	if(Timer0_Init_Value!=256){
		Timer0_Total_num_ovfs++;
	}
	
    #elif (TIMER0_MODE == TIMER0_CTC_MODE)
		 Timer0_TickTime = ((Timer0_Prescaler_value)/(F_CPU/1000000));
		 uint32 Timer0_Time = TIMER0_TIME_MILLI_SEC;
		 uint32 Timer0_Total_num_of_ticks= (Timer0_Time*1000)/Timer0_TickTime;
		 Timer0_Total_num_compare_match= Timer0_Total_num_of_ticks/TIMER0_COUNTING_REG_CAPACITY;
		 Timer0_compare_Reg_init = Timer0_Total_num_of_ticks%TIMER0_COUNTING_REG_CAPACITY;
		 if (Timer0_Total_num_compare_match >=1 ){
			 OCR0 = Timer0_compare_Reg_init;
		 }
		 else OCR0 = Timer0_Total_num_of_ticks-1;
	#endif
	#endif
	
	#if (TIMER1_STATE == TIMER_ENABLE)
		#if (TIMER1_MODE == TIMER1_NORMAL_MODE)
			Timer1_TickTime = ((Timer1_Prescaler_value)/(F_CPU/1000000));
			uint32 Timer1_Time = TIMER1_TIME_MILLI_SEC;
			uint32 Timer1_Total_num_of_ticks= (Timer1_Time*1000)/Timer1_TickTime;
			Timer1_Total_num_ovfs= Timer1_Total_num_of_ticks/TIMER1_COUNTING_REG_CAPACITY;
			Timer1_Init_Value = TIMER1_COUNTING_REG_CAPACITY-(Timer1_Total_num_of_ticks%TIMER1_COUNTING_REG_CAPACITY);
			TCNT1 = Timer1_Init_Value;
			if(Timer1_Init_Value!=TIMER1_COUNTING_REG_CAPACITY){
				Timer1_Total_num_ovfs++;
			}
		#elif (TIMER1_MODE == TIMER1_CTC_MODE)
			Timer1_TickTime = ((Timer1_Prescaler_value)/(F_CPU/1000000));
			uint32 Timer1_Time = TIMER1_TIME_MILLI_SEC;
			uint32 Timer1_Total_num_of_ticks= (Timer1_Time*1000)/Timer1_TickTime;
			Timer1_Total_num_compare_match= Timer1_Total_num_of_ticks/TIMER1_COUNTING_REG_CAPACITY;
			Timer1_compare_Reg_init = Timer1_Total_num_of_ticks%TIMER1_COUNTING_REG_CAPACITY;
			if (Timer1_Total_num_compare_match >=1){
				OCR1A = Timer1_compare_Reg_init;
			}
			else OCR1A = Timer1_Total_num_of_ticks-1;

		#endif

	#endif
	
}
/******************************************************************************
* \Syntax          : void GPT_Init(void)
* \Description     : Initialize General Purpose Timers
*******************************************************************************/
void GPT_Init(void){
	#if TIMER0_STATE == TIMER_ENABLE
	TIMER0_Prescaler_Select();
	TIMER0_Mode_Select();
	TIMER0_Interrupt_Init();
	#endif
	#if TIMER1_STATE == TIMER_ENABLE
	TIMER1_Mode_Select();
	TIMER1_Interrupt_Init();
	TIMER1_Prescaler_Select();
	#endif
}

/**********************************************************************************************************************
 *  END OF FILE: GPT_Core.c 
 *********************************************************************************************************************/

