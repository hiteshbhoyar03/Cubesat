/**
 * ______________________________________________________________________________________________________
 * @author		:		HITESH BHOYAR
 * @file    	:		sric_functions.h
 * @brief   	:		This file contains all the constants parameters for sric
 * ______________________________________________________________________________________________________
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __sric_functions_H__
#define __sric_functions_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Define Macros -------------------------------------------------------------*/

/* Structure Definition ------------------------------------------------------*/

typedef struct _PMIC_2_SRIC
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
}Struct_PMIC_2_SRIC;
extern Struct_PMIC_2_SRIC pm2sr;

typedef struct _OBC_2_SRIC
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
}Struct_OBC_2_SRIC;
extern Struct_OBC_2_SRIC obc2sr;

/* External Configuration Function -------------------------------------------*/
unsigned char PMIC_2_SRIC_Check_CHKSUM(unsigned char* data);
void PMIC_2_SRIC_Parsing(unsigned char* data, Struct_PMIC_2_SRIC* pm2sr);
void PMIC_SRIC_USART2_Initialization(void);

unsigned char OBC_2_SRIC_Check_CHKSUM(unsigned char* data);
void OBC_2_SRIC_Parsing(unsigned char* data, Struct_OBC_2_SRIC* obc2sr);
void OBC_SRIC_USART3_Initialization(void);


void SRIC_CONFIG_SAT_POWER(Struct_OBC_2_SRIC* obc2sr, Struct_PMIC_2_SRIC* pm2sr);
void SEND_DATA_UART(unsigned char* data, USART_TypeDef * USARTx, int len);


#ifdef __cplusplus
}
#endif
#endif /*__sric_functions_H__ */
