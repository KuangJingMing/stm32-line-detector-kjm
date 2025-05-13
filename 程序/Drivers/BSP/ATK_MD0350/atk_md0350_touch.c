/**
 ****************************************************************************************************
 * @file        atk_md0350_touch.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2022-06-21
 * @brief       ATK-MD0350模块触摸驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 F407电机开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./BSP/ATK_MD0350/atk_md0350_touch.h"

#if (ATK_MD0350_USING_TOUCH != 0)

#include "./BSP/ATK_MD0350/atk_md0350_touch_spi.h"
#include "./BSP/ATK_MD0350/atk_md0350_touch_iic.h"
#include <stdlib.h>
#include "./SYSTEM/delay/delay.h"
#include <string.h>

/*****************************************电阻屏**********************************************/

/* 获取X/Y坐标ADC值的命令 */
#define ATK_MD0350_TOUCH_CMD_X  0xD0
#define ATK_MD0350_TOUCH_CMD_Y  0x90

/* ATK-MD0350模块触摸状态数据结构体 */
static struct
{
    struct
    {
        float x;
        float y;
    } fac;          /* 校准比例因子 */
    struct
    {
        uint16_t x;
        uint16_t y;
    } center;       /* 中心坐标的ADC值 */
} g_atk_md0350_touch_sta = {0};

/**
 * @brief       ATK-MD0350模块触摸硬件初始化
 * @param       无
 * @retval      无
 */
static void atk_md0350_rtp_touch_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能时钟 */
    ATK_MD0350_TOUCH_PEN_GPIO_CLK_ENABLE();
    
    /* 初始化PEN引脚 */
    gpio_init_struct.Pin    = ATK_MD0350_TOUCH_PEN_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_TOUCH_PEN_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       获取ATK-MD0350模块触摸的X/Y轴ADC值
 * @note        连续读取ATK_MD0350_TOUCH_READ_TIMES次，
 *              并丢弃最大最小值各ATK_MD0350_TOUCH_READ_DISCARD个，
 *              最后返回剩余的均值
 * @param       cmd: ATK_MD0350_TOUCH_CMD_X: 获取X轴的ADC值（LCD显示内容未旋转）
 *                   ATK_MD0350_TOUCH_CMD_Y: 获取Y轴的ADC值（LCD显示内容未旋转）
 * @retval      获取到的触摸ADC值
 */
static uint16_t atk_md0350_touch_get_adc(uint8_t cmd)
{
    uint16_t dat[ATK_MD0350_TOUCH_READ_TIMES];
    uint8_t dat_index;
    uint8_t dat_index2;
    uint16_t dat_tmp;
    uint16_t dat_sum = 0;
    
    for (dat_index=0; dat_index<ATK_MD0350_TOUCH_READ_TIMES; dat_index++)
    {
        dat[dat_index] = atk_md0350_touch_spi_read(cmd);
    }
    
    for (dat_index=0; dat_index<(ATK_MD0350_TOUCH_READ_TIMES-1); dat_index++)
    {
        for (dat_index2=(dat_index+1); dat_index2<ATK_MD0350_TOUCH_READ_TIMES; dat_index2++)
        {
            if (dat[dat_index] > dat[dat_index2])
            {
                dat_tmp = dat[dat_index];
                dat[dat_index] = dat[dat_index2];
                dat[dat_index2] = dat_tmp;
            }
        }
    }
    
    for (dat_index=ATK_MD0350_TOUCH_READ_DISCARD; dat_index<(ATK_MD0350_TOUCH_READ_TIMES-ATK_MD0350_TOUCH_READ_DISCARD); dat_index++)
    {
        dat_sum += dat[dat_index];
    }
    
    return (dat_sum / (ATK_MD0350_TOUCH_READ_TIMES - (ATK_MD0350_TOUCH_READ_DISCARD << 1)));
}

/**
 * @brief       获取ATK-MD0350模块触摸的X/Y轴ADC值
 * @note        连续读取两次，直至两次读取的插值小于ATK_MD0350_TOUCH_READ_RANGE，
 *              后返回均值
 * @param       cmd: ATK_MD0350_TOUCH_CMD_X: 获取X轴的ADC值（LCD显示内容未旋转）
 *                   ATK_MD0350_TOUCH_CMD_Y: 获取Y轴的ADC值（LCD显示内容未旋转）
 * @retval      获取到的触摸ADC值
 */
