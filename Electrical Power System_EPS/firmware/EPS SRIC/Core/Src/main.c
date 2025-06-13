/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2025 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "sric_functions.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
int _write(int file, char* p, int len)
{
	for(int i=0;i<len;i++)
	{
		while(!LL_USART_IsActiveFlag_TXE(USART1));
		LL_USART_TransmitData8(USART1, *(p+i));
	}
	return len;
}

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern uint8_t usart1_rx_flag;					// DEBUG
extern uint8_t usart1_rx_data;					// DEBUG
uint8_t  flagDMATC = 0;							// DMA TRANSFER COMPLETE FLAG
uint16_t adcVal[6];								// ADC

extern uint8_t pmic_2_sric_rx_buffer[20];		// PMIC-SR RX BUFFER
extern uint8_t pmic_2_sric_rx_complete_flag;	// PMIC-SR COMPLETE FLAG
extern uint8_t obc_2_sric_rx_buffer[20];		// OBC-SR RX BUFFER
extern uint8_t obc_2_sric_rx_complete_flag;		// OBC-SR COMPLETE FLAG

uint8_t sric_2_pmic_tx_buffer[20];				// SRIC-PMIC TX BUFFER
uint8_t sric_2_obc_tx_buffer[20];				// SRIC-PMIC TX BUFFER

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void PeriphCommonClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC1_Init(void);
static void MX_RTC_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

	/* System interrupt init*/
	NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

	/* SysTick_IRQn interrupt configuration */
	NVIC_SetPriority(SysTick_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),15, 0));

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* Configure the peripherals common clocks */
	PeriphCommonClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC1_Init();
	MX_RTC_Init();
	MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */

	LL_USART_EnableIT_RXNE(USART1);				// DEBUG
	LL_USART_EnableIT_RXNE(USART2);				// Uart EPS-SR
	LL_USART_EnableIT_RXNE(USART3);				// Uart OBC-SR

	LL_DMA_ConfigAddresses(DMA1,				// DMA ADC
			LL_DMA_CHANNEL_1,
			LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
			(uint32_t)adcVal,
			LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 6);			// configure DMA length
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);				// enable DMA stream
	LL_ADC_Enable(ADC1);										// enable ADC
	LL_ADC_REG_StartConversion(ADC1);							// start conversion


	LL_GPIO_ResetOutputPin(nEN_EPS_3V3_SR_GPIO_Port,nEN_EPS_3V3_SR_Pin); // KEEP EPS ON

	sric_2_pmic_tx_buffer[0]=0xFE;								// HEADER SETUP
	sric_2_pmic_tx_buffer[1]=0X00;
	sric_2_obc_tx_buffer[0]=0xFB;
	sric_2_obc_tx_buffer[1]=0X00;
	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		/* DMA ---------------------------------------------------------------------------------------*/
		while(!flagDMATC);
		// clear flag
		flagDMATC = 0;

		/* UART PMIC_2_SRIC --------------------------------------------------------------------------*/
		if(pmic_2_sric_rx_complete_flag == 1)
		{
			pmic_2_sric_rx_complete_flag = 0;
			if(PMIC_2_SRIC_Check_CHKSUM(&pmic_2_sric_rx_buffer[0]) == 1){
				PMIC_2_SRIC_Parsing(&pmic_2_sric_rx_buffer[0], &pm2sr);
			}
		}

		/* UART OBC_2_SRIC ---------------------------------------------------------------------------*/
		if(obc_2_sric_rx_complete_flag == 1)
		{
			obc_2_sric_rx_complete_flag = 0;
			if(OBC_2_SRIC_Check_CHKSUM(&obc_2_sric_rx_buffer[0]) == 1){
				OBC_2_SRIC_Parsing(&obc_2_sric_rx_buffer[0], &obc2sr);
			}
		}

		/* CONFIGURE SATELLITE POWER -----------------------------------------------------------------*/
		SRIC_CONFIG_SAT_POWER( &obc2sr,  &pm2sr );





		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/
		/* SATELLITE SRIC TASKS HERE -----------------------------------------------------------------*/







		/* SEND DATA SRIC_2_PMIC ---------------------------------------------------------------------*/
		SEND_DATA_UART(&sric_2_pmic_tx_buffer[0], USART2, 20);// CONTAINS CHKSUM GENRATOR
		/* SEND DATA SRIC_2_OBC ----------------------------------------------------------------------*/
		SEND_DATA_UART(&sric_2_obc_tx_buffer[0], USART3, 20);

		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
	}
	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
	while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_3)
	{
	}
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	while (LL_PWR_IsActiveFlag_VOS() != 0)
	{
	}
	LL_RCC_HSE_Enable();

	/* Wait till HSE is ready */
	while(LL_RCC_HSE_IsReady() != 1)
	{

	}
	LL_PWR_EnableBkUpAccess();
	LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);
	LL_RCC_LSE_Enable();

	/* Wait till LSE is ready */
	while(LL_RCC_LSE_IsReady() != 1)
	{

	}
	LL_RCC_HSE_EnableCSS();
	LL_RCC_LSE_EnableCSS();
	LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLR_DIV_2);
	LL_RCC_PLL_EnableDomain_SYS();
	LL_RCC_PLL_Enable();

	/* Wait till PLL is ready */
	while(LL_RCC_PLL_IsReady() != 1)
	{

	}
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);

	/* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL)
	{

	}
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);

	LL_Init1msTick(64000000);

	LL_SetSystemCoreClock(64000000);
}

/**
 * @brief Peripherals Common Clock Configuration
 * @retval None
 */
