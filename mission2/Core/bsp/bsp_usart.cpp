#include "bsp_usart.h"


Struct_UART_Manage_Object UART1_Manage_Object = {0};


// UART通信发送缓冲区
uint8_t UART1_Tx_Data[256];




/**
 * @brief 初始化UART
 *
 * @param huart UART编号
 * @param Rx_Buffer 接收缓冲区
 * @param Rx_Buffer_Size 接收缓冲区长度
 * @param Callback_Function 处理回调函数
 */
void Uart_Init(UART_HandleTypeDef *huart, uint8_t *Rx_Buffer, uint16_t Rx_Buffer_Size, UART_Call_Back Callback_Function)
{
    if (huart->Instance == USART1)
    {
        UART1_Manage_Object.Rx_Buffer = Rx_Buffer;
        UART1_Manage_Object.Rx_Buffer_Size = Rx_Buffer_Size;
        UART1_Manage_Object.UART_Handler = huart;
        UART1_Manage_Object.Callback_Function = Callback_Function;
    }
    HAL_UARTEx_ReceiveToIdle_DMA(huart, Rx_Buffer, Rx_Buffer_Size);
    //让usart进入准备阶段，允许下一次接收 有个标志位认为他收完了 
    //数据都在Rx_Buffer
}

volatile uint8_t uart1_send_done = 1;

/**
 * @brief 发送数据帧
 *
 * @param huart UART编号
 * @param Data 被发送的数据指针
 * @param Length 长度
 */
uint8_t UART_Send_Data(UART_HandleTypeDef *huart, uint8_t *Data, uint16_t Length)
{
    HAL_UART_Transmit_DMA(huart, Data, Length);
}

/**
 * @brief HAL库UART接收DMA空闲中断
 *
 * @param huart UART编号
 * @param Size 长度
 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    //选择回调函数
    if (huart->Instance == USART1)
    {
        UART1_Manage_Object.Callback_Function(UART1_Manage_Object.Rx_Buffer, UART1_Manage_Object.Rx_Buffer_Size);
        HAL_UARTEx_ReceiveToIdle_DMA(huart, UART1_Manage_Object.Rx_Buffer, UART1_Manage_Object.Rx_Buffer_Size);
        //重新进入准备
    }
}