static uint16_t atk_md0350_touch_get_adc2(uint8_t cmd)
{
    uint16_t dat1;
    uint16_t dat2;
    uint16_t delta;
    
    do {
        dat1 = atk_md0350_touch_get_adc(cmd);
        dat2 = atk_md0350_touch_get_adc(cmd);
        if (dat1 > dat2)
        {
            delta = dat1 - dat2;
        }
        else
        {
            delta = dat2 - dat1;
        }
    } while (delta > ATK_MD0350_TOUCH_READ_RANGE);
    
    return ((dat1 + dat2) >> 1);
}

/**
 * @brief       绘画ATK-MD0350模块触摸校准触摸点
 * @param       x    : 待画校准触摸点的X坐标
 *              y    : 待画校准触摸点的Y坐标
 *              color: 待画校准触摸点的颜色
 * @retval      无
 */
static void atk_md0350_touch_draw_touch_point(uint16_t x, uint16_t y, uint16_t color)
{
    atk_md0350_draw_line(x - 12, y, x + 13, y, color);
    atk_md0350_draw_line(x, y - 12, x, y + 13, color);
    atk_md0350_draw_point(x + 1, y + 1, color);
    atk_md0350_draw_point(x - 1, y + 1, color);
    atk_md0350_draw_point(x + 1, y - 1, color);
    atk_md0350_draw_point(x - 1, y - 1, color);
    atk_md0350_draw_circle(x, y, 6, color);
}

/**
 * @brief       ATK-MD0350模块触摸校准
 * @param       无
 * @retval      无
 */
static void atk_md0350_touch_calibration(void)
{
    struct
    {
        uint16_t x;
        uint16_t y;
    } point[5];
    uint8_t point_index;
    int16_t d1, d2, d3, d4;
    double x_fac, y_fac;
    
    atk_md0350_clear(ATK_MD0350_WHITE);
    atk_md0350_show_string( 40,
                            40,
                            ATK_MD0350_LCD_WIDTH - 80,
                            ATK_MD0350_LCD_HEIGHT - 80,
                            "Please use the stylus click the cross on the screen.The cross will always move until the screen adjustment is completed.",
                            ATK_MD0350_LCD_FONT_16,
                            ATK_MD0350_RED);
    
    while (1)
    {
        for (point_index=0; point_index<5 + 1; point_index++)
        {
            switch (point_index)
            {
                case 0:
                {
                    atk_md0350_touch_draw_touch_point(atk_md0350_get_lcd_width() >> 1, atk_md0350_get_lcd_height() >> 1, ATK_MD0350_WHITE);
                    atk_md0350_touch_draw_touch_point(20, 20, ATK_MD0350_RED);
                    break;
                }
                case 1:
                {
                    atk_md0350_touch_draw_touch_point(20, 20, ATK_MD0350_WHITE);
                    atk_md0350_touch_draw_touch_point(atk_md0350_get_lcd_width() - 20, 20, ATK_MD0350_RED);
                    break;
                }
                case 2:
                {
                    atk_md0350_touch_draw_touch_point(atk_md0350_get_lcd_width() - 20, 20, ATK_MD0350_WHITE);
                    atk_md0350_touch_draw_touch_point(20, atk_md0350_get_lcd_height() - 20, ATK_MD0350_RED);
                    break;
                }
                case 3:
                {
                    atk_md0350_touch_draw_touch_point(20, atk_md0350_get_lcd_height() - 20, ATK_MD0350_WHITE);
                    atk_md0350_touch_draw_touch_point(atk_md0350_get_lcd_width() - 20, atk_md0350_get_lcd_height() - 20, ATK_MD0350_RED);
                    break;
                }
                case 4:
                {
                    atk_md0350_touch_draw_touch_point(atk_md0350_get_lcd_width() - 20, atk_md0350_get_lcd_height() - 20, ATK_MD0350_WHITE);
                    atk_md0350_touch_draw_touch_point(atk_md0350_get_lcd_width() >> 1, atk_md0350_get_lcd_height() >> 1, ATK_MD0350_RED);
                    break;
                }
                case 5:
                {
                    d1 = point[1].x - point[0].x;
                    d3 = point[3].x - point[2].x;
                    d2 = point[3].y - point[1].y;
                    d4 = point[2].y - point[0].y;
                    
                    x_fac = (double)d1 / d3;
                    y_fac = (double)d2 / d4;
                    
                    if (x_fac < 0)
                    {
                        x_fac = -x_fac;
                    }
                    if (y_fac < 0)
                    {
                        y_fac = -y_fac;
                    }
                    
                    if (    x_fac < 0.95 || x_fac > 1.05 || y_fac < 0.95 || y_fac > 1.05 ||
                            abs(d1) > 4095 || abs(d2) > 4095 || abs(d3) > 4095 || abs(d4) > 4095 ||
                            abs(d1) == 0 || abs(d2) == 0 || abs(d3) == 0 || abs(d4) == 0)
                    {
                        break;
                    }
                    
                    g_atk_md0350_touch_sta.fac.x = (float)(d1 + d3) / ((atk_md0350_get_lcd_width() - 40) << 1);
                    g_atk_md0350_touch_sta.fac.y = (float)(d2 + d4) / ((atk_md0350_get_lcd_height() - 40) << 1);
                    
                    g_atk_md0350_touch_sta.center.x = point[4].x;
                    g_atk_md0350_touch_sta.center.y = point[4].y;
                    
                    atk_md0350_clear(ATK_MD0350_WHITE);
                    atk_md0350_show_string( 68,
                                            100,
                                            atk_md0350_get_lcd_width(),
                                            atk_md0350_get_lcd_height(),
                                            "Touch Screen Adjust OK!",
                                            ATK_MD0350_LCD_FONT_16,
                                            ATK_MD0350_BLUE);
                    delay_ms(1000);
                    atk_md0350_clear(ATK_MD0350_WHITE);
                    
                    return;
                }
            }
            delay_ms(200);
            while (ATK_MD0350_TOUCH_READ_PEN() != 0);
            point[point_index].x = atk_md0350_touch_get_adc2(ATK_MD0350_TOUCH_CMD_X);
            point[point_index].y = atk_md0350_touch_get_adc2(ATK_MD0350_TOUCH_CMD_Y);
            while (ATK_MD0350_TOUCH_READ_PEN() == 0);
        }
    }
}

