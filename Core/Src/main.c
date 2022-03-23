/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim8;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM8_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */
uint8_t YY[10];
uint8_t YY1[]={0XBA,0XEC,0XC9,0XAB};//R
uint8_t YY2[]={0XC0,0XB6,0XC9,0XAB};//B
uint8_t YY3[]={0XC2,0XCC,0XC9,0XAB};//G
uint8_t  A0[]={ 0xFF,0x09,0x00,0x00,0x00};
uint8_t  A1[]={ 0xFF,0x09,0x00,0x01,0x00};
uint8_t  A2[]={ 0xFF,0x09,0x00,0x02,0x00};
uint8_t  A3[]={ 0xFF,0x09,0x00,0x03,0x00};
uint8_t  A4[]={ 0xFF,0x09,0x00,0x04,0x00};
uint8_t  A5[]={ 0xFF,0x09,0x00,0x05,0x00};
uint8_t  A6[]={ 0xFF,0x09,0x00,0x06,0x00};
uint8_t  A7[]={ 0xFF,0x09,0x00,0x07,0x00};
uint8_t  A8[]={ 0xFF,0x09,0x00,0x08,0x00};
uint8_t  A9[]={ 0xFF,0x09,0x00,0x09,0x00};
uint8_t A10[]={ 0xFF,0x09,0x00,0x0a,0x00};
uint8_t A11[]={ 0xFF,0x09,0x00,0x0b,0x00};
uint8_t A12[]={ 0xFF,0x09,0x00,0x0c,0x00};
uint8_t A13[]={ 0xFF,0x09,0x00,0x0d,0x00};
uint8_t A14[]={ 0xFF,0x09,0x00,0x0e,0x00};
uint8_t A15[]={ 0xFF,0x09,0x00,0x0f,0x00};
int X=0;
int i=1;
int FLAG=0;
int FLAGX=1;
int SUMX=0;
int SUMY=0;
int STEP=1;
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
 void MOVE(int a)
{
	if(a==1)//直行
	{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,25);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,00);

		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,20);
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,00);

		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,20);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,00);

		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,25);
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,00);
		FLAG=1;
			}

	if(a==2)//R
		{
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,28);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,00);

			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,00);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,21);

			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,20);
			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,00);

			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,00);
			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,28);
			FLAG=2;
				}
}
void STOP(int a)
{

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,100);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,100);

	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,100);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,100);

	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,100);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,100);

	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,100);
	__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,100);
	HAL_Delay(a);

}
void SHUX(void)
{
	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==1&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==1&&FLAGX==0&&FLAG==2)
		{
			FLAGX=1;
			SUMY++;
		}

	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==1&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==1&&FLAGX==0&&FLAG==1)
		{
			FLAGX=1;
			SUMX++;
		}


	if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==0&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==0&&FLAG==2)
		{
			FLAGX=0;
		}

	if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==0&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==0&&FLAG==2)
		{
			FLAGX=0;
		}
}
void TR90(int flag)
{
if(flag==1)
		{
		   FLAG=5;
		   if(i<=2)
		   	{
			   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,26);
			   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,00);

			   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,00);
			   __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,24);

			   __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,00);
			   __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,24);

			   __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,26);
			   __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,00);
		   	}
			 if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==0&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==0&&X==0)
				  {
					  X=1;
				  }

				  if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14)==1&&HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_5)==1&&X==1)
				  {
					  i=3;

					  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,00);
					  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,23);

					  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,20);
					  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,00);

					  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,00);
					  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,20);

					  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,23);
					  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,00);
					  X=2;
				  }
					  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==1&&X==2)
					  {
					  MOVE(1);
					  i=1;
					  X=0;
					  STEP++;
					  }

		}
}
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
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM8_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */

    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim8,TIM_CHANNEL_4);
    HAL_UART_Receive_IT(&huart1,YY,1000);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


//	       HAL_UART_Transmit(&huart2,YY1,sizeof(YY1),1000);
//	       HAL_Delay(2000);


	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,26);
	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,00);

	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,00);
	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,24);

	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,00);
	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,24);

	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,26);
	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,00);
	 	 HAL_Delay(2000);
	 	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,100);
	 	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,100);

	 	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,100);
	 	 __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,100);

	 	 __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,100);
	 	 __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,100);

	 	 __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,100);
	 	 __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,100);
	 	 HAL_Delay(500);



/*
	          __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,0);
	 	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,0);

	 	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,0);
	 	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,0);

	 	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,0);
	 	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,0);

	 	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,0);
	 	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,0);
	      if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==1&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==0)
	      {
	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,30);
	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,0);

	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,30);
	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,0);

	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,00);
	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,0);

	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,00);
	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,0);
//	 	  HAL_Delay(2000);
	      }

	      if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==0&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==1)
	      	      {
	      	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,00);
	      	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,00);

	      	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,00);
	      	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,00);

	      	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,30);
	      	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,00);

	      	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,30);
	      	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,00);
//	      	 	  HAL_Delay(2000);
	      	      }

	      if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==1&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==1)
	     	      {
	     	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,30);
	     	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,0);

	     	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,30);
	     	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,0);

	     	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,30);
	     	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,0);

	     	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,30);
	     	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,0);
//	     	 	  HAL_Delay(2000);
	     	      }

	      if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_11)==0&&HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_10)==0)
	    	      	      {
	    	      	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1,00);
	    	      	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2,00);

	    	      	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3,00);
	    	      	 	  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4,00);

	    	      	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_1,00);
	    	      	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_2,00);

	    	      	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3,00);
	    	      	 	  __HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_4,00);
//	    	      	 	  HAL_Delay(2000);
	    	      	      }
	    	      	      */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);
  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV1;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_USART1;
  PeriphClkInitStruct.Usart234578ClockSelection = RCC_USART234578CLKSOURCE_D2PCLK1;
  PeriphClkInitStruct.Usart16ClockSelection = RCC_USART16CLKSOURCE_D2PCLK2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 31;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 99;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM8 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM8_Init(void)
{

  /* USER CODE BEGIN TIM8_Init 0 */

  /* USER CODE END TIM8_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM8_Init 1 */

  /* USER CODE END TIM8_Init 1 */
  htim8.Instance = TIM8;
  htim8.Init.Prescaler = 63;
  htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim8.Init.Period = 99;
  htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim8.Init.RepetitionCounter = 0;
  htim8.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim8, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim8, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM8_Init 2 */

  /* USER CODE END TIM8_Init 2 */
  HAL_TIM_MspPostInit(&htim8);

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

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart1, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart1, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
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

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
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

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart3.Init.ClockPrescaler = UART_PRESCALER_DIV1;
  huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetTxFifoThreshold(&huart3, UART_TXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_SetRxFifoThreshold(&huart3, UART_RXFIFO_THRESHOLD_1_8) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_UARTEx_DisableFifoMode(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin : PE5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PB10 PB11 */
  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
