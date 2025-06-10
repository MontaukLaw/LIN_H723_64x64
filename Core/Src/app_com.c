#include "user_comm.h"

volatile uint8_t points_data_usb_tx[FRAME_LEN] = {0};
volatile uint8_t time_to_send_data_through_usb = 0;
volatile uint8_t usb_tx_busy = 0; // USB发送忙标志

extern USBD_HandleTypeDef hUsbDeviceHS;

uint8_t usb_ready(void)
{
    return (hUsbDeviceHS.dev_state == USBD_STATE_CONFIGURED);
}

void usb_send_data(void)
{
    if (g_device_state == 0)
    {
        return; // 如果USB没有连接, 则不执行任务
    }

    if (time_to_send_data_through_usb == 0)
    {
        return; // 如果没有准备好发送数据, 则不执行
    }

    HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_SET);
    // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin); // 测试用, 置位GPIO
    CDC_Transmit_HS(points_data_usb_tx, 1000);
    delay_ms(2);
    time_to_send_data_through_usb = 0; // 重置发送标志

    return;
}

void usb_task(void)
{

    // if (!usb_ready())
    //     return;

    if (usb_tx_busy)
        return;

    if (g_device_state == 0)
    {
        return; // 如果USB没有连接, 则不执行任务
    }
    HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_SET);
    // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin); // 测试用, 置位GPIO
    CDC_Transmit_HS(points_data_usb_tx, FRAME_LEN);
    usb_tx_busy = 1;

    delay_ms(20);

    // delay_ms(8);
}

