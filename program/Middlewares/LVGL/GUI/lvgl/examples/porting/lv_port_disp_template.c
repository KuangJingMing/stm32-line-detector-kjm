/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp_template.h"
#include "../../lvgl.h"
#include "./BSP/LCD/lcd.h"
#include "./BSP/LCD/ltdc.h"

extern uint32_t *g_ltdc_framebuf[2];

/*********************
 *      DEFINES
 *********************/
#define MY_DISP_HOR_RES (800)
#define MY_DISP_VER_RES (480)

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * @brief       优化的DMA2D传输到LTDC帧缓冲区
 */
void lcd_dma2d_fast_copy(int16_t sx, int16_t sy, int16_t ex, int16_t ey, lv_color_t *color)
{
    uint32_t timeout = 0;
    uint16_t width = ex - sx + 1;
    uint16_t height = ey - sy + 1;
    uint32_t dst_addr;
    uint16_t dst_offline;
    
    // 计算LTDC帧缓冲区目标地址
    dst_addr = (uint32_t)g_ltdc_framebuf[lcdltdc.activelayer] + lcdltdc.pixsize * (lcdltdc.pwidth * sy + sx);
    dst_offline = lcdltdc.pwidth - width;
    
    RCC->AHB3ENR |= 1 << 4;                     // 使能DMA2D时钟
    
    // 等待DMA2D空闲
    while(DMA2D->CR & DMA2D_CR_START);
    
    DMA2D->CR = 0x00000000UL;                   // 存储器到存储器模式
    
    // 前景层配置 (LVGL缓冲区)
    DMA2D->FGPFCCR = LTDC_PIXFORMAT;            // RGB565格式
    DMA2D->FGMAR = (uint32_t)color;             // 源地址
    DMA2D->FGOR = 0;                            // 源行偏移为0（LVGL缓冲区连续）
    
    // 输出层配置 (LTDC帧缓冲区)
    DMA2D->OPFCCR = LTDC_PIXFORMAT;             // RGB565格式
    DMA2D->OMAR = dst_addr;                     // LTDC帧缓冲区地址
    DMA2D->OOR = dst_offline;                   // 目标行偏移
    
    // 设置传输尺寸
    DMA2D->NLR = (uint32_t)(width << 16) | height;
    
    // 启动传输
    DMA2D->CR |= DMA2D_CR_START;
    
    // 等待传输完成
    while (!(DMA2D->ISR & DMA2D_ISR_TCIF))
    {
        timeout++;
        if (timeout > 0X1FFFFF) break;
    }
    
    DMA2D->IFCR = DMA2D_IFCR_CTCIF;             // 清除传输完成标志
}

/**
 * @brief       初始化并注册显示设备 - 内部RAM版本
 */
void lv_port_disp_init(void)
{
    // 初始化显示硬件
    disp_init();

    // 使用内部RAM创建缓冲区 - 避免频闪的关键配置
    static lv_disp_draw_buf_t draw_buf_dsc;
    
    // 在内部RAM中分配缓冲区 - 30行双缓冲
    static lv_color_t buf_1[MY_DISP_HOR_RES * 30];    // ~48KB
    static lv_color_t buf_2[MY_DISP_HOR_RES * 30];    // ~48KB 
    
    // 初始化双缓冲
    lv_disp_draw_buf_init(&draw_buf_dsc, buf_1, buf_2, MY_DISP_HOR_RES * 30);

    // 注册显示设备驱动
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);

    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf_dsc;
    
    // 关键：不使用全屏刷新
    disp_drv.full_refresh = 0;
    
    lv_disp_drv_register(&disp_drv);
}

/**
 * @brief       初始化显示硬件
 */
static void disp_init(void)
{
    // 基础LCD初始化
    lcd_init();
    lcd_display_dir(1);     // 横屏显示
    
    // 如果是RGB屏，保持LTDC默认配置
    if(lcddev.id == 0x7084 || lcddev.id == 0x4384)
    {
        // LTDC使用内部默认帧缓冲区
        // 不做额外修改，避免频闪问题
    }
}

/**
 * @brief       显示刷新回调 - 防频闪优化
 */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    // 对于RGB屏使用DMA2D加速
    if(lcddev.id == 0x7084 || lcddev.id == 0x4384)
    {
        // 使用DMA2D快速传输到LTDC帧缓冲区
        lcd_dma2d_fast_copy(area->x1, area->y1, area->x2, area->y2, color_p);
    }
    else
    {
        // SPI/并口屏使用传统方法
        lcd_color_fill(area->x1, area->y1, area->x2, area->y2, (uint16_t *)color_p);
    }

    // 立即通知刷新完成
    lv_disp_flush_ready(disp_drv);
}

#else
typedef int keep_pedantic_happy;
#endif