/**
 * @brief       ATK-MD0350模块触摸扫描
 * @param       x: 扫描到触摸的X坐标
 *              y: 扫描到触摸的Y坐标
 * @retval      ATK_MD0350_TOUCH_EOK  : 扫描到有效的触摸
 *              ATK_MD0350_TOUCH_ERROR: 触摸坐标无效
 *              ATK_MD0350_TOUCH_EMPTY: 未扫描到有效的触摸
 */
uint8_t atk_md0350_rtp_touch_scan(uint16_t *x, uint16_t *y)
{
    uint16_t x_adc;
    uint16_t y_adc;
    atk_md0350_lcd_disp_dir_t dir;
    uint16_t x_raw;
    uint16_t y_raw;
    
    if (ATK_MD0350_TOUCH_READ_PEN() == 0)
    {
        x_adc = atk_md0350_touch_get_adc2(ATK_MD0350_TOUCH_CMD_X);
        y_adc = atk_md0350_touch_get_adc2(ATK_MD0350_TOUCH_CMD_Y);
        
        x_raw = (int16_t)(x_adc - g_atk_md0350_touch_sta.center.x) / g_atk_md0350_touch_sta.fac.x + ATK_MD0350_LCD_WIDTH / 2;
        y_raw = (int16_t)(y_adc - g_atk_md0350_touch_sta.center.y) / g_atk_md0350_touch_sta.fac.y + ATK_MD0350_LCD_HEIGHT / 2;
        
        if((x_raw >= ATK_MD0350_LCD_WIDTH) || (y_raw >= ATK_MD0350_LCD_HEIGHT))
        {
            return ATK_MD0350_TOUCH_ERROR;
        }
        
        dir = atk_md0350_get_disp_dir();
        switch (dir)
        {
            case ATK_MD0350_LCD_DISP_DIR_0:
            {
                *x = x_raw;
                *y = y_raw;
                break;
            }
            case ATK_MD0350_LCD_DISP_DIR_90:
            {
                *x = y_raw;
                *y = atk_md0350_get_lcd_height() - x_raw;
                break;
            }
            case ATK_MD0350_LCD_DISP_DIR_180:
            {
                *x = atk_md0350_get_lcd_width() - x_raw;
                *y = atk_md0350_get_lcd_height() - y_raw;
                break;
            }
            case ATK_MD0350_LCD_DISP_DIR_270:
            {
                *x = atk_md0350_get_lcd_width() - y_raw;
                *y = x_raw;
                break;
            }
        }
        
        return ATK_MD0350_TOUCH_EOK;
    }
    
    return ATK_MD0350_TOUCH_EMPTY;
}

/*****************************************电容屏**********************************************/
/* ATK-MD0350模块触摸的PID */
#define ATK_MD0350_TOUCH_PID                "1158"

/* ATK-MD0350模块最大触摸点数量 */
#define ATK_MD0350_TOUCH_TP_MAX             5

