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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_ADC_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t  flagDMATC = 0;
uint16_t adcVal[10];
uint16_t regmap[16];
uint8_t  spi_rx_data = 0;
uint8_t  spi_tx_data = 0;
//int __io_putchar (int ch)
//{
//  while (!LL_USART_IsActiveFlag_TXE(USARTx));
//  LL_USART_TransmitData8(USARTx, (char)ch);
//  return ch;
//}
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

	/* SysTick_IRQn interrupt configuration */
	NVIC_SetPriority(SysTick_IRQn, 3);

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
	MX_GPIO_Init();
	MX_DMA_Init();
	MX_ADC_Init();
	MX_SPI1_Init();
	/* USER CODE BEGIN 2 */

	// configure DMA source & target
	LL_DMA_ConfigAddresses(DMA1,
			LL_DMA_CHANNEL_1,
			LL_ADC_DMA_GetRegAddr(ADC1, LL_ADC_DMA_REG_REGULAR_DATA),
			(uint32_t)adcVal,
			LL_DMA_DIRECTION_PERIPH_TO_MEMORY);
	// configure DMA length
	LL_DMA_SetDataLength(DMA1, LL_DMA_CHANNEL_1, 10);
	// enable DMA stream
	LL_DMA_EnableChannel(DMA1, LL_DMA_CHANNEL_1);
	// enable ADC
	LL_ADC_Enable(ADC1);
	// start conversion
	LL_ADC_REG_StartConversion(ADC1);

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	while (1)
	{
		while(!flagDMATC);
		// clear flag
		flagDMATC = 0;

		int16_t sum_psd1 = adcVal[1]+adcVal[3]+adcVal[2]+adcVal[0];
		int16_t a1 = (int16_t)(adcVal[3]+adcVal[2]) - (int16_t)(adcVal[1]+adcVal[0]);
		int16_t b1 = (int16_t)(adcVal[3]+adcVal[0]) - (int16_t)(adcVal[1]+adcVal[2]);
		int16_t position_x_psd1 = a1/sum_psd1;
		int16_t position_y_psd1 = b1/sum_psd1;
		int16_t intensity_psd1 = sum_psd1;


		int16_t sum_psd2 = adcVal[5]+adcVal[7]+adcVal[6]+adcVal[4];
		int16_t a2 = (int16_t)(adcVal[7]+adcVal[6]) - (int16_t)(adcVal[5]+adcVal[4]);
		int16_t b2 = (int16_t)(adcVal[7]+adcVal[4]) - (int16_t)(adcVal[5]+adcVal[6]);
		int16_t position_x_psd2 = a2/sum_psd2;
		int16_t position_y_psd2 = b2/sum_psd2;
		int16_t intensity_psd2 = sum_psd2;


		//	    // convert to temperature & Vdd
		//	    float temp = (float)adcVal[8] * 3.3f / 4096.0f;
		//	    temp = (temp - 0.76) / 0.0025 + 25;
		//
		//	    // Vdd = 3.3V * Vrefint_cal / Vrefint
		//	    float Vdd = 3.3f * (*VREFINT_CAL_ADDR) / (float)adcVal[9];

		// print results
		//	    printf("psd1 x1: %d, psd1 x2: %d, psd1 y1: %d, psd1 y2: %d,"
		//	    	   "psd2 x1: %d, psd2 x2: %d, psd2 y1: %d, psd2 y2: %d,"
		//	    	   " TEMP: %2.1f, Vdd: %1.2f\r\n",
		//			   adcVal[1],adcVal[3],adcVal[2],adcVal[0],
		//			   adcVal[5],adcVal[7],adcVal[6],adcVal[4], temp, Vdd);

		for(uint16_t i=0;i<10;i++){
			regmap[i] = adcVal[i];
		}
		regmap[10]=position_x_psd1;
		regmap[11]=position_y_psd1;
		regmap[12]=intensity_psd1;
		regmap[13]=position_x_psd2;
		regmap[14]=position_y_psd2;
		regmap[15]=intensity_psd2;
		//	    regmap[16]=temp;
		//	    regmap[17]=Vdd;


		if(LL_GPIO_IsInputPinSet(NCS_GPIO_Port, NCS_Pin) == 0){

			while (!LL_SPI_IsActiveFlag_RXNE(SPI1));
			spi_rx_data = LL_SPI_ReceiveData8(SPI1);

			uint8_t spi_tx_high_byte = ((regmap)[spi_rx_data] >> 8) & 0xFF;
			uint8_t spi_tx_low_byte  =  (regmap)[spi_rx_data] & 0xFF;

			while (!LL_SPI_IsActiveFlag_TXE(SPI1));
			LL_SPI_TransmitData8(SPI1, spi_tx_high_byte);
			while (!LL_SPI_IsActiveFlag_TXE(SPI1));
			LL_SPI_TransmitData8(SPI1, spi_tx_low_byte);
		}



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
	LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
	while(LL_FLASH_GetLatency()!= LL_FLASH_LATENCY_0)
	{
	}
	LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
	while (LL_PWR_IsActiveFlag_VOS() != 0)
	{
	}
	LL_RCC_HSI_Enable();

	/* Wait till HSI is ready */
	while(LL_RCC_HSI_IsReady() != 1)
	{

	}
	LL_RCC_HSI_SetCalibTrimming(16);
	LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
	LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
	LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
	LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSI);

	/* Wait till System clock is ready */
	while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSI)
	{

	}

	LL_Init1msTick(16000000);

	LL_SetSystemCoreClock(16000000);
}