void PeriphCommonClock_Config(void)
{
	LL_RCC_PLLSAI1_ConfigDomain_ADC(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_1, 8, LL_RCC_PLLSAI1R_DIV_2);
	LL_RCC_PLLSAI1_EnableDomain_ADC();
	LL_RCC_PLLSAI1_Enable();

	/* Wait till PLLSAI1 is ready */
	while(LL_RCC_PLLSAI1_IsReady() != 1)
	{

	}
}

/**
 * @brief ADC1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC1_Init(void)
{

	/* USER CODE BEGIN ADC1_Init 0 */

	/* USER CODE END ADC1_Init 0 */

	LL_ADC_InitTypeDef ADC_InitStruct = {0};
	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
	LL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSOURCE_PLLSAI1);

	/* Peripheral clock enable */
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_ADC);

	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	/**ADC1 GPIO Configuration
  PA0   ------> ADC1_IN5
  PA1   ------> ADC1_IN6
  PA4   ------> ADC1_IN9
  PA5   ------> ADC1_IN10
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_0|LL_GPIO_PIN_1|LL_GPIO_PIN_4|LL_GPIO_PIN_5;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* ADC1 DMA Init */

	/* ADC1 Init */
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMA_REQUEST_0);

	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_MEDIUM);

	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_NORMAL);

	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);

	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);

	/* USER CODE BEGIN ADC1_Init 1 */

	/* USER CODE END ADC1_Init 1 */

	/** Common config
	 */
	ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
	ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
	LL_ADC_Init(ADC1, &ADC_InitStruct);
	ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	ADC_REG_InitStruct.SequencerLength = LL_ADC_REG_SEQ_SCAN_ENABLE_6RANKS;
	ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
	ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
	LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
	LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
	LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_VREFINT|LL_ADC_PATH_INTERNAL_VBAT);
	ADC_CommonInitStruct.CommonClock = LL_ADC_CLOCK_ASYNC_DIV1;
	LL_ADC_CommonInit(__LL_ADC_COMMON_INSTANCE(ADC1), &ADC_CommonInitStruct);

	/* Disable ADC deep power down (enabled by default after reset state) */
	LL_ADC_DisableDeepPowerDown(ADC1);
	/* Enable ADC internal voltage regulator */
	LL_ADC_EnableInternalRegulator(ADC1);
	/* Delay for ADC internal voltage regulator stabilization. */
	/* Compute number of CPU cycles to wait for, from delay in us. */
	/* Note: Variable divided by 2 to compensate partially */
	/* CPU processing cycles (depends on compilation optimization). */
	/* Note: If system core clock frequency is below 200kHz, wait time */
	/* is only a few CPU processing cycles. */
	uint32_t wait_loop_index;
	wait_loop_index = ((LL_ADC_DELAY_INTERNAL_REGUL_STAB_US * (SystemCoreClock / (100000 * 2))) / 10);
	while(wait_loop_index != 0)
	{
		wait_loop_index--;
	}

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_5);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_5, LL_ADC_SAMPLINGTIME_247CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_5, LL_ADC_SINGLE_ENDED);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_2, LL_ADC_CHANNEL_6);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_6, LL_ADC_SAMPLINGTIME_247CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_6, LL_ADC_SINGLE_ENDED);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_3, LL_ADC_CHANNEL_9);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_9, LL_ADC_SAMPLINGTIME_247CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_9, LL_ADC_SINGLE_ENDED);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_4, LL_ADC_CHANNEL_10);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_10, LL_ADC_SAMPLINGTIME_247CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_10, LL_ADC_SINGLE_ENDED);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_5, LL_ADC_CHANNEL_VBAT);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_VBAT, LL_ADC_SAMPLINGTIME_247CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_VBAT, LL_ADC_SINGLE_ENDED);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_6, LL_ADC_CHANNEL_VREFINT);
	LL_ADC_SetChannelSamplingTime(ADC1, LL_ADC_CHANNEL_VREFINT, LL_ADC_SAMPLINGTIME_247CYCLES_5);
	LL_ADC_SetChannelSingleDiff(ADC1, LL_ADC_CHANNEL_VREFINT, LL_ADC_SINGLE_ENDED);
	/* USER CODE BEGIN ADC1_Init 2 */

	/* USER CODE END ADC1_Init 2 */

}

