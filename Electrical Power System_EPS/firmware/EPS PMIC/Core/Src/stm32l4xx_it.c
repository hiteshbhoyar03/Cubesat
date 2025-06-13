/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
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
#include "stm32l4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
#define SRIC_2_PMIC_HEADER 					0x0F
#define OBC_2_PMIC_HEADER 					0x0F
#define SRIC_2_PMIC_COMMAND 				0x0F
#define OBC_2_PMIC_COMMAND					0x0F

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
extern uint8_t flagDMATC1;
extern uint8_t flagDMATC3;

uint8_t usart1_rx_flag = 0;		// DEBUG
uint8_t usart1_rx_data = 0;		// DEBUG

uint8_t usart2_rx_flag = 0;		// Uart SRIC-PMIC
uint8_t usart2_rx_data = 0;		// Uart SRIC-PMIC
uint8_t usart3_rx_flag = 0;		// Uart OBC-PMIC
uint8_t usart3_rx_data = 0;		// Uart OBC-PMIC

uint8_t sric_2_pmic_rx_buffer[20];					// SRIC-PMIC BUFFER
uint8_t sric_2_pmic_rx_complete_flag = 0;			// SRIC-PMIC COMPLETE FLAG
uint8_t obc_2_pmic_rx_buffer[20];					// OBC-PMIC BUFFER
uint8_t obc_2_pmic_rx_complete_flag = 0;			// OBC-PMIC COMPLETE FLAG

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel1 global interrupt.
  */
void DMA1_Channel1_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */
	 if ( LL_DMA_IsActiveFlag_TC1(DMA1) )
	  {
	    flagDMATC1 =  1 ;
	    LL_DMA_ClearFlag_TC1( DMA1 ) ;
	  }

  /* USER CODE END DMA1_Channel1_IRQn 0 */
  /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */

  /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel3 global interrupt.
  */
void DMA1_Channel3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel3_IRQn 0 */
	 if ( LL_DMA_IsActiveFlag_TC1(DMA1) )
	  {
	    flagDMATC3 =  1 ;
	    LL_DMA_ClearFlag_TC3( DMA1 ) ;
	  }

  /* USER CODE END DMA1_Channel3_IRQn 0 */
  /* USER CODE BEGIN DMA1_Channel3_IRQn 1 */

  /* USER CODE END DMA1_Channel3_IRQn 1 */
}

/**
  * @brief This function handles USART1 global interrupt.
  */
void USART1_IRQHandler(void)
{
  /* USER CODE BEGIN USART1_IRQn 0 */
	/*--------------------------------------------------------------------------------------------*/
	/* DEBUG -------------------------------------------------------------------------------------*/
	/*--------------------------------------------------------------------------------------------*/
	if(LL_USART_IsActiveFlag_RXNE(USART1))
	{
		usart1_rx_data = LL_USART_ReceiveData8(USART1);
		usart1_rx_flag = 1;
	}

  /* USER CODE END USART1_IRQn 0 */
  /* USER CODE BEGIN USART1_IRQn 1 */

  /* USER CODE END USART1_IRQn 1 */
}

/**
  * @brief This function handles USART2 global interrupt.
  */
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
	/*--------------------------------------------------------------------------------------------*/
	/* SRIC_2_PMIC -------------------------------------------------------------------------------*/
	/*--------------------------------------------------------------------------------------------*/
	static unsigned char cnt = 0;

	if(LL_USART_IsActiveFlag_RXNE(USART3))
	{
		usart3_rx_data = LL_USART_ReceiveData8(USART2);
		usart3_rx_flag = 1;

//		while(!LL_USART_IsActiveFlag_TXE(USART1));
//		LL_USART_TransmitData8(USART1, usart3_rx_data);		// Transmit TO PC

		switch(cnt)
		{
		case 0 :	if(usart2_rx_data == SRIC_2_PMIC_HEADER)
					{obc_2_pmic_rx_buffer[cnt++] = usart2_rx_data;}			break;

		case 1 :	if(usart2_rx_data == SRIC_2_PMIC_COMMAND)
					{obc_2_pmic_rx_buffer[cnt++] = usart2_rx_data;}
					else {cnt = 0;}												break;

		case 19:	obc_2_pmic_rx_buffer[cnt]    = usart2_rx_data;
					cnt=0;
					obc_2_pmic_rx_complete_flag  = 1;							break;

		default:	obc_2_pmic_rx_buffer[cnt++]  = usart2_rx_data;			break;
		}
	}

  /* USER CODE END USART2_IRQn 0 */
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

	/*--------------------------------------------------------------------------------------------*/
	/* OBC_2_PMIC -------------------------------------------------------------------------------*/
	/*--------------------------------------------------------------------------------------------*/
	static unsigned char cnt = 0;

	if(LL_USART_IsActiveFlag_RXNE(USART2))
	{
		usart2_rx_data = LL_USART_ReceiveData8(USART3);
		usart2_rx_flag = 1;

//		while(!LL_USART_IsActiveFlag_TXE(USART1));
//		LL_USART_TransmitData8(USART1, usart2_rx_data);		// Transmit TO PC

		switch(cnt)
		{
		case 0 :	if(usart2_rx_data == OBC_2_PMIC_HEADER)
					{sric_2_pmic_rx_buffer[cnt++] = usart2_rx_data;}			break;

		case 1 :	if(usart2_rx_data == OBC_2_PMIC_COMMAND)
					{sric_2_pmic_rx_buffer[cnt++] = usart2_rx_data;}
					else {cnt = 0;}												break;

		case 19:	sric_2_pmic_rx_buffer[cnt]    = usart2_rx_data;
					cnt=0;
					sric_2_pmic_rx_complete_flag  = 1;							break;

		default:	sric_2_pmic_rx_buffer[cnt++]  = usart2_rx_data;				break;
		}
	}

  /* USER CODE END USART3_IRQn 0 */
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles UART4 global interrupt.
  */
void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */

  /* USER CODE END UART4_IRQn 0 */
  /* USER CODE BEGIN UART4_IRQn 1 */

  /* USER CODE END UART4_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
