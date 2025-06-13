/**
 * ______________________________________________________________________________________________________
 * @author		:		HITESH BHOYAR
 * @file    	:		sric_functions.c
 * @brief   	:		This file includes the functions for sric
 * ______________________________________________________________________________________________________
 */

#include <sric_functions.h>

Struct_OBC_2_SRIC obc2sr;
Struct_PMIC_2_SRIC pm2sr;

unsigned char PMIC_2_SRIC_Check_CHKSUM(unsigned char* data)
{
	unsigned short crc = 0xFFFF;

	for(int i=0;i<18;i++)
	{
		crc = crc - data[i];
	}

	return ((crc&0x00FF) == data[18]) && ((crc >> 8) == data[19]);
}

void PMIC_2_SRIC_Parsing(unsigned char* data, Struct_PMIC_2_SRIC* pm2sr)
{
	pm2sr->channel_0 = (unsigned char)(data[2]) & 0xFF;
	pm2sr->channel_1 = (unsigned char)(data[3]) & 0xFF;
	pm2sr->channel_2 = (unsigned char)(data[4]) & 0xFF;
	pm2sr->channel_3 = (unsigned char)(data[5]) & 0xFF;
	pm2sr->channel_4 = (unsigned char)(data[6]) & 0xFF;
	pm2sr->channel_5 = (unsigned char)(data[7]) & 0xFF;
	pm2sr->channel_6 = (unsigned char)(data[8]) & 0xFF;
	pm2sr->channel_7 = (unsigned char)(data[8]) & 0xFF;
	pm2sr->channel_8 = (unsigned char)(data[10]) & 0xFF;
	pm2sr->channel_9 = (unsigned char)(data[11]) & 0xFF;
	pm2sr->channel_a = (unsigned char)(data[12]) & 0xFF;
	pm2sr->channel_b = (unsigned char)(data[13]) & 0xFF;
	pm2sr->channel_c = (unsigned char)(data[14]) & 0xFF;
	pm2sr->channel_d = (unsigned char)(data[15]) & 0xFF;
	pm2sr->channel_e = (unsigned char)(data[16]) & 0xFF;
	pm2sr->channel_f = (unsigned char)(data[17]) & 0xFF;
}

void PMIC_SRIC_USART2_Initialization(void)
{

}

unsigned char OBC_2_SRIC_Check_CHKSUM(unsigned char* data)
{
	unsigned short crc = 0xFFFF;

	for(int i=0;i<18;i++)
	{
		crc = crc - data[i];
	}

	return ((crc&0x00FF) == data[18]) && ((crc >> 8) == data[19]);
}


void OBC_2_SRIC_Parsing(unsigned char* data, Struct_OBC_2_SRIC* obc2sr)
{
	obc2sr->channel_0 = (unsigned char)(data[2]) & 0xFF;
	obc2sr->channel_1 = (unsigned char)(data[3]) & 0xFF;
	obc2sr->channel_2 = (unsigned char)(data[4]) & 0xFF;
	obc2sr->channel_3 = (unsigned char)(data[5]) & 0xFF;
	obc2sr->channel_4 = (unsigned char)(data[6]) & 0xFF;
	obc2sr->channel_5 = (unsigned char)(data[7]) & 0xFF;
	obc2sr->channel_6 = (unsigned char)(data[8]) & 0xFF;
	obc2sr->channel_7 = (unsigned char)(data[8]) & 0xFF;
	obc2sr->channel_8 = (unsigned char)(data[10]) & 0xFF;
	obc2sr->channel_9 = (unsigned char)(data[11]) & 0xFF;
	obc2sr->channel_a = (unsigned char)(data[12]) & 0xFF;
	obc2sr->channel_b = (unsigned char)(data[13]) & 0xFF;
	obc2sr->channel_c = (unsigned char)(data[14]) & 0xFF;
	obc2sr->channel_d = (unsigned char)(data[15]) & 0xFF;
	obc2sr->channel_e = (unsigned char)(data[16]) & 0xFF;
	obc2sr->channel_f = (unsigned char)(data[17]) & 0xFF;
}

void OBC_SRIC_USART3_Initialization(void)
{

}