/**
 * @brief RTC Initialization Function
 * @param None
 * @retval None
 */
static void MX_RTC_Init(void)
{

	/* USER CODE BEGIN RTC_Init 0 */

	/* USER CODE END RTC_Init 0 */

	LL_RTC_InitTypeDef RTC_InitStruct = {0};
	LL_RTC_TimeTypeDef RTC_TimeStruct = {0};
	LL_RTC_DateTypeDef RTC_DateStruct = {0};

	if(LL_RCC_GetRTCClockSource() != LL_RCC_RTC_CLKSOURCE_LSE)
	{
		FlagStatus pwrclkchanged = RESET;
		/* Update LSE configuration in Backup Domain control register */
		/* Requires to enable write access to Backup Domain if necessary */
		if (LL_APB1_GRP1_IsEnabledClock (LL_APB1_GRP1_PERIPH_PWR) != 1U)
		{
			/* Enables the PWR Clock and Enables access to the backup domain */
			LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
			pwrclkchanged = SET;
		}
		if (LL_PWR_IsEnabledBkUpAccess () != 1U)
		{
			/* Enable write access to Backup domain */
			LL_PWR_EnableBkUpAccess();
			while (LL_PWR_IsEnabledBkUpAccess () == 0U)
			{
			}
		}
		LL_RCC_ForceBackupDomainReset();
		LL_RCC_ReleaseBackupDomainReset();
		LL_RCC_LSE_SetDriveCapability(LL_RCC_LSEDRIVE_LOW);
		LL_RCC_LSE_Enable();

		/* Wait till LSE is ready */
		while(LL_RCC_LSE_IsReady() != 1)
		{
		}
		LL_RCC_SetRTCClockSource(LL_RCC_RTC_CLKSOURCE_LSE);
		/* Restore clock configuration if changed */
		if (pwrclkchanged == SET)
		{
			LL_APB1_GRP1_DisableClock(LL_APB1_GRP1_PERIPH_PWR);
		}
	}

	/* Peripheral clock enable */
	LL_RCC_EnableRTC();

	/* USER CODE BEGIN RTC_Init 1 */

	/* USER CODE END RTC_Init 1 */

	/** Initialize RTC and set the Time and Date
	 */
	RTC_InitStruct.HourFormat = LL_RTC_HOURFORMAT_24HOUR;
	RTC_InitStruct.AsynchPrescaler = 127;
	RTC_InitStruct.SynchPrescaler = 255;
	LL_RTC_Init(RTC, &RTC_InitStruct);

	/** Initialize RTC and set the Time and Date
	 */
	RTC_TimeStruct.Hours = 0x0;
	RTC_TimeStruct.Minutes = 0x0;
	RTC_TimeStruct.Seconds = 0x0;

	LL_RTC_TIME_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_TimeStruct);
	RTC_DateStruct.WeekDay = LL_RTC_WEEKDAY_THURSDAY;
	RTC_DateStruct.Month = LL_RTC_MONTH_JUNE;
	RTC_DateStruct.Day = 0x12;
	RTC_DateStruct.Year = 0x25;

	LL_RTC_DATE_Init(RTC, LL_RTC_FORMAT_BCD, &RTC_DateStruct);
	/* USER CODE BEGIN RTC_Init 2 */

	/* USER CODE END RTC_Init 2 */

}

