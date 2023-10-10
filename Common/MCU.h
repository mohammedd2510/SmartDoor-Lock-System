/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  MCU.h
 *       Module: MCU Register Definitions
 *
 *  Description: has the definition of all the registers in the MCU  
 *  
 *********************************************************************************************************************/

#ifndef MCU_H_
#define MCU_H_
/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "std_types.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/*************************************** GPIO Registers ************************************************/
#define PHYSICAL_GPIO_ACCESS(addr)      (*(volatile uint8*)(addr))
#define GPIOA_BASE_ADDRRESS             (0X39)
#define GPIOB_BASE_ADDRRESS             (0X36)
#define GPIOC_BASE_ADDRRESS             (0X33)
#define GPIOD_BASE_ADDRRESS             (0X30)

#define GPIO_INPUT_REGISTER_PIN         (0X00)
#define GPIO_DIRCETION_REGISTER_DDR     (0X01)
#define GPIO_OUTPUT_REGISTER_PORT       (0X02)

/*Direction Registers*/
#define GPIOA_DIRECTION_REGISTER PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRRESS+GPIO_DIRCETION_REGISTER_DDR)
#define GPIOB_DIRECTION_REGISTER PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRRESS+GPIO_DIRCETION_REGISTER_DDR)
#define GPIOC_DIRECTION_REGISTER PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRRESS+GPIO_DIRCETION_REGISTER_DDR)
#define GPIOD_DIRECTION_REGISTER PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRRESS+GPIO_DIRCETION_REGISTER_DDR)

/*Output Registers*/
#define GPIOA_OUTPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRRESS+GPIO_OUTPUT_REGISTER_PORT)
#define GPIOB_OUTPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRRESS+GPIO_OUTPUT_REGISTER_PORT)
#define GPIOC_OUTPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRRESS+GPIO_OUTPUT_REGISTER_PORT)
#define GPIOD_OUTPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRRESS+GPIO_OUTPUT_REGISTER_PORT)

/*Input Registers*/
#define GPIOA_INPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOA_BASE_ADDRRESS+GPIO_INPUT_REGISTER_PIN)
#define GPIOB_INPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOB_BASE_ADDRRESS+GPIO_INPUT_REGISTER_PIN)
#define GPIOC_INPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOC_BASE_ADDRRESS+GPIO_INPUT_REGISTER_PIN)
#define GPIOD_INPUT_REGISTER PHYSICAL_GPIO_ACCESS(GPIOD_BASE_ADDRRESS+GPIO_INPUT_REGISTER_PIN)
/*******************************************************************************************************/
#define  SREG (*(volatile uint8*)(0x5F))
#define  MCUCR (*(volatile uint8*)(0x55))
#define  MCUCSR (*(volatile uint8*)(0x54))
#define  GICR (*(volatile uint8*)(0x5B))
#define  GIFR (*(volatile uint8*)(0x5A))


#define ADMUX (*(volatile uint8*)(0x27))
#define ADCSRA (*(volatile uint8*)(0x26))
#define ADCL (*(volatile uint8*)(0x24))
#define ADCH (*(volatile uint8*)(0x25))
#define SFIOR (*(volatile uint8*)(0x50))

/**********************************************/
typedef union {
	struct  
	{
		uint8 CS00 :1;
		uint8 CS01 :1;
		uint8 CS02 :1;
		uint8 WGM01:1;
		uint8 COM00:1;
		uint8 COM01 :1;
		uint8 WGM00 :1;
		uint8 FOC0 :1;
	};
	struct{
		uint8 CS:3 ;
		uint8    :1;
		uint8 COM:2;
		uint8    :1;
		uint8    :1;
		};
	}TCCR0_t;
	
#define TCCR0_bits (*(volatile TCCR0_t*)(0x53))
#define TCCR0 (*(volatile uint8*)(0x53))
#define TCNT0 (*(volatile uint8*)(0x52))

typedef struct
{
	uint8 TOIE0 :1;
	uint8 OCIE0 :1;
	uint8 TOIE1 :1;
	uint8 OCIE1B:1;
	uint8 OCIE1A:1;
	uint8 _TICIE1:1;
	uint8 TOIE2 :1;
	uint8 OCIE2 :1;
}TIMSK_bits_t;
#define TIMSK_bits (*(volatile TIMSK_bits_t*)(0x59))
#define TIMSK (*(volatile uint8*)(0x59))

typedef struct
{
	uint8 TOV0 :1;
	uint8 OCF0 :1;
	uint8 TOV1 :1;
	uint8 OCF1B:1;
	uint8 OCF1A:1;
	uint8 ICF1 :1;
	uint8 TOV2 :1;
	uint8 OCF2 :1;
}TIFR_bits_t;
#define TIFR_bits (*(volatile TIFR_bits_t*)(0x58))
#define TIFR (*(volatile uint8*)(0x58))

#define OCR0 (*(volatile uint8*)(0x5C))

