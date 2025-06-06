/**
 ****************************************************************************************************
 * @file        mpu.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2020-03-22
 * @brief       MPU内存保护 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 STM32H750开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20200322
 * 第一次发布
 *
 ****************************************************************************************************
 */

#include "user_comm.h"

/**
 * @brief       禁止MPU保护
 * @param       无
 * @retval      无
 */
void mpu_disable(void)
{
    SCB->SHCSR &= ~(1 << 16); /* 禁止MemManage */
    MPU->CTRL &= ~(1 << 0);   /* 禁止MPU */
}

/**
 * @brief       开启MPU保护
 * @param       无
 * @retval      无
 */
void mpu_enable(void)
{
    MPU->CTRL = (1 << 2) | (1 << 0); /* 使能PRIVDEFENA,使能MPU */
    SCB->SHCSR |= 1 << 16;           /* 使能MemManage */
}

/**
 * @brief       禁止MPU保护
 * @param       nbytes:要转换的数据,字节数
 * @retval      nbytes以2为底的指数值
 */
static uint8_t mpu_convert_bytes_to_pot(uint32_t nbytes)
{
    uint8_t count = 0;

    while (nbytes != 1)
    {
        nbytes >>= 1;
        count++;
    }

    return count;
}

/**
 * @brief       设置某个区域的MPU保护
 * @param       baseaddr: MPU保护区域的基址(首地址)
 * @param       size:MPU保护区域的大小(必须是32的倍数,单位为字节)
 * @param       rnum:MPU保护区编号,范围:0~7,最大支持8个保护区域
 * @param       de:禁止指令访问;0,允许指令访问;1,禁止指令访问
 * @param       ap:访问权限,访问关系如下:
 *   @arg       0,无访问（特权&用户都不可访问）
 *   @arg       1,仅支持特权读写访问
 *   @arg       2,禁止用户写访问（特权可读写访问）
 *   @arg       3,全访问（特权&用户都可访问）
 *   @arg       4,无法预测(禁止设置为4!!!)
 *   @arg       5,仅支持特权读访问
 *   @arg       6,只读（特权&用户都不可以写）
 *   @note      详见:STM32H7编程手册.pdf,4.6.6节,Table 91.
 * @param       sen:是否允许共用;0,不允许;1,允许
 * @param       cen:是否允许cache;0,不允许;1,允许
 * @param       ben:是否允许缓冲;0,不允许;1,允许
 * @retval      0, 成功; 1, 错误;
 */
uint8_t mpu_set_protection(uint32_t baseaddr, uint32_t size, uint32_t rnum, uint8_t de, uint8_t ap, uint8_t sen, uint8_t cen, uint8_t ben)
{
    uint32_t tempreg = 0;
    uint8_t rnr = 0;

    if ((size % 32) || size == 0)
        return 1; /* 大小不是32的倍数,或者size为0,说明参数错误 */

    rnr = mpu_convert_bytes_to_pot(size) - 1; /* 转换为2为底的指数值 */
    mpu_disable();                            /* 设置之前,先禁止MPU保护 */
    MPU->RNR = rnum;                          /* 设置保护区域 */
    MPU->RBAR = baseaddr;                     /* 设置基址 */
    tempreg |= ((uint32_t)de) << 28;          /* 禁止/允许指令访问(禁止/允许读取指令) */
    tempreg |= ((uint32_t)ap) << 24;          /* 设置访问权限, */
    tempreg |= 0 << 19;                       /* 设置类型扩展域为level0 */
    tempreg |= ((uint32_t)sen) << 18;         /* 是否允许共用 */
    tempreg |= ((uint32_t)cen) << 17;         /* 是否允许cache */
    tempreg |= ((uint32_t)ben) << 16;         /* 是否允许缓冲 */
    tempreg |= 0 << 8;                        /* 禁止子区域 */
    tempreg |= rnr << 1;                      /* 设置保护区域大小 */
    tempreg |= 1 << 0;                        /* 使能该保护区域 */
    MPU->RASR = tempreg;                      /* 设置RASR寄存器 */
    mpu_enable();                             /* 设置完毕,使能MPU保护 */
    return 0;
}

/**
 * @brief       设置需要保护的存储块
 *   @note
 *              必须对部分存储区域进行MPU保护,否则可能导致程序运行异常
 *              比如MCU屏不显示,摄像头采集数据出错等等问题...
 *
 * @param       无
 * @retval      nbytes以2为底的指数值
 */
void mpu_memory_protection(void)
{
    /* 保护整个DTCM,共128K字节,允许指令访问,禁止共用,允许cache,允许缓冲 */
    mpu_set_protection(0x20000000, 128 * 1024, 1, 0, MPU_REGION_FULL_ACCESS, 0, 1, 1);

    /* 保护整个AXI SRAM,共512K字节,允许指令访问,禁止共用,允许cache,允许缓冲 */
    mpu_set_protection(0x24000000, 512 * 1024, 2, 0, MPU_REGION_FULL_ACCESS, 0, 1, 1);

    /* 保护整个SRAM1~SRAM3,共288K字节,允许指令访问,禁止共用,允许cache,允许缓冲 */
    mpu_set_protection(0x30000000, 512 * 1024, 3, 0, MPU_REGION_FULL_ACCESS, 0, 1, 1);

    /* 保护整个SRAM4,共64K字节,允许指令访问,禁止共用,允许cache,允许缓冲 */
    mpu_set_protection(0x38000000, 64 * 1024, 4, 0, MPU_REGION_FULL_ACCESS, 0, 1, 1);

    /* 保护MCU LCD屏所在的FMC区域,,共64M字节,允许指令访问,禁止共用,禁止cache,禁止缓冲 */
    mpu_set_protection(0x60000000, 64 * 1024 * 1024, 5, 0, MPU_REGION_FULL_ACCESS, 0, 0, 0);

    /* 保护SDRAM区域,共64M字节,允许指令访问,禁止共用,允许cache,允许缓冲 */
    mpu_set_protection(0XC0000000, 64 * 1024 * 1024, 6, 0, MPU_REGION_FULL_ACCESS, 0, 1, 1);

    /* 保护整个NAND FLASH区域,共256M字节,禁止指令访问,禁止共用,禁止cache,禁止缓冲 */
    mpu_set_protection(0X80000000, 256 * 1024 * 1024, 7, 1, MPU_REGION_FULL_ACCESS, 0, 0, 0);
}

// /**
//  * @brief       MemManage错误处理中断
//  *   @note      进入此中断以后,将无法恢复程序运行!!
//  *
//  * @param       无
//  * @retval      nbytes以2为底的指数值
//  */
// void MemManage_Handler(void)
// {
//     LED1(0);                          /* 点亮LED1(GREEN LED) */
//     printf("Mem Access Error!!\r\n"); /* 输出错误信息 */
//     delay_ms(1000);
//     printf("Soft Reseting...\r\n"); /* 提示软件重启 */
//     delay_ms(1000);
//     sys_soft_reset(); /* 软复位 */
// }
