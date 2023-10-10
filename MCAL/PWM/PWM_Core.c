/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  PWM_Core.c 
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "PWM_Core.h"


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
* \Syntax          : void PWM_Init(void)
* \Description     : Initialize The PWM Mode and Type
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
void PWM_Init(void){
	#if (PWM0_STATE == PWM_ENABLE)
		#if (PWM0_TYPE == PWM_FAST)
			SET_PWM0_FAST_MODE();
		#elif (PWM0_TYPE == PWM_PHASE_CORRECT)
			SET_PWM0_PHASE_CORRECT_MODE();
		#endif /*(PWM0_TYPE == PWM_FAST) */
		
		#if (PWM0_MODE == PWM_NONINVERTED)
			SET_PWM0_NON_INVERTED_MODE();
		#elif (PWM0_MODE == PWM_INVERTED)
			SET_PWM0_INVERTED_MODE();
		#endif
		
	#endif /* (PWM0_STATE == PWM_ENABLE) */
	
	#if (PWM1_STATE == PWM_ENABLE)
		#if (PWM1_TYPE == PWM_FAST)
		SET_PWM1_FAST_MODE();
		#elif (PWM1_TYPE == PWM_PHASE_CORRECT)
		SET_PWM1_PHASE_CORRECT_MODE();
		#endif /*(PWM1_TYPE == PWM_FAST) */
		
		#if (PWM1_MODE == PWM_NONINVERTED)
		SET_PWM1_NON_INVERTED_MODE();
		#elif (PWM1_MODE == PWM_INVERTED)
		SET_PWM1_INVERTED_MODE();
		#endif
	#endif /* (PWM1_STATE == PWM_ENABLE) */
}
/******************************************************************************
* \Syntax          : void PWM0_Generate(uint8 Duty_Cycle)
* \Description     : Generate PWM Signal Using Timer0
* \Parameters	   : uint8 Duty_Cycle , Duty Cycle to be generated
* \Return value:   : void
*******************************************************************************/
void PWM0_Generate(uint8 Duty_Cycle){
	#if (PWM0_STATE == PWM_ENABLE)
		#if (PWM0_TYPE == PWM_FAST)
			#if (PWM0_MODE == PWM_NONINVERTED)
			OCR0 = ((Duty_Cycle * 256)/100);
			#elif (PWM0_MODE == PWM_INVERTED)
			OCR0 = 255-((Duty_Cycle * 256)/100);
			#endif /* (PWM0_MODE == PWM_NONINVERTED) */
		#elif (PWM0_TYPE == PWM_PHASE_CORRECT)
			#if (PWM0_MODE == PWM_NONINVERTED)
			OCR0 = ((Duty_Cycle * 255)/100);
			#elif (PWM0_MODE == PWM_INVERTED)
			OCR0 = 255-((Duty_Cycle * 255)/100);
			#endif /* (PWM0_MODE == PWM_NONINVERTED) */
		#endif /*(PWM0_TYPE == PWM_FAST) */
		#if (PWM0_PRESC == PWM_PRESC1)
		PWM0_SET_PRESCALER_1();
		#elif (PWM0_PRESC == PWM_PRESC8)
			PWM0_SET_PRESCALER_8();
		#elif (PWM0_PRESC == PWM_PRESC64)
			PWM0_SET_PRESCALER_64();
		#elif (PWM0_PRESC == PWM_PRESC256)
			PWM0_SET_PRESCALER_256();
		#elif (PWM0_PRESC == PWM_PRESC1024)
			PWM0_SET_PRESCALER_1024();	
		#endif /*(PWM0_PRESC == PWM_PRESC8)*/
	#endif /* (PWM0_STATE == PWM_ENABLE) */
}
/******************************************************************************
* \Syntax          : void PWM1_Generate(uint8 Duty_Cycle , uint16 Frequency)
* \Description     : Generate PWM Signal Using Timer1
* \Parameters	   : uint8 Duty_Cycle - Duty Cycle of signal generated , uint16 Frequency - Frequence of generated Signal
* \Return value:   : void
*******************************************************************************/
void PWM1_Generate(uint8 Duty_Cycle , uint16 Frequency){
uint16 TOP =0 ;
	#if (PWM1_STATE == PWM_ENABLE)
	#if (PWM1_TYPE == PWM_FAST)
		TOP= (F_CPU /(Frequency * PWM1_PRESC));
		ICR1 = TOP;
	#if (PWM1_MODE == PWM_NONINVERTED)
	OCR1A = ((Duty_Cycle * (TOP+1))/100)-1;
	#elif (PWM1_MODE == PWM_INVERTED)
	OCR1A = TOP-((Duty_Cycle * (TOP+1))/100);
	#endif /* (PWM1_MODE == PWM_NONINVERTED) */
	#elif (PWM1_TYPE == PWM_PHASE_CORRECT)
	TOP= (F_CPU /(2*Frequency * PWM1_PRESC));
	ICR1 = TOP;
	#if (PWM1_MODE == PWM_NONINVERTED)
	OCR1A = ((Duty_Cycle * TOP)/100);
	#elif (PWM1_MODE == PWM_INVERTED)
	OCR1A = TOP-((Duty_Cycle * TOP)/100);
	#endif /* (PWM1_MODE == PWM_NONINVERTED) */
	#endif /*(PWM1_TYPE == PWM_FAST) */
	#if (PWM1_PRESC == PWM_PRESC8)
	PWM1_SET_PRESCALER_8();
	#elif (PWM1_PRESC == PWM_PRESC64)
	PWM1_SET_PRESCALER_64();
	#elif (PWM1_PRESC == PWM_PRESC256)
	PWM1_SET_PRESCALER_256();
	#elif (PWM1_PRESC == PWM_PRESC1024)
	PWM1_SET_PRESCALER_1024();
	#endif /*(PWM1_PRESC == PWM_PRESC8)*/
	#endif /* (PWM1_STATE == PWM_ENABLE) */
}



/**********************************************************************************************************************
 *  END OF FILE: PWM_Core.c 
 *********************************************************************************************************************/
