/*
 * App.c
 *
 * Created: 9/25/2023 3:34:43 PM
 * Author : Mohamed Osama
 */ 

#include "App.h"	

int main(void)
{
	SmartDoor_Initialize(); // Initialize Pins Direction to be Output/Input
    while (1) 
    {
		SmartDoor_Start();
	}
}

