#include "user_comm.h"

__attribute__((section("dma_buffer"), aligned(32)))
uint8_t tx_buf[100] = {0};

__attribute__((section("dma_buffer"), aligned(32))) // 用于存储点数据, 保存在CPU可以访问的区域
volatile uint8_t points_data[TOTAL_POINTS] = {0};

__attribute__((section("dma_buffer"), aligned(32))) // uint8_t adc_dma_buffer[1000] = {0};
uint8_t adc_dma_buffer[ADC_BUFFER_SIZE] = {0};      // 现在大小是以 word 为单位

volatile uint8_t counter = 0;

volatile uint8_t adc_val = 0;
volatile uint8_t read_to_send_data = 0;

static void switch_chs(void);

void uart_test(void)
{
    counter++;
    tx_buf[0] = counter;
    HAL_UART_Transmit_DMA(&huart1, tx_buf, 6);
    delay_ms(100);
}

void adc_data_handler(void)
{
    // 简单计算平均值

    uint32_t adc_sum = 0;
    for (uint32_t i = 0; i < ADC_BUFFER_SIZE; i++)
    {
        adc_sum += adc_dma_buffer[i];
    }

    tx_buf[0] = adc_sum / ADC_BUFFER_SIZE; // 计算平均值
}

void main_task(void)
{
    // 切换通道
    switch_chs();

    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, ADC_BUFFER_SIZE) != HAL_OK)
    {
        // 启动DMA失败
        Error_Handler();
    }

    // HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_SET);

    adc_data_handler();

    if (read_to_send_data)
    {
        HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);
        read_to_send_data = 0;
    }
    // HAL_UART_Transmit_DMA(&huart1, tx_buf, 1); // 发送ADC平均值

    // delay_ms(100);
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);
        // adc_busy = 0;
        // HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_RESET);
        // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);
        // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);
        // odr = TEST_PORT_GPIO_Port->ODR;
        // TEST_PORT_GPIO_Port->BSRR = ((odr & TEST_PORT_Pin) << 16) | (~odr & TEST_PORT_Pin);
    }
}

const GPIO_Channel channels[64] = {
    CH_DEF(0), CH_DEF(1), CH_DEF(2), CH_DEF(3), CH_DEF(4), CH_DEF(5), CH_DEF(6), CH_DEF(7),
    CH_DEF(8), CH_DEF(9), CH_DEF(10), CH_DEF(11), CH_DEF(12), CH_DEF(13), CH_DEF(14), CH_DEF(15),
    CH_DEF(16), CH_DEF(17), CH_DEF(18), CH_DEF(19), CH_DEF(20), CH_DEF(21), CH_DEF(22), CH_DEF(23),
    CH_DEF(24), CH_DEF(25), CH_DEF(26), CH_DEF(27), CH_DEF(28), CH_DEF(29), CH_DEF(30), CH_DEF(31),
    CH_DEF(32), CH_DEF(33), CH_DEF(34), CH_DEF(35), CH_DEF(36), CH_DEF(37), CH_DEF(38), CH_DEF(39),
    CH_DEF(40), CH_DEF(41), CH_DEF(42), CH_DEF(43), CH_DEF(44), CH_DEF(45), CH_DEF(46), CH_DEF(47),
    CH_DEF(48), CH_DEF(49), CH_DEF(50), CH_DEF(51), CH_DEF(52), CH_DEF(53), CH_DEF(54), CH_DEF(55),
    CH_DEF(56), CH_DEF(57), CH_DEF(58), CH_DEF(59), CH_DEF(60), CH_DEF(61), CH_DEF(62), CH_DEF(63)};

void set_channel_pin(uint8_t ch, GPIO_PinState pin_status)
{
    if (ch < sizeof(channels) / sizeof(channels[0]))
    {
        HAL_GPIO_WritePin(channels[ch].port, channels[ch].pin, pin_status);
    }
}

void turn_on_ch(uint16_t ch)
{

    static uint16_t last_ch = 0;

    // 关闭上一个通道
    set_channel_pin(last_ch, GPIO_PIN_RESET);

    // 打开下一个通道
    set_channel_pin(ch, GPIO_PIN_SET);

    last_ch = ch;
}

static void switch_chs(void)
{
    static uint16_t ch = 0;

    turn_on_ch(ch);

    ch++;
    if (ch >= INPUT_CH_NUMBER)
    {
        ch = 0;
        read_to_send_data = 1;
    }
}