/* ATK-MD0350模块触摸部分寄存器定义 */
#define ATK_MD0350_TOUCH_REG_CTRL           0x8040  /* 控制寄存器 */
#define ATK_MD0350_TOUCH_REG_PID            0x8140  /* PID寄存器 */
#define ATK_MD0350_TOUCH_REG_TPINFO         0x814E  /* 触摸状态寄存器 */
#define ATK_MD0350_TOUCH_REG_TP1            0x8150  /* 触摸点1数据寄存器 */
#define ATK_MD0350_TOUCH_REG_TP2            0x8158  /* 触摸点2数据寄存器 */
#define ATK_MD0350_TOUCH_REG_TP3            0x8160  /* 触摸点3数据寄存器 */
#define ATK_MD0350_TOUCH_REG_TP4            0x8168  /* 触摸点4数据寄存器 */
#define ATK_MD0350_TOUCH_REG_TP5            0x8170  /* 触摸点5数据寄存器 */

/* 触摸状态寄存器掩码 */
#define ATK_MD0350_TOUCH_TPINFO_MASK_STA    0x80
#define ATK_MD0350_TOUCH_TPINFO_MASK_CNT    0x0F

/* ATK-MD0350模块触摸点数据寄存器 */
static const uint16_t g_atk_md0350_touch_tp_reg[ATK_MD0350_TOUCH_TP_MAX] = {
    ATK_MD0350_TOUCH_REG_TP1,
    ATK_MD0350_TOUCH_REG_TP2,
    ATK_MD0350_TOUCH_REG_TP3,
    ATK_MD0350_TOUCH_REG_TP4,
    ATK_MD0350_TOUCH_REG_TP5,
};

/**
 * @brief       ATK-MD0350模块触摸硬件初始化
 * @param       无
 * @retval      无
 */
static void atk_md0350_ctp_touch_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能时钟 */
    ATK_MD0350_TOUCH_PEN_GPIO_CLK_ENABLE();
    ATK_MD0350_TOUCH_TCS_GPIO_CLK_ENABLE();
    
    /* 初始化PEN引脚 */
    gpio_init_struct.Pin    = ATK_MD0350_TOUCH_PEN_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_NOPULL;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_TOUCH_PEN_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化TCS引脚 */
    gpio_init_struct.Pin    = ATK_MD0350_TOUCH_TCS_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_TOUCH_TCS_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       ATK-MD0350模块触摸硬件复位
 * @param       addr: 复位后使用的IIC通讯地址
 * @retval      无
 */
static void atk_md0350_touch_hw_reset(atk_md0350_touch_iic_addr_t addr)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 配置PEN引脚为输出 */
    gpio_init_struct.Pin    = ATK_MD0350_TOUCH_PEN_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;
    gpio_init_struct.Pull   = GPIO_PULLUP;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_TOUCH_PEN_GPIO_PORT, &gpio_init_struct);
    
    switch (addr)
    {
        case ATK_MD0350_TOUCH_IIC_ADDR_14:
        {
            ATK_MD0350_TOUCH_TCS(0);
            ATK_MD0350_TOUCH_PEN(0);
            ATK_MD0350_TOUCH_PEN(1);
            delay_ms(1);
            ATK_MD0350_TOUCH_TCS(1);
            delay_ms(10);
            break;
        }
        case ATK_MD0350_TOUCH_IIC_ADDR_5D:
        {
            ATK_MD0350_TOUCH_TCS(0);
            ATK_MD0350_TOUCH_PEN(0);
            delay_ms(1);
            ATK_MD0350_TOUCH_TCS(1);
            delay_ms(10);
            break;
        }
        default:
        {
            break;
        }
    }
    
    /* 重新配置PEN引脚为输入 */
    gpio_init_struct.Pin    = ATK_MD0350_TOUCH_PEN_GPIO_PIN;
    gpio_init_struct.Mode   = GPIO_MODE_INPUT;
    gpio_init_struct.Pull   = GPIO_NOPULL;
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(ATK_MD0350_TOUCH_PEN_GPIO_PORT, &gpio_init_struct);
}

/**
 * @brief       ATK-MD0350模块触摸软件复位
 * @param       无
 * @retval      无
 */
static void atk_md0350_touch_sw_reset(void)
{
    uint8_t dat;
    
    dat = 0x02;
    atk_md0350_touch_iic_write_reg(ATK_MD0350_TOUCH_REG_CTRL, &dat, 1);
    delay_ms(10);
    
    dat = 0x00;
    atk_md0350_touch_iic_write_reg(ATK_MD0350_TOUCH_REG_CTRL, &dat, 1);
}

/**
 * @brief       获取ATK-MD0350模块触摸的PID
 * @param       pid: 获取到的PID（ASCII）
 * @retval      无
 */
