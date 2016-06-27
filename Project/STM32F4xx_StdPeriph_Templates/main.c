/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.7.1
  * @date    20-May-2016
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/** @addtogroup Template_Project
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static __IO uint32_t uwTimingDelay;
RCC_ClocksTypeDef RCC_Clocks;

/* Private function prototypes -----------------------------------------------*/
static void Delay(__IO uint32_t nTime);

/* Private functions ---------------------------------------------------------*/
uint8_t SPI2_Send(uint8_t data)
{
	SPI2->DR = data;
	while( !(SPI2->SR & SPI_I2S_FLAG_TXE) );
	while( !(SPI2->SR & SPI_I2S_FLAG_RXNE) );
	while( SPI2->SR & SPI_I2S_FLAG_BSY );
	return SPI2->DR;
}


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
 
	SPI_InitTypeDef SPI_InitStructure;
	
	
	uint8_t recieved_val = 0;
	
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       files before to branch to application main.
       To reconfigure the default setting of SystemInit() function, 
       refer to system_stm32f4xx.c file */

  /* SysTick end of count event each 10ms */
  RCC_GetClocksFreq(&RCC_Clocks);
  SysTick_Config(RCC_Clocks.HCLK_Frequency / 100);
  
  /* Add your application code here */
  /* Insert 50 ms delay */
  Delay(5);
	
	
	
	
  /* Output HSE clock on MCO1 pin(PA8) ****************************************/ 
  /* Enable the GPIOA peripheral */ 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  
  /* Configure MCO1 pin(PA8) in alternate function */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
//  /* HSE clock selected to output on MCO1 pin(PA8)*/
//  RCC_MCO1Config(RCC_MCO1Source_HSE, RCC_MCO1Div_1);
  
  
  /* Output SYSCLK/4 clock on MCO2 pin(PC9) ***********************************/ 
  /* Enable the GPIOACperipheral */ 
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
//  
//  /* Configure MCO2 pin(PC9) in alternate function */
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//    
//  /* SYSCLK/4 clock selected to output on MCO2 pin(PC9)*/
//  RCC_MCO2Config(RCC_MCO2Source_SYSCLK, RCC_MCO2Div_4);
  
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4 ;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
//	SPI1_InitStructure.SPI_CRCPolynomial = 
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
	
	GPIO_Init(GPIOI, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource1, GPIO_AF_SPI2);
	GPIO_PinAFConfig(GPIOI, GPIO_PinSource3, GPIO_AF_SPI2);
  
	SPI_Init(SPI1, &SPI_InitStructure);
	SPI_Init(SPI2, &SPI_InitStructure);
	
	SPI_Cmd(SPI2, ENABLE);

		 
  /* Infinite loop */
  while (1)
  {
//		SPI2_Send(0XAA);
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  uwTimingDelay = nTime;

  while(uwTimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (uwTimingDelay != 0x00)
  { 
    uwTimingDelay--;
  }
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