/**
 * @brief ADC Initialization Function
 * @param None
 * @retval None
 */
static void MX_ADC_Init(void)
{

	/* USER CODE BEGIN ADC_Init 0 */

	/* USER CODE END ADC_Init 0 */

	LL_ADC_REG_InitTypeDef ADC_REG_InitStruct = {0};
	LL_ADC_InitTypeDef ADC_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	/**ADC GPIO Configuration
  PA0-CK_IN   ------> ADC_IN0
  PA1   ------> ADC_IN1
  PA2   ------> ADC_IN2
  PA3   ------> ADC_IN3
  PA4   ------> ADC_IN4
  PA5   ------> ADC_IN5
  PA6   ------> ADC_IN6
  PA7   ------> ADC_IN7
	 */
	GPIO_InitStruct.Pin = Y2_PSD1_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(Y2_PSD1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = X1_PSD1_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(X1_PSD1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = Y1_PSD1_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(Y1_PSD1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = X2_PSD1_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(X2_PSD1_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = Y2_PSD2_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(Y2_PSD2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = X1_PSD2_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(X1_PSD2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = Y1_PSD2_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(Y1_PSD2_GPIO_Port, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = X2_PSD2_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(X2_PSD2_GPIO_Port, &GPIO_InitStruct);

	/* ADC DMA Init */

	/* ADC Init */
	LL_DMA_SetPeriphRequest(DMA1, LL_DMA_CHANNEL_1, LL_DMA_REQUEST_0);

	LL_DMA_SetDataTransferDirection(DMA1, LL_DMA_CHANNEL_1, LL_DMA_DIRECTION_PERIPH_TO_MEMORY);

	LL_DMA_SetChannelPriorityLevel(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PRIORITY_VERYHIGH);

	LL_DMA_SetMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MODE_CIRCULAR);

	LL_DMA_SetPeriphIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PERIPH_NOINCREMENT);

	LL_DMA_SetMemoryIncMode(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MEMORY_INCREMENT);

	LL_DMA_SetPeriphSize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_PDATAALIGN_HALFWORD);

	LL_DMA_SetMemorySize(DMA1, LL_DMA_CHANNEL_1, LL_DMA_MDATAALIGN_HALFWORD);

	/* USER CODE BEGIN ADC_Init 1 */

	/* USER CODE END ADC_Init 1 */

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_0);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_1);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_2);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_3);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_4);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_5);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_6);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_7);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_TEMPSENSOR);
	LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_TEMPSENSOR);

	/** Configure Regular Channel
	 */
	LL_ADC_REG_SetSequencerChAdd(ADC1, LL_ADC_CHANNEL_VREFINT);
	LL_ADC_SetCommonPathInternalCh(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_PATH_INTERNAL_VREFINT);

	/** Common config
	 */
	ADC_REG_InitStruct.TriggerSource = LL_ADC_REG_TRIG_SOFTWARE;
	ADC_REG_InitStruct.SequencerDiscont = LL_ADC_REG_SEQ_DISCONT_DISABLE;
	ADC_REG_InitStruct.ContinuousMode = LL_ADC_REG_CONV_CONTINUOUS;
	ADC_REG_InitStruct.DMATransfer = LL_ADC_REG_DMA_TRANSFER_UNLIMITED;
	ADC_REG_InitStruct.Overrun = LL_ADC_REG_OVR_DATA_PRESERVED;
	LL_ADC_REG_Init(ADC1, &ADC_REG_InitStruct);
	LL_ADC_SetSamplingTimeCommonChannels(ADC1, LL_ADC_SAMPLINGTIME_160CYCLES_5);
	LL_ADC_SetOverSamplingScope(ADC1, LL_ADC_OVS_DISABLE);
	LL_ADC_REG_SetSequencerScanDirection(ADC1, LL_ADC_REG_SEQ_SCAN_DIR_FORWARD);
	LL_ADC_SetCommonFrequencyMode(__LL_ADC_COMMON_INSTANCE(ADC1), LL_ADC_CLOCK_FREQ_MODE_HIGH);
	LL_ADC_DisableIT_EOC(ADC1);
	LL_ADC_DisableIT_EOS(ADC1);
	ADC_InitStruct.Clock = LL_ADC_CLOCK_SYNC_PCLK_DIV1;
	ADC_InitStruct.Resolution = LL_ADC_RESOLUTION_12B;
	ADC_InitStruct.DataAlignment = LL_ADC_DATA_ALIGN_RIGHT;
	ADC_InitStruct.LowPowerMode = LL_ADC_LP_MODE_NONE;
	LL_ADC_Init(ADC1, &ADC_InitStruct);

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
	/* USER CODE BEGIN ADC_Init 2 */

	/* USER CODE END ADC_Init 2 */

}

