/**
 * ______________________________________________________________________________________________________
 * @author		:		HITESH BHOYAR
 * @file    	:		pmic_functions.h
 * @brief   	:		This file contains all the constants parameters for pmic
 * ______________________________________________________________________________________________________
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __pmic_functions_H__
#define __pmic_functions_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Define Macros -------------------------------------------------------------*/

/* Structure Definition ------------------------------------------------------*/

typedef struct _SRIC_2_PMIC
{
	unsigned char channel_0;
	unsigned char channel_1;
	unsigned char channel_2;
	unsigned char channel_3;
	unsigned char channel_4;
	unsigned char channel_5;
	unsigned char channel_6;
	unsigned char channel_7;
	unsigned char channel_8;
	unsigned char channel_9;
	unsigned char channel_a;
	unsigned char channel_b;
	unsigned char channel_c;
	unsigned char channel_d;
	unsigned char channel_e;
	unsigned char channel_f;
}Struct_SRIC_2_PMIC;
extern Struct_SRIC_2_PMIC sr2pm;

typedef struct _OBC_2_PMIC
{
	unsigned char channel_0;
	unsigned char channel_1;
	unsigned char channel_2;
	unsigned char channel_3;
	unsigned char channel_4;
	unsigned char channel_5;
	unsigned char channel_6;
	unsigned char channel_7;
	unsigned char channel_8;
	unsigned char channel_9;
	unsigned char channel_a;
	unsigned char channel_b;
	unsigned char channel_c;
	unsigned char channel_d;
	unsigned char channel_e;
	unsigned char channel_f;
}Struct_OBC_2_PMIC;
extern Struct_OBC_2_PMIC obc2pm;

/* External Configuration Function -------------------------------------------*/
unsigned char SRIC_2_PMIC_Check_CHKSUM(unsigned char* data);
void SRIC_2_PMIC_Parsing(unsigned char* data, Struct_SRIC_2_PMIC* sr2pm);
void SRIC_PMIC_USART2_Initialization(void);

unsigned char OBC_2_PMIC_Check_CHKSUM(unsigned char* data);
void OBC_2_PMIC_Parsing(unsigned char* data, Struct_OBC_2_PMIC* obc2pm);
void OBC_PMIC_USART3_Initialization(void);


void PMIC_CONFIG_SAT_POWER(Struct_OBC_2_PMIC* obc2pm);
void SEND_DATA_UART(unsigned char* data, USART_TypeDef * USARTx, int len);


#ifdef __cplusplus
}
#endif
#endif /*__pmic_functions_H__ */
