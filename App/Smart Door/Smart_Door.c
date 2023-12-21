/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Smart_Door.c 
 *      \details  - This Project is about SmartDoor lockSystem you must enter the right pin for the Servo motor 
				    That describes the door moves 90 degree ,
				  - you have also the ability to set new pin but you must enter the Old pin First 
				  - The new pin is saved in the external EEPROM that uses I2C for Communication 
				  - Also all the inputs are taken using BlueTooth Module that uses UART Protocol for communication 
				  - if you enter the pin wrong for 3 times the Buzzer will ring for 4 seconds
				  - everything will be displayed using 16x2 Character LCD
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Smart_Door.h"

/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
static uint8 pin_Char=0; // Represents each password number you enter
static uint8 Current_pin[PIN_SIZE]={'0','0','0','0'}; // Contains the predefined Password
static uint8 pin_Number_Check[PIN_SIZE]={0}; // Contains The Password the User writes to check it
static uint8 Attempts_Flag=0; // Contains the Number of Attempts
static uint8 Wrong_Password_Flag=0; // Flag to check if password Wrong
static uint8 pin_Counter=0;
static Lock_status_t Lock_Status=INIT_STATE; // Contains The Status of Lock if it sets new pin or check current pin
/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
static void Welcome_Message(void);
static void Unlocked_Door_Routine(void);
static void Wrong_Password_Message(void);
static void Wrong_Password_3Times_Routine(void);
static void Check_Password(void);
static void Get_Password(void);
static void Get_New_Password(void);
static void Check_Current_Pin_Routine(void);
static void Select_Lock_Status(void);
static void Setting_New_Pin(void);
static void Set_New_Pin_Routine(void);

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : static void Select_Lock_Status(void)
* \Description     : This Function lets the user to choose from two options 
					 1-Set New Pin
					 2-Enter Your Pin 
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Select_Lock_Status(void){
	LCD_GoTo(0,0);
	LCD_WriteString("1:Set New PIN");
	LCD_GoTo(1,0);
	LCD_WriteString("2:Enter Your PIN");
	Bluetooth_Select_Variable(&Lock_Status);
	Bluetooth_Start_Receiving();
	while(Lock_Status!=SET_NEW_PIN && Lock_Status!=CHEK_CURRENT_PIN )
	{
		while(Bluetooth_Check_DataReceived()==0);
	}
	Bluetooth_Stop_Receiving();
	LCD_Clear();
}
/******************************************************************************
* \Syntax          : static void Check_Current_Pin_Routine(void)
* \Description     : This Function let user enter the current pin to check it
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Check_Current_Pin_Routine(void){
	LCD_GoTo(0,0);
	LCD_WriteString(" Enter Pin :");
	LCD_GoTo(1,5);
	Bluetooth_Select_Variable(&pin_Char);
	Get_Password();
	Check_Password();
	if (Wrong_Password_Flag == 1)
	{
		Attempts_Flag++;
		if (Attempts_Flag ==3)
		{
			Wrong_Password_3Times_Routine();
		}
		else
		{
			Wrong_Password_Message();
		}
	}
	else
	{
		Unlocked_Door_Routine();
		Lock_Status=INIT_STATE;
	}
	LCD_Clear();
}
/******************************************************************************
* \Syntax          : static void Set_New_Pin_Routine(void)
* \Description     : This Function let user enter set new pin routine and checks old pin
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Set_New_Pin_Routine(void){
	LCD_GoTo(0,0);
	LCD_WriteString("Enter Old Pin :");
	LCD_GoTo(1,5);
	Bluetooth_Select_Variable(&pin_Char);
	Get_Password();
	Check_Password();
	if (Wrong_Password_Flag == 1)
	{
		Attempts_Flag++;
		if (Attempts_Flag ==3)
		{
			Wrong_Password_3Times_Routine();
		}
		else
		{
			Wrong_Password_Message();
		}
	}
	else 
	{
		LCD_Clear();
		Setting_New_Pin();
		Lock_Status=INIT_STATE;
	}
	LCD_Clear();
}
/******************************************************************************
* \Syntax          : static void Welcome_Message(void)
* \Description     : Shows The Welcome Message of The Application 
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Welcome_Message(void){
	LCD_GoTo(0,0);
	LCD_WriteString(" Lock Door ");
	LCD_WriteChar(DOOR_ICON);
	LCD_WriteChar(DOOR_LOCKED_ICON);
	LCD_GoTo(1,0);
	LCD_WriteString("   Project ");
	_delay_ms(2000);
	LCD_Clear();
	LCD_WriteString("    Made By");
	LCD_GoTo(1,0);
	LCD_WriteString("Mohamed Osama ");
	LCD_WriteChar(Smile_Face);
	_delay_ms(2000);
	LCD_Clear();
	LCD_WriteString(" You have Only ");
	LCD_GoTo(1,0);
	LCD_WriteString("  3 Attempts ");
	_delay_ms(2000);
	LCD_Clear();	
}
/******************************************************************************
* \Syntax          : static void Get_Password(void)
* \Description     : This Function Gets The Password From User
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Get_Password(void){
	Bluetooth_Start_Receiving();
	for (pin_Counter=0;pin_Counter<PIN_SIZE;pin_Counter++)
	{
		while(Bluetooth_Check_DataReceived()==0);
		if ((pin_Char>='0')&&(pin_Char<='9'))
		{
			pin_Number_Check[pin_Counter]=pin_Char;
			LCD_WriteChar('*');
		}
		else pin_Counter--;
	}
	Bluetooth_Stop_Receiving();
}
/******************************************************************************
* \Syntax          : static void Get_New_Password(void)
* \Description     : This Function Gets New Password From User
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Get_New_Password(void){
	Bluetooth_Start_Receiving();
	for (pin_Counter=0;pin_Counter<PIN_SIZE;pin_Counter++)
	{
		while(Bluetooth_Check_DataReceived()==0);
		if ((pin_Char>='0')&&(pin_Char<='9'))
		{
			Current_pin[pin_Counter]=pin_Char;
			LCD_WriteChar('*');
		}
		else pin_Counter--;
	}
	Bluetooth_Stop_Receiving();
}
/******************************************************************************
* \Syntax          : static void Check_Password(void)
* \Description     : This Function Checks if The Password written Wrong or right
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Check_Password(void){
	for (pin_Counter=0;pin_Counter<PIN_SIZE;pin_Counter++)
	{
		if (Current_pin[pin_Counter] != pin_Number_Check[pin_Counter])
		{
			Wrong_Password_Flag =1;
			break;
		}
	}
}
/******************************************************************************
* \Syntax          : static void Wrong_Password_3Times_Routine(void)
* \Description     : This Function fires Alarm cause you run out of attempts and shows wrong password message
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Wrong_Password_3Times_Routine(void){
	LCD_Clear();
	LCD_WriteString(" Wrong Password ");
	LCD_GoTo(1,0);
	LCD_WriteString("3 Times Alarm On");
	LED_SetValue(LED_RED,LED_HIGH);
	BUZZ_ON();
	_delay_ms(4000);
	LED_SetValue(LED_RED,LED_LOW);
	BUZZ_OFF();
	Attempts_Flag=2;
	Wrong_Password_Flag=0;
	LCD_Clear();
}
/******************************************************************************
* \Syntax          : static void Wrong_Password_Message(void)
* \Description     : This Function Shows the Wrong Password Message
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Wrong_Password_Message(void){
	Wrong_Password_Flag=0;
	LCD_Clear();
	LED_SetValue(LED_RED,LED_HIGH);
	LCD_WriteString(" Wrong Password ");
	LCD_GoTo(1,0);
	LCD_WriteString("   Try Again   ");
	_delay_ms(1300);
	LED_SetValue(LED_RED,LED_LOW);
	LCD_Clear();
}
/******************************************************************************
* \Syntax          : static void Unlocked_Door_Routine(void)
* \Description     : This Function unlock the door and shows welcome Home Message 
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Unlocked_Door_Routine(void){
	Attempts_Flag =0;
	LCD_Clear();
	LED_SetValue(LED_BLUE,LED_HIGH);
	LCD_WriteString(" Welcome Home ");
	LCD_WriteChar(DOOR_UNLOCKED_ICON);
	ServoMotor_SetDegree(90);
	_delay_ms(2800);
	ServoMotor_SetDegree(0);
	LED_SetValue(LED_BLUE,LED_LOW);
	LCD_Clear();
}
/******************************************************************************
* \Syntax          : static void Setting_New_Pin(void)
* \Description     : This Function let user enter new pin after he enters the old pin right
				     and Saves the new pin in the EEPROM
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
static void Setting_New_Pin(void){
	LCD_GoTo(0,0);
	LCD_WriteString("Enter New Pin :");
	LCD_GoTo(1,5);
	Get_New_Password();
	EEPROM_WriteMultipleByte(EEPROM_Address,0X00,Current_pin,PIN_SIZE);
	LCD_Clear();
	LCD_WriteString("  PIN Changed");
	LCD_GoTo(1,0);
	LCD_WriteString("  Successfully  ");
	_delay_ms(2200);
}

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : void SmartDoor_Initialize(void)
* \Description     : Initialize The Smart Door Application and Shows The Welcome Message
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
void SmartDoor_Initialize(void){
	PORT_Init();
	LCD_Init();
	Bluetooth_Init();
	Bluetooth_Select_Variable(&pin_Char);
	ServoMotor_Init();
	EEPROM_INIT();
	_delay_ms(10);
	EEPROM_ReadMultipleByte(EEPROM_Address ,0X00,Current_pin,PIN_SIZE);
	LCD_Custom_Char_Init();
	Welcome_Message();
}
/******************************************************************************
* \Syntax          : void SmartDoor_Start(void)
* \Description     : Start The SmartDoor Application
* \Parameters	   : void
* \Return value:   : void
*******************************************************************************/
void SmartDoor_Start(void){
	if (Lock_Status == INIT_STATE)
	{
		Select_Lock_Status();
	}
	else if (Lock_Status == CHEK_CURRENT_PIN){
		Check_Current_Pin_Routine();	
	}
	else if (Lock_Status == SET_NEW_PIN){
		Set_New_Pin_Routine();
	}
	
}
/**********************************************************************************************************************
 *  END OF FILE: Smart_Door.c 
 *********************************************************************************************************************/
