/**
 * ______________________________________________________________________________________________________
 * @author		:		HITESH BHOYAR
 * @file    	:		pmic_functions.c
 * @brief   	:		This file includes the functions for pmic
 * ______________________________________________________________________________________________________
 */

#include <pmic_functions.h>

Struct_SRIC_2_PMIC sr2pm;
Struct_OBC_2_PMIC obc2pm;


unsigned char SRIC_2_PMIC_Check_CHKSUM(unsigned char* data)
{
	unsigned short crc = 0xFFFF;

	for(int i=0;i<18;i++)
	{
		crc = crc - data[i];
	}

	return ((crc&0x00FF) == data[18]) && ((crc >> 8) == data[19]);
}

void SRIC_2_PMIC_Parsing(unsigned char* data, Struct_SRIC_2_PMIC* sr2pm)
{
	sr2pm->channel_0 = (unsigned char)(data[2]) & 0xFF;
	sr2pm->channel_1 = (unsigned char)(data[3]) & 0xFF;
	sr2pm->channel_2 = (unsigned char)(data[4]) & 0xFF;
	sr2pm->channel_3 = (unsigned char)(data[5]) & 0xFF;
	sr2pm->channel_4 = (unsigned char)(data[6]) & 0xFF;
	sr2pm->channel_5 = (unsigned char)(data[7]) & 0xFF;
	sr2pm->channel_6 = (unsigned char)(data[8]) & 0xFF;
	sr2pm->channel_7 = (unsigned char)(data[8]) & 0xFF;
	sr2pm->channel_8 = (unsigned char)(data[10]) & 0xFF;
	sr2pm->channel_9 = (unsigned char)(data[11]) & 0xFF;
	sr2pm->channel_a = (unsigned char)(data[12]) & 0xFF;
	sr2pm->channel_b = (unsigned char)(data[13]) & 0xFF;
	sr2pm->channel_c = (unsigned char)(data[14]) & 0xFF;
	sr2pm->channel_d = (unsigned char)(data[15]) & 0xFF;
	sr2pm->channel_e = (unsigned char)(data[16]) & 0xFF;
	sr2pm->channel_f = (unsigned char)(data[17]) & 0xFF;
}

void SRIC_PMIC_USART2_Initialization(void)
{

}


unsigned char OBC_2_PMIC_Check_CHKSUM(unsigned char* data)
{
	unsigned short crc = 0xFFFF;

	for(int i=0;i<18;i++)
	{
		crc = crc - data[i];
	}

	return ((crc&0x00FF) == data[18]) && ((crc >> 8) == data[19]);
}

void OBC_2_PMIC_Parsing(unsigned char* data, Struct_OBC_2_PMIC* obc2pm)
{
	obc2pm->channel_0 = (unsigned char)(data[2]) & 0xFF;
	obc2pm->channel_1 = (unsigned char)(data[3]) & 0xFF;
	obc2pm->channel_2 = (unsigned char)(data[4]) & 0xFF;
	obc2pm->channel_3 = (unsigned char)(data[5]) & 0xFF;
	obc2pm->channel_4 = (unsigned char)(data[6]) & 0xFF;
	obc2pm->channel_5 = (unsigned char)(data[7]) & 0xFF;
	obc2pm->channel_6 = (unsigned char)(data[8]) & 0xFF;
	obc2pm->channel_7 = (unsigned char)(data[8]) & 0xFF;
	obc2pm->channel_8 = (unsigned char)(data[10]) & 0xFF;
	obc2pm->channel_9 = (unsigned char)(data[11]) & 0xFF;
	obc2pm->channel_a = (unsigned char)(data[12]) & 0xFF;
	obc2pm->channel_b = (unsigned char)(data[13]) & 0xFF;
	obc2pm->channel_c = (unsigned char)(data[14]) & 0xFF;
	obc2pm->channel_d = (unsigned char)(data[15]) & 0xFF;
	obc2pm->channel_e = (unsigned char)(data[16]) & 0xFF;
	obc2pm->channel_f = (unsigned char)(data[17]) & 0xFF;
}

void OBC_PMIC_USART3_Initialization(void)
{

}