typedef union {
	struct
	{
		uint8 CS10 :1;
		uint8 CS11 :1;
		uint8 CS12 :1;
		uint8 WGM12:1;
		uint8 WGM13:1;
		uint8      :1;
		uint8 _ICES1 :1;
		uint8 ICNC1 :1;
		uint8 WGM10 :1;
		uint8 WGM11 :1;
		uint8 FOC1B :1;
		uint8 FOC1A:1;
		uint8 COM1B0:1;
		uint8 COM1B1 :1;
		uint8 COM1A0 :1;
		uint8 COM1A1 :1;
	};
	struct{
		uint8 CS :3;
		uint8 :1;
		uint8:1;
		uint8      :1;
		uint8 :1;
		uint8 :1;
		uint8  :1;
		uint8 :1;
		uint8 :1;
		uint8 :1;
		uint8 COM1B:2;
		uint8 COM1A :2;
	};
}TCCR1_t;

#define TCCR1_bits (*(volatile TCCR1_t*)(0x4E))
#define TCCR1 (*(volatile uint16*)(0x4E))
#define TCCR1B (*(volatile uint8*)(0x4E))
#define TCNT1 (*(volatile uint16*)(0x4C))
#define OCR1A (*(volatile uint16*)(0x4A))
#define OCR1B (*(volatile uint16*)(0x48))
#define ICR1 (*(volatile uint16*)(0x46))

/******UART Registers *******/

typedef struct{
		uint8 _TXB8 :1;
		uint8 _RXB8:1;
		uint8 _UCSZ2:1;
		uint8 _TXEN :1;
		uint8 _RXEN :1;
		uint8 _UDRIE:1;
		uint8 _TXCIE :1;
		uint8 _RXCIE:1;
}UCSRB_t;

#define UCSRB_bits (*(volatile UCSRB_t*)(0x2A))
#define UCSRB (*(volatile uint8*)(0x2A))

typedef struct{
	uint8 _MPCM :1;
	uint8 _U2X:1;
	uint8 _PE:1;
	uint8 _DOR :1;
	uint8 _FE :1;
	uint8 _UDRE:1;
	uint8 _TXC :1;
	uint8 _RXC:1;
}UCSRA_t;

#define UCSRA_bits (*(volatile UCSRA_t*)(0x2B))
#define UCSRA (*(volatile uint8*)(0x2B))

typedef union{
	struct{
	uint8 _UCPOL :1;
	uint8 _UCSZ0:1;
	uint8 _UCSZ1:1;
	uint8 _USBS:1;
	uint8 _UPM0 :1;
	uint8 _UPM1 :1;
	uint8 _UMSEL :1;
	uint8 _URSEL:1;
	};
	struct{
		uint8  :1;
		uint8 _UCSZ:2;
		uint8 :1;
		uint8 _UPM :2;
		uint8  :1;
		uint8 :1;
	};
}UCSRC_t;

#define UCSRC_bits (*(volatile UCSRC_t*)(0x40))
#define UCSRC (*(volatile uint8*)(0x40))

struct{
	uint8 _UBRR :4;
	uint8 :7;
	uint8 _URSEL:1;
}UBBRH_t;

#define UBRRH_bits (*(volatile UBRRH_t*)(0x40))
#define UBRRH (*(volatile uint8*)(0x40))
#define UBRRL (*(volatile uint8*)(0x29))
#define UDR (*(volatile uint8*)(0x2c))
/**********************************************************************************************************************/
/******************SPI Registers******************/
typedef struct {
	union {
		 struct {
			 uint8 SPR:2; 
			 uint8 CPHA:1;
			 uint8 CPOL:1;
			 uint8 MSTR:1;
			 uint8 DORD:1;
			 uint8 SPE:1;
			 uint8 SPIE:1;
			}SPCR_BITS;
		uint8 SPCR;
		};
		union{
			 struct{
				uint8 SPI2X:1;
				uint8      :5;
				uint8 WCOL :1;
				uint8 SPIF :1;
				}SPSR_BITS;
			uint8 SPSR;
			};
		uint8 _SPDR;
	}SPI_REGISTERS;
#define SPI (*(volatile SPI_REGISTERS*)(0x2D))

/*****I2C Registers**********/
typedef struct{
	uint8 _TWIE :1;
	uint8       :1;
	uint8 _TWEN:1;
	uint8 _TWWC :1;
	uint8 _TWSTO :1;
	uint8 _TWSTA:1;
	uint8 _TWEA :1;
	uint8 _TWINT:1;
}TWCR_t;

#define TWCR_bits (*(volatile TWCR_t*)(0x56))
#define TWCR (*(volatile uint8*)(0x56))

typedef struct{
	uint8 _TWGCE :1;
	uint8 _TWA   :7;
}TWAR_t;

#define TWAR_bits (*(volatile TWAR_t*)(0x22))
#define TWAR (*(volatile uint8*)(0x22))
#define TWDR (*(volatile uint8*)(0x23))

typedef struct{
	uint8 _TWPS :2;
	uint8       :1;
	uint8 _TWS   :5;
}TWSR_t;

#define TWSR_bits (*(volatile TWSR_t*)(0x21))
#define TWSR (*(volatile uint8*)(0x21))
#define TWBR (*(volatile uint8*)(0x20))

#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/************************************************************************************/
 /*  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

 
#endif /* MCU_H_ */

/**********************************************************************************************************************
 *  END OF FILE: 
 *********************************************************************************************************************/


