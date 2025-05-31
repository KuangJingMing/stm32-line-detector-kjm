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
/* 导入lcd驱动头文件 */
#include "./BSP/LCD/lcd.h"

/*********************
 *      DEFINES
 *********************/
#define USE_SRAM        1       /* 使用外部sdram为1，否则为0 */
#ifdef USE_SRAM
#include "./BSP/SDRAM/sdram.h"  /* 包含SDRAM驱动头文件 */
#endif

#define MY_DISP_HOR_RES (800)   /* 屏幕宽度 */
#define MY_DISP_VER_RES (480)   /* 屏幕高度 */

/* SDRAM地址定义(根据你的硬件修改) */
#ifndef BANK5_SDRAM_ADDR
#define BANK5_SDRAM_ADDR        0xC0000000  /* SDRAM基地址 */
#endif

#define LVGL_BUFFER_ADDR        (BANK5_SDRAM_ADDR + 0x100000)  /* LVGL缓冲区地址偏移 */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
/* 显示设备初始化函数 */
static void disp_init(void);

/* 显示设备刷新函数 */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
/**
 * @brief       LCD加速绘制函数
 * @param       (sx,sy),(ex,ey):填充矩形对角坐标,区域大小为:(ex - sx + 1) * (ey - sy + 1)
 * @param       color:要填充的颜色
 * @retval      无
 */
void lcd_draw_fast_rgb_color(int16_t sx, int16_t sy,int16_t ex, int16_t ey, uint16_t *color)
{
    uint16_t w = ex-sx+1;
    uint16_t h = ey-sy+1;

    lcd_set_window(sx, sy, w, h);
    uint32_t draw_size = w * h;
    lcd_write_ram_prepare();

    for(uint32_t i = 0; i < draw_size; i++)
    {
        lcd_wr_data(color[i]);
    }
}

/**
 * @brief       初始化并注册显示设备
 * @param       无
 * @retval      无
 */
void lv_port_disp_init(void)
{
    /*-------------------------
     * 初始化显示设备
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * 创建一个绘图缓冲区
     *----------------------------*/

    static lv_disp_draw_buf_t draw_buf_dsc_1;
    
#if USE_SRAM
    /* 使用外部SDRAM作为显示缓冲区 */
    lv_color_t *buf_1 = (lv_color_t *)LVGL_BUFFER_ADDR;
    
    /* 可选：清零缓冲区 */
    memset(buf_1, 0, MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t));
    
    /* 初始化显示缓冲区 - 使用全屏缓冲区以获得最佳性能 */
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * MY_DISP_VER_RES);
#else
    /* 使用内部RAM（较小的缓冲区） */
    static lv_color_t buf_1[MY_DISP_HOR_RES * 100];  /* 减少到100行以节省内存 */
    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 100);
#endif

    /* 双缓冲区示例（可选，需要更多SDRAM空间）*/
#if 0 && USE_SRAM
    static lv_disp_draw_buf_t draw_buf_dsc_2;
    lv_color_t *buf_2_1 = (lv_color_t *)LVGL_BUFFER_ADDR;
    lv_color_t *buf_2_2 = (lv_color_t *)(LVGL_BUFFER_ADDR + MY_DISP_HOR_RES * MY_DISP_VER_RES * sizeof(lv_color_t));
    
    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * MY_DISP_VER_RES);
#endif

    /*-----------------------------------
     * 在 LVGL 中注册显示设备
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                  /* 显示设备的描述符 */
    lv_disp_drv_init(&disp_drv);                    /* 初始化为默认值 */

    /* 建立访问显示设备的函数  */
    disp_drv.hor_res = lcddev.width;
    disp_drv.ver_res = lcddev.height;

    /* 用来将缓冲区的内容复制到显示设备 */
    disp_drv.flush_cb = disp_flush;

    /* 设置显示缓冲区 */
    disp_drv.draw_buf = &draw_buf_dsc_1;

#if USE_SRAM
    /* 全屏缓冲区时启用全刷新模式以获得最佳性能 */
    disp_drv.full_refresh = 1;
#endif

    /* 注册显示设备 */
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * @brief       初始化显示设备和必要的外围设备
 * @param       无
 * @retval      无
 */
static void disp_init(void)
{
#if USE_SRAM
    /* 首先初始化SDRAM */
    sdram_init();
#endif
    
    /* 初始化LCD */
    lcd_init();
    lcd_display_dir(1); /* 设置横屏 */
}

/**
 * @brief       将内部缓冲区的内容刷新到显示屏上的特定区域
 * @param       disp_drv    : 显示设备
 * @param       area        : 要刷新的区域
 * @param       color_p     : 颜色数组
 * @retval      无
 */
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    /* 在指定区域内填充指定颜色块 */
    lcd_color_fill(area->x1, area->y1, area->x2, area->y2, (uint16_t *)color_p);
    
    /* 重要!!! 通知图形库，已经刷新完毕了 */
    lv_disp_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif