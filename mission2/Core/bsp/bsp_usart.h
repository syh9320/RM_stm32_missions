#ifndef BSP_USART_H
#define BSP_USART_H
 
#include "stm32f1xx_hal.h"
 


 /**
  * @brief UART通信接收回调函数数据类型
  *
  */
 typedef void (*UART_Call_Back)(uint8_t *Buffer, uint16_t Length);
 

/**
  * @brief UART通信处理结构体
*/
typedef struct 
{
    UART_HandleTypeDef *UART_Handler;
    uint8_t *Rx_Buffer;
    uint16_t Rx_Buffer_Size;
    UART_Call_Back Callback_Function;
}Struct_UART_Manage_Object;
 

extern UART_HandleTypeDef huart1;



extern Struct_UART_Manage_Object UART1_Manage_Object;

 
 
extern uint8_t UART1_Tx_Data[];

 
 
void Uart_Init(UART_HandleTypeDef *huart, uint8_t *Rx_Buffer, uint16_t Rx_Buffer_Size, UART_Call_Back Callback_Function);
 
uint8_t UART_Send_Data(UART_HandleTypeDef *huart, uint8_t *Data, uint16_t Length);
 

#endif