static void atk_md0350_touch_get_pid(char *pid)
{
    atk_md0350_touch_iic_read_reg(ATK_MD0350_TOUCH_REG_PID, (uint8_t *)pid, 4);
    pid[4] = '\0';
}

/**
 * @brief       ATK-MD0350模块触摸扫描
 * @note        连续调用间隔需大于10ms
 * @param       point: 扫描到的触摸点信息
 *              cnt  : 需要扫描的触摸点数量（1~ATK_MD0350_TOUCH_TP_MAX）
 * @retval      0   : 没有扫描到触摸点
 *              其他: 实际获取到的触摸点信息数量
 */
uint8_t atk_md0350_ctp_touch_scan(atk_md0350_touch_point_t *point, uint8_t cnt)
{
    uint8_t tp_info;
    uint8_t tp_cnt;
    uint8_t point_index;
    atk_md0350_lcd_disp_dir_t dir;
    uint8_t tpn_info[6];
    atk_md0350_touch_point_t point_raw;
    
    if ((cnt == 0) || (cnt > ATK_MD0350_TOUCH_TP_MAX))
    {
        return 0;
    }
    
    for (point_index=0; point_index<cnt; point_index++)
    {
        if (&point[point_index] == NULL)
        {
            return 0;
        }
    }
    
    atk_md0350_touch_iic_read_reg(ATK_MD0350_TOUCH_REG_TPINFO, &tp_info, sizeof(tp_info));
    if ((tp_info & ATK_MD0350_TOUCH_TPINFO_MASK_STA) == ATK_MD0350_TOUCH_TPINFO_MASK_STA)
    {
        tp_cnt = tp_info & ATK_MD0350_TOUCH_TPINFO_MASK_CNT;
        tp_cnt = (cnt < tp_cnt) ? cnt : tp_cnt;
        
        for (point_index=0; point_index<tp_cnt; point_index++)
        {
            atk_md0350_touch_iic_read_reg(g_atk_md0350_touch_tp_reg[point_index], tpn_info, sizeof(tpn_info));
            point_raw.x = (uint16_t)(tpn_info[1] << 8) | tpn_info[0];
            point_raw.y = (uint16_t)(tpn_info[3] << 8) | tpn_info[2];
            point_raw.size = (uint16_t)(tpn_info[5] << 8) | tpn_info[4];
            
            dir = atk_md0350_get_disp_dir();
            switch (dir)
            {
                case ATK_MD0350_LCD_DISP_DIR_0:
                {
                    point[point_index].x = point_raw.x;
                    point[point_index].y = point_raw.y;
                    break;
                }
                case ATK_MD0350_LCD_DISP_DIR_90:
                {
                    point[point_index].x = point_raw.y;
                    point[point_index].y = atk_md0350_get_lcd_height() - point_raw.x;
                    break;
                }
                case ATK_MD0350_LCD_DISP_DIR_180:
                {
                    point[point_index].x = atk_md0350_get_lcd_width() - point_raw.x;
                    point[point_index].y = atk_md0350_get_lcd_height() - point_raw.y;
                    break;
                }
                case ATK_MD0350_LCD_DISP_DIR_270:
                {
                    point[point_index].x = atk_md0350_get_lcd_width() - point_raw.y;
                    point[point_index].y = point_raw.x;
                    break;
                }
            }
            
            point[point_index].size = point_raw.size;
        }
        
        tp_info = 0;
        atk_md0350_touch_iic_write_reg(ATK_MD0350_TOUCH_REG_TPINFO, &tp_info, sizeof(tp_info));
        
        return tp_cnt;
    }
    else
    {
        return 0;
    }
}
/******************************************************************************************/

/**
 * @brief       ATK-MD0350模块触摸初始化
 * @param       无
 * @retval      0:电阻屏；1:电容屏
 */
uint8_t atk_md0350_touch_init(void)
{
    char pid[5];

    atk_md0350_ctp_touch_hw_init();
    atk_md0350_touch_hw_reset(ATK_MD0350_TOUCH_IIC_ADDR_14);
    atk_md0350_touch_iic_init(ATK_MD0350_TOUCH_IIC_ADDR_14);
    delay_ms(100);
    atk_md0350_touch_get_pid(pid);

    if (strcmp(pid, ATK_MD0350_TOUCH_PID) != 0)     /* 若读取到的非1158,该触摸屏为电阻触摸屏 */
    {
        atk_md0350_rtp_touch_hw_init();
        atk_md0350_touch_spi_init();
        atk_md0350_touch_calibration();
        return 0;   /* 电阻屏 */
    }
    atk_md0350_touch_sw_reset();

    return 1;       /* 电容屏 */
}



#endif /* ATK_MD0350_USING_TOUCH */