/**
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void)
{

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	LL_SPI_InitTypeDef SPI_InitStruct = {0};

	LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	/* Peripheral clock enable */
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SPI1);

	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);
	/**SPI1 GPIO Configuration
  PB0   ------> SPI1_MISO
  PB1   ------> SPI1_MOSI
  PB3   ------> SPI1_SCK
	 */
	GPIO_InitStruct.Pin = LL_GPIO_PIN_0;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_1;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_1;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = LL_GPIO_PIN_3;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_ALTERNATE;
	GPIO_InitStruct.Speed = LL_GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.OutputType = LL_GPIO_OUTPUT_PUSHPULL;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	GPIO_InitStruct.Alternate = LL_GPIO_AF_0;
	LL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	SPI_InitStruct.TransferDirection = LL_SPI_FULL_DUPLEX;
	SPI_InitStruct.Mode = LL_SPI_MODE_SLAVE;
	SPI_InitStruct.DataWidth = LL_SPI_DATAWIDTH_8BIT;
	SPI_InitStruct.ClockPolarity = LL_SPI_POLARITY_LOW;
	SPI_InitStruct.ClockPhase = LL_SPI_PHASE_1EDGE;
	SPI_InitStruct.NSS = LL_SPI_NSS_SOFT;
	SPI_InitStruct.BitOrder = LL_SPI_MSB_FIRST;
	SPI_InitStruct.CRCCalculation = LL_SPI_CRCCALCULATION_DISABLE;
	SPI_InitStruct.CRCPoly = 7;
	LL_SPI_Init(SPI1, &SPI_InitStruct);
	LL_SPI_SetStandard(SPI1, LL_SPI_PROTOCOL_MOTOROLA);
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

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
	NVIC_SetPriority(DMA1_Channel1_IRQn, 0);
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
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOA);
	LL_IOP_GRP1_EnableClock(LL_IOP_GRP1_PERIPH_GPIOB);

	/**/
	GPIO_InitStruct.Pin = NCS_Pin;
	GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = LL_GPIO_PULL_NO;
	LL_GPIO_Init(NCS_GPIO_Port, &GPIO_InitStruct);

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