void PMIC_CONFIG_SAT_POWER(Struct_OBC_2_PMIC* obc2pm){

	/* EN 3V3 1 ------------------------------------------------------------------*/
	if( (obc2pm->channel_0 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_3V3_1_BUCK_PM_GPIO_Port, EN_3V3_1_BUCK_PM_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_3V3_1_BUCK_PM_GPIO_Port, EN_3V3_1_BUCK_PM_Pin);
	if( (obc2pm->channel_1 & 0x01) == 0x01 )
	{
		LL_GPIO_SetOutputPin(EN_3V3_1_BUCK_PM_GPIO_Port, EN_3V3_1_BUCK_PM_Pin);
		LL_GPIO_SetOutputPin(EN_3V3_1_PM_GPIO_Port, EN_3V3_1_PM_Pin);
	}
	else
		LL_GPIO_ResetOutputPin(EN_3V3_1_PM_GPIO_Port, EN_3V3_1_PM_Pin);


	/* EN 3V3 2 ------------------------------------------------------------------*/
	if( (obc2pm->channel_2 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_3V3_2_BUCK_PM_GPIO_Port, EN_3V3_2_BUCK_PM_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_3V3_2_BUCK_PM_GPIO_Port, EN_3V3_2_BUCK_PM_Pin);

	if( (obc2pm->channel_3 & 0x01) == 0x01 )
	{
		LL_GPIO_SetOutputPin(EN_3V3_2_BUCK_PM_GPIO_Port, EN_3V3_2_BUCK_PM_Pin);
		LL_GPIO_SetOutputPin(EN_3V3_2_PM_GPIO_Port, EN_3V3_2_PM_Pin);
	}
	else
		LL_GPIO_ResetOutputPin(EN_3V3_2_PM_GPIO_Port, EN_3V3_2_PM_Pin);


	/* EN 5V0 --------------------------------------------------------------------*/
	if( (obc2pm->channel_4 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_5V_BOOST_PM_GPIO_Port, EN_5V_BOOST_PM_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_5V_BOOST_PM_GPIO_Port, EN_5V_BOOST_PM_Pin);

	if( (obc2pm->channel_5 & 0x01) == 0x01 )
	{
		LL_GPIO_SetOutputPin(EN_5V_BOOST_PM_GPIO_Port, EN_5V_BOOST_PM_Pin);
		LL_GPIO_SetOutputPin(EN_5V_PM_GPIO_Port, EN_5V_PM_Pin);
	}
	else
		LL_GPIO_ResetOutputPin(EN_5V_PM_GPIO_Port, EN_5V_PM_Pin);


	/* EN UNREG 1 ----------------------------------------------------------------*/
	if( (obc2pm->channel_6 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_UNREG1_PM_GPIO_Port, EN_UNREG1_PM_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_UNREG1_PM_GPIO_Port, EN_UNREG1_PM_Pin);

	/* EN UNREG 2 ----------------------------------------------------------------*/
	if( (obc2pm->channel_7 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_UNREG2_PM_GPIO_Port, EN_UNREG2_PM_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_UNREG2_PM_GPIO_Port, EN_UNREG2_PM_Pin);


	/* MCU OBC -------------------------------------------------------------------*/
	if( (obc2pm->channel_8 & 0x01) == 0x01 ){
		LL_GPIO_SetOutputPin(EN_MCU_BUCK_PM_GPIO_Port, EN_MCU_BUCK_PM_Pin);
	}
	else
		LL_GPIO_ResetOutputPin(EN_MCU_BUCK_PM_GPIO_Port, EN_MCU_BUCK_PM_Pin);
	if( (obc2pm->channel_9 & 0x01) == 0x01 )
	{
		LL_GPIO_SetOutputPin(EN_MCU_BUCK_PM_GPIO_Port, EN_MCU_BUCK_PM_Pin);
		LL_GPIO_SetOutputPin(EN_MCU_3V3_PM_GPIO_Port, EN_MCU_3V3_PM_Pin);
	}
	else{
		LL_GPIO_ResetOutputPin(EN_MCU_3V3_PM_GPIO_Port, EN_MCU_3V3_PM_Pin);
	}

}


void SEND_DATA_UART(unsigned char* data, USART_TypeDef * USARTx, int len){

	unsigned short crc = 0xFFFF;

	for(int i=0;i<len;i++)
	{
		crc = crc - data[i];
	}
	data[len-2]=(crc&0x00FF);
	data[len-1]=(crc >> 8);

	for(int i=0;i<len;i++)
	{
		while(!LL_USART_IsActiveFlag_TXE(USARTx));
		LL_USART_TransmitData8(USARTx, data[i]);
	}

}
