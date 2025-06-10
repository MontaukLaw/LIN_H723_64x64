#include "user_comm.h"

__attribute__((section("dma_buffer"), aligned(32)))
uint8_t tx_buf[100] = {0};

__attribute__((section("dma_buffer"), aligned(32))) // 用于存储点数据, 保存在CPU可以访问的区域
volatile uint8_t points_data[FRAME_LEN] = {0};

__attribute__((section("dma_buffer"), aligned(32))) // uint8_t adc_dma_buffer[1000] = {0};
uint8_t adc_dma_buffer[ADC_BUFFER_SIZE] = {0};      // 现在大小是以 word 为单位

volatile uint8_t counter = 0;

volatile uint8_t adc_val = 0;
// volatile uint8_t ready_to_send_data = 0;
volatile uint8_t time_to_change_adc_ch = 0;
volatile uint8_t adc_busy = 0; // ADC是否忙碌

volatile uint16_t point_idx = 0;
volatile uint16_t input_ch = 0;
volatile uint16_t adc_ch = 0;

volatile uint8_t uart_busy = 0; // UART是否忙碌

void init_frame_tail(void)
{

    // 初始化帧尾
    points_data[TOTAL_POINTS] = 0xAA;     // 帧尾第一个字节
    points_data[TOTAL_POINTS + 1] = 0x55; // 帧尾第二个字节
    points_data[TOTAL_POINTS + 2] = 0x03; // 帧尾第三个字节
    points_data[TOTAL_POINTS + 3] = 0x99; // 帧尾第四个字节
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

static void close_all_adc_ch(void)
{
    HAL_GPIO_WritePin(HC4067_EN_1_GPIO_Port, HC4067_EN_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(HC4067_EN_2_GPIO_Port, HC4067_EN_2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(HC4067_EN_3_GPIO_Port, HC4067_EN_3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(HC4067_EN_4_GPIO_Port, HC4067_EN_4_Pin, GPIO_PIN_SET);
}

static void set_adc_ch(void)
{
    close_all_adc_ch();

    uint16_t adc_ch_idx = adc_ch % 16;

    if (adc_ch < 16)
    {
        HAL_GPIO_WritePin(HC4067_EN_1_GPIO_Port, HC4067_EN_1_Pin, GPIO_PIN_RESET);
        // HC4067_S0_1_GPIO_Port
        HAL_GPIO_WritePin(HC4067_S0_1_GPIO_Port, HC4067_S0_1_Pin, (adc_ch_idx & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S1_1_GPIO_Port, HC4067_S1_1_Pin, (adc_ch_idx & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S2_1_GPIO_Port, HC4067_S2_1_Pin, (adc_ch_idx & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S3_1_GPIO_Port, HC4067_S3_1_Pin, (adc_ch_idx & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if (adc_ch < 32)
    {
        HAL_GPIO_WritePin(HC4067_EN_2_GPIO_Port, HC4067_EN_2_Pin, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(HC4067_S0_2_GPIO_Port, HC4067_S0_2_Pin, (adc_ch_idx & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S1_2_GPIO_Port, HC4067_S1_2_Pin, (adc_ch_idx & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S2_2_GPIO_Port, HC4067_S2_2_Pin, (adc_ch_idx & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S3_2_GPIO_Port, HC4067_S3_2_Pin, (adc_ch_idx & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if (adc_ch < 48)
    {
        HAL_GPIO_WritePin(HC4067_EN_3_GPIO_Port, HC4067_EN_3_Pin, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(HC4067_S0_3_GPIO_Port, HC4067_S0_3_Pin, (adc_ch_idx & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S1_3_GPIO_Port, HC4067_S1_3_Pin, (adc_ch_idx & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S2_3_GPIO_Port, HC4067_S2_3_Pin, (adc_ch_idx & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S3_3_GPIO_Port, HC4067_S3_3_Pin, (adc_ch_idx & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
    else if (adc_ch < 64)
    {
        HAL_GPIO_WritePin(HC4067_EN_4_GPIO_Port, HC4067_EN_4_Pin, GPIO_PIN_RESET);

        HAL_GPIO_WritePin(HC4067_S0_4_GPIO_Port, HC4067_S0_4_Pin, (adc_ch_idx & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S1_4_GPIO_Port, HC4067_S1_4_Pin, (adc_ch_idx & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S2_4_GPIO_Port, HC4067_S2_4_Pin, (adc_ch_idx & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(HC4067_S3_4_GPIO_Port, HC4067_S3_4_Pin, (adc_ch_idx & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}

// 切换adc通道
static void change_adc_ch(void)
{
    if (time_to_change_adc_ch == 0)
    {
        return;
    }

    // 切换adc通道
    set_adc_ch();

    adc_ch++;
    if (adc_ch >= ADC_CHANNEL_NUMBER)
    {
        adc_ch = 0;
    }

    time_to_change_adc_ch = 0;
}

static void turn_on_input_ch(void)
{

    // static uint16_t last_ch = 0;

    // 关闭上一个通道
    // set_channel_pin(last_ch, GPIO_PIN_RESET);

    // 打开下一个通道
    set_channel_pin(input_ch, GPIO_PIN_SET);

    // last_ch = input_ch;
}

void main_task_update(void)
{
    static uint8_t test_counter = 0;

    memset(points_data, 0, TOTAL_POINTS);
    test_counter++;
    points_data[0] = test_counter;                          // 将第一个点设置为测试计数器
    HAL_UART_Transmit_DMA(&huart1, points_data, FRAME_LEN); // 发送点数据
    // uart_busy = 1;
    // HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_SET);

    delay_ms(100);
}

// 切换数据索引
static void change_point_idx(void)
{
    point_idx++;
    static uint8_t test_counter = 0;
    if (point_idx >= TOTAL_POINTS)
    {
        // test_counter++;
        // points_data[0] = test_counter;                          // 将第一个点设置为测试计数器
        HAL_UART_Transmit_DMA(&huart1, points_data, FRAME_LEN); // 发送点数据
        uart_busy = 1;
        
        // CDC_Transmit_HS(points_data, FRAME_LEN);
        // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin); // 切换测试端口
        // HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_SET);

        // delay_ms(10);

        point_idx = 0;
    }
}

// 切换输入通道
// 因为输入切换比较容易, 改gpio就行.
static void change_input_ch(void)
{
    input_ch++;
    if (input_ch >= INPUT_CH_NUMBER)
    {
        input_ch = 0;
        time_to_change_adc_ch = 1;
    }
}

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

    // tx_buf[0] = adc_sum / ADC_BUFFER_SIZE; // 计算平均值
    points_data[point_idx] = adc_sum / ADC_BUFFER_SIZE;
}

// void send_data_to_uart(void)
// {
//     if (ready_to_send_data == 0)
//     {
//         return;
//     }

//     // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);
//     HAL_UART_Transmit_DMA(&huart1, points_data, TOTAL_POINTS); // 发送点数据
//     HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_SET);

//     ready_to_send_data = 0;
// }

void main_task_adc(void)
{
    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, ADC_BUFFER_SIZE) != HAL_OK)
    {
        // 启动DMA失败
        Error_Handler();
    }

    adc_busy = 1;
    while (adc_busy)
        ;
}

void main_task(void)
{

    if (uart_busy)
    {
        return;
    }
    
    set_channel_pin(input_ch, GPIO_PIN_SET);
    
    // 切换输入通道
    // turn_on_input_ch();

    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, ADC_BUFFER_SIZE) != HAL_OK)
    {
        // 启动DMA失败
        Error_Handler();
    }

    adc_busy = 1;
    while (adc_busy)
        ;

    // 关闭Input
    set_channel_pin(input_ch, GPIO_PIN_RESET);

    // HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_SET);

    adc_data_handler();

    // HAL_UART_Transmit_DMA(&huart1, tx_buf, 1); // 发送ADC平均值

    // delay_ms(100);

    // 修改输入通道索引
    change_input_ch();

    change_adc_ch();

    change_point_idx();

    // send_data_to_uart();
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc->Instance == ADC1)
    {
        // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);
        adc_busy = 0;
        // HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_RESET);
        // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);
        // HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);
        // odr = TEST_PORT_GPIO_Port->ODR;
        // TEST_PORT_GPIO_Port->BSRR = ((odr & TEST_PORT_Pin) << 16) | (~odr & TEST_PORT_Pin);
    }
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    if (huart->Instance == USART1)
    {
        HAL_GPIO_TogglePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin);

        // HAL_GPIO_WritePin(TEST_PORT_GPIO_Port, TEST_PORT_Pin, GPIO_PIN_RESET);

        uart_busy = 0; // UART发送完成
    }
}

void main_task_single_ch(void)
{

    // 打开下一个通道
    set_channel_pin(input_ch, GPIO_PIN_SET);
}

void main_task_only_ch0(void)
{
    uint8_t ch = 2;
    HAL_GPIO_WritePin(HC4067_S0_1_GPIO_Port, HC4067_S0_1_Pin, (ch & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(HC4067_S1_1_GPIO_Port, HC4067_S1_1_Pin, (ch & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(HC4067_S2_1_GPIO_Port, HC4067_S2_1_Pin, (ch & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(HC4067_S3_1_GPIO_Port, HC4067_S3_1_Pin, (ch & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    // 打开第一个HC4067开关
    HAL_GPIO_WritePin(HC4067_EN_1_GPIO_Port, HC4067_EN_1_Pin, GPIO_PIN_RESET);
    // HAL_GPIO_WritePin(CH0_GPIO_Port, CH0_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(CH6_GPIO_Port, CH6_Pin, GPIO_PIN_SET);

    if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_dma_buffer, ADC_BUFFER_SIZE) != HAL_OK)
    {
        // 启动DMA失败
        Error_Handler();
    }

    adc_busy = 1;
    while (adc_busy)
        ;
    // delay_us(1);

    // 设置第一个HC4067开关的通道
    // HC4067_S0_1_GPIO_Port

    HAL_GPIO_WritePin(HC4067_EN_1_GPIO_Port, HC4067_EN_1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(CH6_GPIO_Port, CH6_Pin, GPIO_PIN_RESET);

    // 简单计算平均值
    uint32_t adc_sum = 0;
    for (uint32_t i = 0; i < ADC_BUFFER_SIZE; i++)
    {
        adc_sum += adc_dma_buffer[i];
    }

    memset(points_data, 0, TOTAL_POINTS);
    // tx_buf[0] = adc_sum / ADC_BUFFER_SIZE; // 计算平均值
    points_data[0] = adc_sum / ADC_BUFFER_SIZE;

    // static uint8_t test_counter = 0;

    // test_counter++;
    // points_data[0] = test_counter;                          // 将第一个点设置为测试计数器
    HAL_UART_Transmit_DMA(&huart1, points_data, FRAME_LEN); // 发送点数据

    delay_ms(100); // 延时100ms
    delay_us(1);   // 延时10us
}