void SRIC_CONFIG_SAT_POWER(Struct_OBC_2_SRIC* obc2sr, Struct_PMIC_2_SRIC* pm2sr){

	/* EN 3V3 1 ------------------------------------------------------------------*/
	if( (obc2sr->channel_0 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_3V3_1_BUCK_SR_GPIO_Port, EN_3V3_1_BUCK_SR_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_3V3_1_BUCK_SR_GPIO_Port, EN_3V3_1_BUCK_SR_Pin);
	if( (obc2sr->channel_1 & 0x01) == 0x01 )
	{
		LL_GPIO_SetOutputPin(EN_3V3_1_BUCK_SR_GPIO_Port, EN_3V3_1_BUCK_SR_Pin);
		LL_GPIO_SetOutputPin(EN_3V3_1_SR_GPIO_Port, EN_3V3_1_SR_Pin);
	}
	else
		LL_GPIO_ResetOutputPin(EN_3V3_1_SR_GPIO_Port, EN_3V3_1_SR_Pin);


	/* EN 3V3 2 ------------------------------------------------------------------*/
	if( (obc2sr->channel_2 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_3V3_2_BUCK_SR_GPIO_Port, EN_3V3_2_BUCK_SR_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_3V3_2_BUCK_SR_GPIO_Port, EN_3V3_2_BUCK_SR_Pin);

	if( (obc2sr->channel_3 & 0x01) == 0x01 )
	{
		LL_GPIO_SetOutputPin(EN_3V3_2_BUCK_SR_GPIO_Port, EN_3V3_2_BUCK_SR_Pin);
		LL_GPIO_SetOutputPin(EN_3V3_2_SR_GPIO_Port, EN_3V3_2_SR_Pin);
	}
	else
		LL_GPIO_ResetOutputPin(EN_3V3_2_SR_GPIO_Port, EN_3V3_2_SR_Pin);


	/* EN 5V0 --------------------------------------------------------------------*/
	if( (obc2sr->channel_4 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_5V_BOOST_SR_GPIO_Port, EN_5V_BOOST_SR_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_5V_BOOST_SR_GPIO_Port, EN_5V_BOOST_SR_Pin);

	if( (obc2sr->channel_5 & 0x01) == 0x01 )
	{
		LL_GPIO_SetOutputPin(EN_5V_BOOST_SR_GPIO_Port, EN_5V_BOOST_SR_Pin);
		LL_GPIO_SetOutputPin(EN_5V_SR_GPIO_Port, EN_5V_SR_Pin);
	}
	else
		LL_GPIO_ResetOutputPin(EN_5V_SR_GPIO_Port, EN_5V_SR_Pin);


	/* EN UNREG 1 ----------------------------------------------------------------*/
	if( (obc2sr->channel_6 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_UNREG1_SR_GPIO_Port, EN_UNREG1_SR_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_UNREG1_SR_GPIO_Port, EN_UNREG1_SR_Pin);

	/* EN UNREG 2 ----------------------------------------------------------------*/
	if( (obc2sr->channel_7 & 0x01) == 0x01 )
		LL_GPIO_SetOutputPin(EN_UNREG2_SR_GPIO_Port, EN_UNREG2_SR_Pin);
	else
		LL_GPIO_ResetOutputPin(EN_UNREG2_SR_GPIO_Port, EN_UNREG2_SR_Pin);


	/* MCU OBC -------------------------------------------------------------------*/
	if( (obc2sr->channel_8 & 0x01) == 0x01 ){
		LL_GPIO_SetOutputPin(EN_MCU_BUCK_SR_GPIO_Port, EN_MCU_BUCK_SR_Pin);
	}
	else
		LL_GPIO_ResetOutputPin(EN_MCU_BUCK_SR_GPIO_Port, EN_MCU_BUCK_SR_Pin);
	if( (obc2sr->channel_9 & 0x01) == 0x01 )
	{
		LL_GPIO_SetOutputPin(EN_MCU_BUCK_SR_GPIO_Port, EN_MCU_BUCK_SR_Pin);
		LL_GPIO_SetOutputPin(EN_MCU_3V3_SR_GPIO_Port, EN_MCU_3V3_SR_Pin);
	}
	else{
		LL_GPIO_ResetOutputPin(EN_MCU_3V3_SR_GPIO_Port, EN_MCU_3V3_SR_Pin);
	}


	/* nEN_EPS_3V3_SR  -----------------------------------------------------------*/
	if( (obc2sr->channel_a & 0x01) == 0x01 ||  (pm2sr->channel_0 & 0x01) == 0x01 )
		LL_GPIO_ResetOutputPin(nEN_EPS_3V3_SR_GPIO_Port, nEN_EPS_3V3_SR_Pin);
	else
		LL_GPIO_SetOutputPin(nEN_EPS_3V3_SR_GPIO_Port, nEN_EPS_3V3_SR_Pin);

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
