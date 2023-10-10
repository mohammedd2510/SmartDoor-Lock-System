/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IRQH_Core.c 
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IRQH_Core.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
 void (*CallBack_PtrFunc[20])(void)={NULL};
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



void IRQH_SetGlobalINT(uint8 Global_INT_Status){
	switch (Global_INT_Status){
		case INT_ENABLE : 
		SET_BIT(SREG,7);
		break;
		case INT_DISABLE:
		CLR_BIT(SREG,7);
		break;
		default:
		break;
	}
}
void IRQH_SetExternalINT(void){
	#if (EXT_INT_0 == INT_ENABLE)
	SET_BIT (GICR,6);
		#if (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
				CLR_BIT (MCUCR,0);
				SET_BIT (MCUCR,1);
		#elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
				SET_BIT (MCUCR,0);
				SET_BIT (MCUCR,1);
		#elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_ANY_LOGICAL_CHANGE)
				SET_BIT (MCUCR,0);
				CLR_BIT (MCUCR,1);
		#elif (EXT_INT0_TRIGGER == EXT_INT_TRIGGER_LOW_LEVEL)
				CLR_BIT (MCUCR,0);
				CLR_BIT (MCUCR,1);
		#endif //EXT_INT0_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE
	#endif // (EXT_INT_0 == INT_ENABLE)
	#if (EXT_INT_1 == INT_ENABLE)
	 SET_BIT (GICR,7);
	 #if (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
	 CLR_BIT (MCUCR,2);
	 SET_BIT (MCUCR,3);
	 #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
	 SET_BIT (MCUCR,2);
	 SET_BIT (MCUCR,3);
	 #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_ANY_LOGICAL_CHANGE)
	 SET_BIT (MCUCR,2);
	 CLR_BIT (MCUCR,3);
	 #elif (EXT_INT1_TRIGGER == EXT_INT_TRIGGER_LOW_LEVEL)
	 CLR_BIT (MCUCR,2);
	 CLR_BIT (MCUCR,3);
	 #endif //EXT_INT1_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE
	#endif
	#if (EXT_INT_2 == INT_ENABLE)
	SET_BIT (GICR,5);
	#if (EXT_INT2_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE)
	CLR_BIT (MCUCSR,6);
	#elif (EXT_INT2_TRIGGER == EXT_INT_TRIGGER_RISING_EDGE)
	SET_BIT (MCUCSR,6);
	#endif //EXT_INT2_TRIGGER == EXT_INT_TRIGGER_FALLING_EDGE
	#endif
}
void IRQH_Set_CallBack(uint8 Interrupt_Vector_Index, void (*p)(void)){
	CallBack_PtrFunc[Interrupt_Vector_Index]=p;
}
ISR(INT0_vect){
	if(CallBack_PtrFunc[External_Interrupt_Request_0_VECTOR_INDEX]!=NULL){
		(CallBack_PtrFunc[External_Interrupt_Request_0_VECTOR_INDEX])();
	}
}
ISR(ADC_vect){
	if(CallBack_PtrFunc[ADC_Conversion_Complete_VECTOR_INDEX]!=NULL){
		(CallBack_PtrFunc[ADC_Conversion_Complete_VECTOR_INDEX])();
	}
}
ISR(TIMER0_OVF_vect){
	static uint32 cnt =0 ;
	cnt++;
	if (cnt==Timer0_Total_num_ovfs)
	{
		cnt=0;
		TCNT0=Timer0_Init_Value;
		if(CallBack_PtrFunc[Timer_Counter0_Overflow_VECTOR_INDEX]!=NULL){
			(CallBack_PtrFunc[Timer_Counter0_Overflow_VECTOR_INDEX])();
		}
	}
}
ISR(TIMER0_COMP_vect){
	static uint32 cnt =0 ;
	if (Timer0_Total_num_compare_match>=1)
	{
		OCR0 = TIMER0_COUNTING_REG_CAPACITY;
		if (cnt == Timer0_Total_num_compare_match)
		{
			if(CallBack_PtrFunc[Timer_Counter0_Compare_Match_VECTOR_INDEX]!=NULL){
				(CallBack_PtrFunc[Timer_Counter0_Compare_Match_VECTOR_INDEX])();
			}
			cnt=0;
			OCR0 = Timer0_compare_Reg_init;
		}
		else cnt++;
	}
	else {
		if(CallBack_PtrFunc[Timer_Counter0_Compare_Match_VECTOR_INDEX]!=NULL){
			(CallBack_PtrFunc[Timer_Counter0_Compare_Match_VECTOR_INDEX])();
		}
	}
}
ISR(TIMER1_COMPA_vect){
	static uint8 cnt =0 ;
	if (Timer1_Total_num_compare_match>=1)
	{
		OCR1A = TIMER1_COUNTING_REG_CAPACITY;
		if (cnt == Timer1_Total_num_compare_match)
		{
			if(CallBack_PtrFunc[Timer_Counter1_Compare_Match_A_VECTOR_INDEX]!=NULL){
				(CallBack_PtrFunc[Timer_Counter1_Compare_Match_A_VECTOR_INDEX])();
			}
			cnt=0;
			OCR1A = Timer1_compare_Reg_init;
		}
	else cnt++;
	}
	else {
		if(CallBack_PtrFunc[Timer_Counter1_Compare_Match_A_VECTOR_INDEX]!=NULL){
			(CallBack_PtrFunc[Timer_Counter1_Compare_Match_A_VECTOR_INDEX])();
		}
	}
}
ISR (TIMER1_OVF_vect){
	Timer1_OVF_Cnt++;
	#if (ICU_STATUS == ICU_DISABLE)
	if (Timer1_OVF_Cnt==Timer1_Total_num_ovfs)
	{
		Timer1_OVF_Cnt=0;
		TCNT1=Timer1_Init_Value;
		if(CallBack_PtrFunc[Timer_Counter1_Overflow_VECTOR_INDEX]!=NULL){
			(CallBack_PtrFunc[Timer_Counter1_Overflow_VECTOR_INDEX])();
		}
	}
	#endif
}
ISR(USART_RXC_vect){
	if(CallBack_PtrFunc[USART_Rx_Complete_VECTOR_INDEX]!=NULL){
		(CallBack_PtrFunc[USART_Rx_Complete_VECTOR_INDEX])();
	}
}
/*ISR (TIMER1_CAPT_vect){
	ICU_Cnt++;
	if (ICU_Cnt == 1)
	{
		Cap1 = ICR1;
		Timer1_OVF_Cnt =0;
		SET_ICU_FALLING_EDGE();
	}
	else if (ICU_Cnt == 2){
		Cap2 = ICR1 + (Timer1_OVF_Cnt *TIMER1_COUNTING_REG_CAPACITY);
		#if ICU_FUNCTION == CAPTURE_ON_TIME
			SET_ICU_INTERRUPT_DISABLE();
		#elif ICU_FUNCTION == CAPTURE_FULL_TIME
			SET_ICU_RISING_EDGE();
		#endif
	}
	#if (ICU_FUNCTION == CAPTURE_FULL_TIME)
		else if(ICU_Cnt == 3){
			Cap3=ICR1 + (Timer1_OVF_Cnt *TIMER1_COUNTING_REG_CAPACITY);
				TCNT1=0;
				SET_ICU_INTERRUPT_DISABLE();
		}
	#endif
}*/
/**********************************************************************************************************************
 *  END OF FILE: IRQH_Core.h 
 *********************************************************************************************************************/
