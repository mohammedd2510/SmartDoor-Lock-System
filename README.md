# **  SmartDoor Lock System Project Made by Mohamed Osama **

## Hardware used :
 1. Atmega32
 2. LCD 16x2
 3. HC-05 Bluetooth Module
 4. SG90 Servo Motor
 5. 24C08 EEPROM
 6. Buzzer
 7. Blue LED
 
 ## Software used :
 ### MCAL LAYER :
 1. DIO DRIVER
 2. PORT DRIVER
 3. GPT DRIVER
 4. PWM DRIVER
 5. IRQH DRIVER
 6. UART DRIVER
 7. I2C DRIVER

### HAL LAYER :
1. LCD DRIVER
2. BUZZER DRIVER
3. LED DRIVER
4. BLUETOOTH MODULE DRIVER
5. EEPROM DRIVER
6. SERVO MOTOR DRIVER

 ## Features :
 1. can set a new pin but must enter old pin first
 2. the new pin will be saved in external EEPROM that communicates with I2C Protocol
 3. it check the current pin to open the door that is described by a servo motor
 4. if you enter wrong pin 3 times buzzer will ring for 4 seconds and wrong pin message shown on LCD
 5. all inputs will be taken using Bluetooth module that communicates with UART Protocol
 6. if you enter the right pin servo motor will move 90 degrees for 3 seconds then return 0 degrees
 7. if you enter the right pin a welcome home message will be shown on the LCD and Blue LED ON

Note : The project is made by CFGS for each pin you can change it as you wish
