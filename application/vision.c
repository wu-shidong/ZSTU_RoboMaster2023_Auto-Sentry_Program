#include "vision.h"
//#include "bsp_usart.h"
#include "usart.h"
#include <stdlib.h>
#include <string.h>
uint8_t USART1_RX_BUF =0;
uint8_t USART1_RX_CNT =0;
uint8_t USART1_RX_STA =0;
#define USART1_TX_BUF_LENGHT 512
uint8_t usart1_buf[USART1_TX_BUF_LENGHT];
Vision_Data vision_info[2];

void usart1_vision_init (void)
{
	    //enable receive interrupt and idle interrupt
    //使能接收中断和空闲中断
    __HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);  //receive interrupt
//    __HAL_UART_ENABLE_IT(&huart1, UART_IT_IDLE);  //idle interrupt
}
/**
  * @brief   将接收到的字符一位位存进去
  * @param   none
  * @retva   none
  */
void append_vision_arr(uint8_t * vision_info,uint8_t *val,uint8_t offset)
{
    memcpy((void *)(vision_info + offset),(void *)(val),sizeof(uint8_t));
}
/**
  * @brief   清除数据
  * @param   none
  * @retva   none
  */
void clear_vision_data(void *vision_info)
{
    memset((void *)vision_info,0,sizeof(Vision_Data)); 
}
/**
  * @brief   校验是否收完
  * @param   none
  * @retva   none
  */
uint8_t check_vision_data(void * euler_angle_info)
{
    if (USART1_RX_CNT==32)
    {
        return 1;
    }
    else
    {
        return 0;
    }
 
}

void USART1_IRQHandler(void)  
{
  volatile uint8_t receive;
	static Vision_Data vision_temp;
    //receive interrupt 接收中断
    if(huart1.Instance->SR & UART_FLAG_RXNE)
    {
			receive = huart1.Instance->DR;
			USART1_RX_BUF=receive;
			if(USART1_RX_STA==0)
       {
            if(USART1_RX_BUF==0xAA)
            {
                USART1_RX_STA=1; 
                USART1_RX_CNT=0;
                clear_vision_data(&vision_temp);
                append_vision_arr((uint8_t *)&vision_temp,&USART1_RX_BUF,USART1_RX_CNT);
            }
		   }
        else
        {
            USART1_RX_CNT++;
            append_vision_arr((uint8_t *)&vision_temp,&USART1_RX_BUF,USART1_RX_CNT);
        }
        if(check_vision_data(&vision_temp)==1)
        {
            USART1_RX_CNT = 0;
            USART1_RX_STA = 0;
           if(vision_temp.Data_ID==0x01)
            {
                memcpy((void *)(&vision_info[0]),(void *)(&vision_temp),sizeof(Vision_Data));
            }else if(vision_temp.Data_ID==0x02)
            {
                memcpy((void *)(&vision_info[1]),(void *)(&vision_temp),sizeof(Vision_Data));
            }else
            {
                
            }
        }			
    }
    //idle interrupt 空闲中断
//    else if(huart1.Instance->SR & UART_FLAG_IDLE)
//    {
//      receive = huart1.Instance->DR;
//    }

}