/**
 * @brief USART1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART1_UART_Init(void)
{

	/* USER CODE BEGIN USART1_Init 0 */

	/* USER CODE END USART1_Init 0 */

	LL_USART_InitTypeDef USART_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	LL_RCC_SetUSARTClockSource(LL_RCC_USART1_CLKSOURCE_PCLK2);

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);

	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	/**USART1 GPIO Configuration
  PA9   ------> USART1_TX
  PA10   ------> USART1_RX
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_9|LL_GPIO_PIN_10;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART1 interrupt Init */
	NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(USART1_IRQn);

	/* USER CODE BEGIN USART1_Init 1 */

	/* USER CODE END USART1_Init 1 */
	USART_InitStruct.BaudRate = 115200;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART1, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART1);
	LL_USART_Enable(USART1);
	/* USER CODE BEGIN USART1_Init 2 */

	/* USER CODE END USART1_Init 2 */

}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void)
{

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	LL_USART_InitTypeDef USART_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	LL_RCC_SetUSARTClockSource(LL_RCC_USART2_CLKSOURCE_PCLK1);

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);

	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	/**USART2 GPIO Configuration
  PA2   ------> USART2_TX
  PA3   ------> USART2_RX
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_2|LL_GPIO_PIN_3;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/* USART2 interrupt Init */
	NVIC_SetPriority(USART2_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(USART2_IRQn);

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	USART_InitStruct.BaudRate = 115200;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART2, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART2);
	LL_USART_Enable(USART2);
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void)
{

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	LL_USART_InitTypeDef USART_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	LL_RCC_SetUSARTClockSource(LL_RCC_USART3_CLKSOURCE_PCLK1);

	/* Peripheral clock enable */
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);

	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);
	/**USART3 GPIO Configuration
  PB10   ------> USART3_TX
  PB11   ------> USART3_RX
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_10|LL_GPIO_PIN_11;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_7;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USART3 interrupt Init */
	NVIC_SetPriority(USART3_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(USART3_IRQn);

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	USART_InitStruct.BaudRate = 115200;
	USART_InitStruct.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitStruct.StopBits = LL_USART_STOPBITS_1;
	USART_InitStruct.Parity = LL_USART_PARITY_NONE;
	USART_InitStruct.TransferDirection = LL_USART_DIRECTION_TX_RX;
	USART_InitStruct.HardwareFlowControl = LL_USART_HWCONTROL_NONE;
	USART_InitStruct.OverSampling = LL_USART_OVERSAMPLING_16;
	LL_USART_Init(USART3, &USART_InitStruct);
	LL_USART_ConfigAsyncMode(USART3);
	LL_USART_Enable(USART3);
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */

}

/**
 * Enable DMA controller clock
 */
static void MX_DMA_Init(void)
{

	/* Init with LL driver */
	/* DMA controller clock enable */
	LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_DMA1);

	/* DMA interrupt init */
	/* DMA1_Channel1_IRQn interrupt configuration */
	NVIC_SetPriority(DMA1_Channel1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0, 0));
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOC);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOH);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOA);
	LL_AHB2_GRP1_EnableClock(LL_AHB2_GRP1_PERIPH_GPIOB);

	/**/
	LL_GPIO_ResetOutputPin(nEN_EPS_3V3_SR_GPIO_Port, nEN_EPS_3V3_SR_Pin);

	/**/
	LL_GPIO_ResetOutputPin(GPIOA, EN_MCU_BUCK_SR_Pin|EN_MCU_3V3_SR_Pin|EN_5V_SR_Pin|WAKE_SR_Pin
			|DONE_SR_Pin);

	/**/
	LL_GPIO_ResetOutputPin(GPIOB, EN_3V3_2_BUCK_SR_Pin|EN_3V3_2_SR_Pin|EN_UNREG1_SR_Pin|EN_UNREG2_SR_Pin
			|EN_3V3_1_BUCK_SR_Pin|EN_3V3_1_SR_Pin|EN_5V_BOOST_SR_Pin|DEBUG_LED4_SR_Pin
			|DEBUG_LED3_SR_Pin|DEBUG_LED2_SR_Pin|DEBUG_LED1_SR_Pin);

	/**/
	GPIO_InitStruct.Pin = nEN_EPS_3V3_SR_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(nEN_EPS_3V3_SR_GPIO_Port, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = EN_MCU_BUCK_SR_Pin|EN_MCU_3V3_SR_Pin|EN_5V_SR_Pin|WAKE_SR_Pin
			|DONE_SR_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	/**/
	GPIO_InitStruct.Pin = EN_3V3_2_BUCK_SR_Pin|EN_3V3_2_SR_Pin|EN_UNREG1_SR_Pin|EN_UNREG2_SR_Pin
			|EN_3V3_1_BUCK_SR_Pin|EN_3V3_1_SR_Pin|EN_5V_BOOST_SR_Pin|DEBUG_LED4_SR_Pin
			|DEBUG_LED3_SR_Pin|DEBUG_LED2_SR_Pin|DEBUG_LED1_SR_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_OUTPUT;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
