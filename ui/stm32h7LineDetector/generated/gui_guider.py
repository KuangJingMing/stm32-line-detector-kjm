# Copyright 2025 NXP
# NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
# accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
# activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
# comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
# terms, then you may not retain, install, activate or otherwise use the software.

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct
import fs_driver

lv.init()
SDL.init(w=800,h=480)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(800*480*4)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 800
disp_drv.ver_res = 480
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init()
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

fs_drv = lv.fs_drv_t()
fs_driver.fs_register(fs_drv, 'Z')

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def anim_width_cb(obj, v):
    obj.set_width(v)

def anim_height_cb(obj, v):
    obj.set_height(v)

def anim_img_zoom_cb(obj, v):
    obj.set_zoom(v)

def anim_img_rotate_cb(obj, v):
    obj.set_angle(v)

global_font_cache = {}
def test_font(font_family, font_size):
    global global_font_cache
    if font_family + str(font_size) in global_font_cache:
        return global_font_cache[font_family + str(font_size)]
    if font_size % 2:
        candidates = [
            (font_family, font_size),
            (font_family, font_size-font_size%2),
            (font_family, font_size+font_size%2),
            ("montserrat", font_size-font_size%2),
            ("montserrat", font_size+font_size%2),
            ("montserrat", 16)
        ]
    else:
        candidates = [
            (font_family, font_size),
            ("montserrat", font_size),
            ("montserrat", 16)
        ]
    for (family, size) in candidates:
        try:
            if eval(f'lv.font_{family}_{size}'):
                global_font_cache[font_family + str(font_size)] = eval(f'lv.font_{family}_{size}')
                if family != font_family or size != font_size:
                    print(f'WARNING: lv.font_{family}_{size} is used!')
                return eval(f'lv.font_{family}_{size}')
        except AttributeError:
            try:
                load_font = lv.font_load(f"Z:MicroPython/lv_font_{family}_{size}.fnt")
                global_font_cache[font_family + str(font_size)] = load_font
                return load_font
            except:
                if family == font_family and size == font_size:
                    print(f'WARNING: lv.font_{family}_{size} is NOT supported!')

global_image_cache = {}
def load_image(file):
    global global_image_cache
    if file in global_image_cache:
        return global_image_cache[file]
    try:
        with open(file,'rb') as f:
            data = f.read()
    except:
        print(f'Could not open {file}')
        sys.exit()

    img = lv.img_dsc_t({
        'data_size': len(data),
        'data': data
    })
    global_image_cache[file] = img
    return img

def calendar_event_handler(e,obj):
    code = e.get_code()

    if code == lv.EVENT.VALUE_CHANGED:
        source = e.get_current_target()
        date = lv.calendar_date_t()
        if source.get_pressed_date(date) == lv.RES.OK:
            source.set_highlighted_dates([date], 1)

def spinbox_increment_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.increment()
def spinbox_decrement_event_cb(e, obj):
    code = e.get_code()
    if code == lv.EVENT.SHORT_CLICKED or code == lv.EVENT.LONG_PRESSED_REPEAT:
        obj.decrement()

def digital_clock_cb(timer, obj, current_time, show_second, use_ampm):
    hour = int(current_time[0])
    minute = int(current_time[1])
    second = int(current_time[2])
    ampm = current_time[3]
    second = second + 1
    if second == 60:
        second = 0
        minute = minute + 1
        if minute == 60:
            minute = 0
            hour = hour + 1
            if use_ampm:
                if hour == 12:
                    if ampm == 'AM':
                        ampm = 'PM'
                    elif ampm == 'PM':
                        ampm = 'AM'
                if hour > 12:
                    hour = hour % 12
    hour = hour % 24
    if use_ampm:
        if show_second:
            obj.set_text("%d:%02d:%02d %s" %(hour, minute, second, ampm))
        else:
            obj.set_text("%d:%02d %s" %(hour, minute, ampm))
    else:
        if show_second:
            obj.set_text("%d:%02d:%02d" %(hour, minute, second))
        else:
            obj.set_text("%d:%02d" %(hour, minute))
    current_time[0] = hour
    current_time[1] = minute
    current_time[2] = second
    current_time[3] = ampm

def analog_clock_cb(timer, obj):
    datetime = time.localtime()
    hour = datetime[3]
    if hour >= 12: hour = hour - 12
    obj.set_time(hour, datetime[4], datetime[5])

def datetext_event_handler(e, obj):
    code = e.get_code()
    target = e.get_target()
    if code == lv.EVENT.FOCUSED:
        if obj is None:
            bg = lv.layer_top()
            bg.add_flag(lv.obj.FLAG.CLICKABLE)
            obj = lv.calendar(bg)
            scr = target.get_screen()
            scr_height = scr.get_height()
            scr_width = scr.get_width()
            obj.set_size(int(scr_width * 0.8), int(scr_height * 0.8))
            datestring = target.get_text()
            year = int(datestring.split('/')[0])
            month = int(datestring.split('/')[1])
            day = int(datestring.split('/')[2])
            obj.set_showed_date(year, month)
            highlighted_days=[lv.calendar_date_t({'year':year, 'month':month, 'day':day})]
            obj.set_highlighted_dates(highlighted_days, 1)
            obj.align(lv.ALIGN.CENTER, 0, 0)
            lv.calendar_header_arrow(obj)
            obj.add_event_cb(lambda e: datetext_calendar_event_handler(e, target), lv.EVENT.ALL, None)
            scr.update_layout()

def datetext_calendar_event_handler(e, obj):
    code = e.get_code()
    target = e.get_current_target()
    if code == lv.EVENT.VALUE_CHANGED:
        date = lv.calendar_date_t()
        if target.get_pressed_date(date) == lv.RES.OK:
            obj.set_text(f"{date.year}/{date.month}/{date.day}")
            bg = lv.layer_top()
            bg.clear_flag(lv.obj.FLAG.CLICKABLE)
            bg.set_style_bg_opa(lv.OPA.TRANSP, 0)
            target.delete()

# Create scrHome
scrHome = lv.obj()
scrHome.set_size(800, 480)
scrHome.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome.set_style_bg_color(lv.color_hex(0xF3F8FE), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_contBG
scrHome_contBG = lv.obj(scrHome)
scrHome_contBG.set_pos(0, 0)
scrHome_contBG.set_size(800, 105)
scrHome_contBG.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome_contBG, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_contBG.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_bg_color(lv.color_hex(0x2f3243), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contBG.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_contMain
scrHome_contMain = lv.obj(scrHome)
scrHome_contMain.set_pos(58, 111)
scrHome_contMain.set_size(683, 247)
scrHome_contMain.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome_contMain, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_contMain.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_radius(12, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contMain.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create scrHome_contSetup
scrHome_contSetup = lv.obj(scrHome_contMain)
scrHome_contSetup.set_pos(510, 17)
scrHome_contSetup.set_size(166, 211)
scrHome_contSetup.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome_contSetup, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_contSetup.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_bg_img_src("B:MicroPython/_btn_bg_4_166x211.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contSetup.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create scrHome_imgIconSetup
scrHome_imgIconSetup = lv.img(scrHome_contSetup)
scrHome_imgIconSetup.set_src("B:MicroPython/_setup_alpha_66x66.bin")
scrHome_imgIconSetup.add_flag(lv.obj.FLAG.CLICKABLE)
scrHome_imgIconSetup.set_pivot(50,50)
scrHome_imgIconSetup.set_angle(0)
scrHome_imgIconSetup.set_pos(75, 33)
scrHome_imgIconSetup.set_size(66, 66)
scrHome_imgIconSetup.add_flag(lv.obj.FLAG.EVENT_BUBBLE)
# Set style for scrHome_imgIconSetup, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_imgIconSetup.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconSetup.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconSetup.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_labelSetup
scrHome_labelSetup = lv.label(scrHome_contSetup)
scrHome_labelSetup.set_text("设置模式")
scrHome_labelSetup.set_long_mode(lv.label.LONG.WRAP)
scrHome_labelSetup.set_width(lv.pct(100))
scrHome_labelSetup.set_pos(8, 157)
scrHome_labelSetup.set_size(128, 33)
scrHome_labelSetup.add_flag(lv.obj.FLAG.EVENT_BUBBLE)
# Set style for scrHome_labelSetup, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_labelSetup.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_text_font(test_font("SourceHanSerifSC_Regular", 25), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelSetup.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_contPrint
scrHome_contPrint = lv.obj(scrHome_contMain)
scrHome_contPrint.set_pos(343, 17)
scrHome_contPrint.set_size(166, 211)
scrHome_contPrint.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome_contPrint, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_contPrint.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_bg_img_src("B:MicroPython/_btn_bg_3_166x211.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contPrint.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create scrHome_imgIconPrint
scrHome_imgIconPrint = lv.img(scrHome_contPrint)
scrHome_imgIconPrint.set_src("B:MicroPython/_print_alpha_66x66.bin")
scrHome_imgIconPrint.add_flag(lv.obj.FLAG.CLICKABLE)
scrHome_imgIconPrint.set_pivot(50,50)
scrHome_imgIconPrint.set_angle(0)
scrHome_imgIconPrint.set_pos(75, 33)
scrHome_imgIconPrint.set_size(66, 66)
scrHome_imgIconPrint.add_flag(lv.obj.FLAG.EVENT_BUBBLE)
# Set style for scrHome_imgIconPrint, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_imgIconPrint.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconPrint.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconPrint.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_labelPrint
scrHome_labelPrint = lv.label(scrHome_contPrint)
scrHome_labelPrint.set_text("日志模式")
scrHome_labelPrint.set_long_mode(lv.label.LONG.WRAP)
scrHome_labelPrint.set_width(lv.pct(100))
scrHome_labelPrint.set_pos(5, 157)
scrHome_labelPrint.set_size(128, 33)
scrHome_labelPrint.add_flag(lv.obj.FLAG.EVENT_BUBBLE)
# Set style for scrHome_labelPrint, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_labelPrint.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_text_font(test_font("SourceHanSerifSC_Regular", 25), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrint.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_contCopy
scrHome_contCopy = lv.obj(scrHome_contMain)
scrHome_contCopy.set_pos(10, 17)
scrHome_contCopy.set_size(166, 211)
scrHome_contCopy.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome_contCopy, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_contCopy.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_bg_img_src("B:MicroPython/_btn_bg_1_166x211.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contCopy.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create scrHome_imgIconCopy
scrHome_imgIconCopy = lv.img(scrHome_contCopy)
scrHome_imgIconCopy.set_src("B:MicroPython/_copy_alpha_61x70.bin")
scrHome_imgIconCopy.add_flag(lv.obj.FLAG.CLICKABLE)
scrHome_imgIconCopy.set_pivot(50,50)
scrHome_imgIconCopy.set_angle(0)
scrHome_imgIconCopy.set_pos(75, 33)
scrHome_imgIconCopy.set_size(61, 70)
scrHome_imgIconCopy.add_flag(lv.obj.FLAG.EVENT_BUBBLE)
# Set style for scrHome_imgIconCopy, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_imgIconCopy.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconCopy.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconCopy.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_labelCopy
scrHome_labelCopy = lv.label(scrHome_contCopy)
scrHome_labelCopy.set_text("学习模式")
scrHome_labelCopy.set_long_mode(lv.label.LONG.WRAP)
scrHome_labelCopy.set_width(lv.pct(100))
scrHome_labelCopy.set_pos(5, 157)
scrHome_labelCopy.set_size(128, 33)
scrHome_labelCopy.add_flag(lv.obj.FLAG.EVENT_BUBBLE)
# Set style for scrHome_labelCopy, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_labelCopy.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_text_font(test_font("SourceHanSerifSC_Regular", 25), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelCopy.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_contScan
scrHome_contScan = lv.obj(scrHome_contMain)
scrHome_contScan.set_pos(176, 18)
scrHome_contScan.set_size(166, 211)
scrHome_contScan.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome_contScan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_contScan.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_bg_img_src("B:MicroPython/_btn_bg_2_166x211.bin", lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_bg_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_bg_img_recolor_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contScan.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create scrHome_imgIconScan
scrHome_imgIconScan = lv.img(scrHome_contScan)
scrHome_imgIconScan.set_src("B:MicroPython/_scan_alpha_61x70.bin")
scrHome_imgIconScan.add_flag(lv.obj.FLAG.CLICKABLE)
scrHome_imgIconScan.set_pivot(50,50)
scrHome_imgIconScan.set_angle(0)
scrHome_imgIconScan.set_pos(75, 33)
scrHome_imgIconScan.set_size(61, 70)
scrHome_imgIconScan.add_flag(lv.obj.FLAG.EVENT_BUBBLE)
# Set style for scrHome_imgIconScan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_imgIconScan.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconScan.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconScan.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_labelScan
scrHome_labelScan = lv.label(scrHome_contScan)
scrHome_labelScan.set_text("检测模式")
scrHome_labelScan.set_long_mode(lv.label.LONG.WRAP)
scrHome_labelScan.set_width(lv.pct(100))
scrHome_labelScan.set_pos(5, 157)
scrHome_labelScan.set_size(128, 33)
scrHome_labelScan.add_flag(lv.obj.FLAG.EVENT_BUBBLE)
# Set style for scrHome_labelScan, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_labelScan.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_text_font(test_font("SourceHanSerifSC_Regular", 25), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelScan.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_contTop
scrHome_contTop = lv.obj(scrHome)
scrHome_contTop.set_pos(38, -1)
scrHome_contTop.set_size(723, 107)
scrHome_contTop.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome_contTop, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_contTop.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contTop.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contTop.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contTop.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contTop.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contTop.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contTop.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contTop.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create scrHome_imgIconWIFI
scrHome_imgIconWIFI = lv.img(scrHome_contTop)
scrHome_imgIconWIFI.set_src("B:MicroPython/_wifi_alpha_55x44.bin")
scrHome_imgIconWIFI.add_flag(lv.obj.FLAG.CLICKABLE)
scrHome_imgIconWIFI.set_pivot(50,50)
scrHome_imgIconWIFI.set_angle(0)
scrHome_imgIconWIFI.set_pos(33, 37)
scrHome_imgIconWIFI.set_size(55, 44)
# Set style for scrHome_imgIconWIFI, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_imgIconWIFI.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconWIFI.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconWIFI.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_imgIconCall
scrHome_imgIconCall = lv.img(scrHome_contTop)
scrHome_imgIconCall.set_src("B:MicroPython/_tel_alpha_46x42.bin")
scrHome_imgIconCall.add_flag(lv.obj.FLAG.CLICKABLE)
scrHome_imgIconCall.set_pivot(50,50)
scrHome_imgIconCall.set_angle(0)
scrHome_imgIconCall.set_pos(118, 38)
scrHome_imgIconCall.set_size(46, 42)
# Set style for scrHome_imgIconCall, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_imgIconCall.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconCall.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconCall.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_imgIconEco
scrHome_imgIconEco = lv.img(scrHome_contTop)
scrHome_imgIconEco.set_src("B:MicroPython/_eco_alpha_48x38.bin")
scrHome_imgIconEco.add_flag(lv.obj.FLAG.CLICKABLE)
scrHome_imgIconEco.set_pivot(50,50)
scrHome_imgIconEco.set_angle(0)
scrHome_imgIconEco.set_pos(190, 37)
scrHome_imgIconEco.set_size(48, 38)
# Set style for scrHome_imgIconEco, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_imgIconEco.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconEco.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconEco.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_imgIconPC
scrHome_imgIconPC = lv.img(scrHome_contTop)
scrHome_imgIconPC.set_src("B:MicroPython/_pc_alpha_50x42.bin")
scrHome_imgIconPC.add_flag(lv.obj.FLAG.CLICKABLE)
scrHome_imgIconPC.set_pivot(50,50)
scrHome_imgIconPC.set_angle(0)
scrHome_imgIconPC.set_pos(276, 37)
scrHome_imgIconPC.set_size(50, 42)
# Set style for scrHome_imgIconPC, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_imgIconPC.set_style_img_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconPC.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_imgIconPC.set_style_clip_corner(True, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_labelDate
scrHome_labelDate = lv.label(scrHome_contTop)
scrHome_labelDate.set_text("22 Aug 2023  14:30")
scrHome_labelDate.set_long_mode(lv.label.LONG.WRAP)
scrHome_labelDate.set_width(lv.pct(100))
scrHome_labelDate.set_pos(366, 44)
scrHome_labelDate.set_size(363, 49)
# Set style for scrHome_labelDate, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_labelDate.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_text_color(lv.color_hex(0xe9e9e9), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_text_font(test_font("montserratMedium", 26), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelDate.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_labelPrompt
scrHome_labelPrompt = lv.label(scrHome)
scrHome_labelPrompt.set_text("stm32h7线束检测器")
scrHome_labelPrompt.set_long_mode(lv.label.LONG.WRAP)
scrHome_labelPrompt.set_width(lv.pct(100))
scrHome_labelPrompt.set_pos(58, 382)
scrHome_labelPrompt.set_size(415, 79)
# Set style for scrHome_labelPrompt, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_labelPrompt.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_radius(14, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_text_color(lv.color_hex(0x000000), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_text_font(test_font("SourceHanSerifSC_Regular", 23), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_text_line_space(50, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_labelPrompt.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrHome_contColorInk
scrHome_contColorInk = lv.obj(scrHome)
scrHome_contColorInk.set_pos(506, 370)
scrHome_contColorInk.set_size(235, 91)
scrHome_contColorInk.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrHome_contColorInk, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_contColorInk.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_radius(14, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_bg_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_contColorInk.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Create scrHome_barBlueInk
scrHome_barBlueInk = lv.bar(scrHome_contColorInk)
scrHome_barBlueInk.set_style_anim_time(1000, 0)
scrHome_barBlueInk.set_mode(lv.bar.MODE.NORMAL)
scrHome_barBlueInk.set_range(0, 100)
scrHome_barBlueInk.set_value(80, lv.ANIM.ON)
scrHome_barBlueInk.set_pos(16, 0)
scrHome_barBlueInk.set_size(40, 88)
# Set style for scrHome_barBlueInk, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_barBlueInk.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_barBlueInk.set_style_radius(17, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_barBlueInk.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for scrHome_barBlueInk, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
scrHome_barBlueInk.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barBlueInk.set_style_bg_color(lv.color_hex(0x2ad3ff), lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barBlueInk.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barBlueInk.set_style_radius(17, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Create scrHome_barRedInk
scrHome_barRedInk = lv.bar(scrHome_contColorInk)
scrHome_barRedInk.set_style_anim_time(1000, 0)
scrHome_barRedInk.set_mode(lv.bar.MODE.NORMAL)
scrHome_barRedInk.set_range(0, 100)
scrHome_barRedInk.set_value(25, lv.ANIM.ON)
scrHome_barRedInk.set_pos(68, 0)
scrHome_barRedInk.set_size(35, 88)
# Set style for scrHome_barRedInk, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_barRedInk.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_barRedInk.set_style_radius(17, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_barRedInk.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for scrHome_barRedInk, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
scrHome_barRedInk.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barRedInk.set_style_bg_color(lv.color_hex(0xef1382), lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barRedInk.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barRedInk.set_style_radius(17, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Create scrHome_barYellowInk
scrHome_barYellowInk = lv.bar(scrHome_contColorInk)
scrHome_barYellowInk.set_style_anim_time(1000, 0)
scrHome_barYellowInk.set_mode(lv.bar.MODE.NORMAL)
scrHome_barYellowInk.set_range(0, 100)
scrHome_barYellowInk.set_value(70, lv.ANIM.ON)
scrHome_barYellowInk.set_pos(115, 0)
scrHome_barYellowInk.set_size(40, 88)
# Set style for scrHome_barYellowInk, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_barYellowInk.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_barYellowInk.set_style_radius(17, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_barYellowInk.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for scrHome_barYellowInk, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
scrHome_barYellowInk.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barYellowInk.set_style_bg_color(lv.color_hex(0xe4ea09), lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barYellowInk.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barYellowInk.set_style_radius(17, lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Create scrHome_barBlackInk
scrHome_barBlackInk = lv.bar(scrHome_contColorInk)
scrHome_barBlackInk.set_style_anim_time(1000, 0)
scrHome_barBlackInk.set_mode(lv.bar.MODE.NORMAL)
scrHome_barBlackInk.set_range(0, 100)
scrHome_barBlackInk.set_value(55, lv.ANIM.ON)
scrHome_barBlackInk.set_pos(171, -3)
scrHome_barBlackInk.set_size(40, 88)
# Set style for scrHome_barBlackInk, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrHome_barBlackInk.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_barBlackInk.set_style_radius(17, lv.PART.MAIN|lv.STATE.DEFAULT)
scrHome_barBlackInk.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
# Set style for scrHome_barBlackInk, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
scrHome_barBlackInk.set_style_bg_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barBlackInk.set_style_bg_color(lv.color_hex(0x000000), lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barBlackInk.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrHome_barBlackInk.set_style_radius(17, lv.PART.INDICATOR|lv.STATE.DEFAULT)

scrHome.update_layout()
# Create scrComplete
scrComplete = lv.obj()
scrComplete.set_size(800, 480)
scrComplete.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrComplete, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrComplete.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete.set_style_bg_color(lv.color_hex(0xF3F8FE), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrComplete_contBG
scrComplete_contBG = lv.obj(scrComplete)
scrComplete_contBG.set_pos(0, 0)
scrComplete_contBG.set_size(800, 105)
scrComplete_contBG.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrComplete_contBG, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrComplete_contBG.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_bg_color(lv.color_hex(0x2f3243), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_contBG.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrComplete_labelTitle
scrComplete_labelTitle = lv.label(scrComplete)
scrComplete_labelTitle.set_text("xxx完成")
scrComplete_labelTitle.set_long_mode(lv.label.LONG.WRAP)
scrComplete_labelTitle.set_width(lv.pct(100))
scrComplete_labelTitle.set_pos(225, 40)
scrComplete_labelTitle.set_size(350, 56)
# Set style for scrComplete_labelTitle, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrComplete_labelTitle.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_text_font(test_font("SourceHanSerifSC_Regular", 33), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_labelTitle.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrComplete_btnNext
scrComplete_btnNext = lv.btn(scrComplete)
scrComplete_btnNext_label = lv.label(scrComplete_btnNext)
scrComplete_btnNext_label.set_text("返回")
scrComplete_btnNext_label.set_long_mode(lv.label.LONG.WRAP)
scrComplete_btnNext_label.set_width(lv.pct(100))
scrComplete_btnNext_label.align(lv.ALIGN.CENTER, 0, 0)
scrComplete_btnNext.set_style_pad_all(0, lv.STATE.DEFAULT)
scrComplete_btnNext.set_pos(594, 393)
scrComplete_btnNext.set_size(166, 65)
# Set style for scrComplete_btnNext, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrComplete_btnNext.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_bg_color(lv.color_hex(0x2f3243), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_radius(30, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_text_font(test_font("SourceHanSerifSC_Regular", 30), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnNext.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrComplete_btnBack
scrComplete_btnBack = lv.btn(scrComplete)
scrComplete_btnBack_label = lv.label(scrComplete_btnBack)
scrComplete_btnBack_label.set_text("<")
scrComplete_btnBack_label.set_long_mode(lv.label.LONG.WRAP)
scrComplete_btnBack_label.set_width(lv.pct(100))
scrComplete_btnBack_label.align(lv.ALIGN.CENTER, 0, 0)
scrComplete_btnBack.set_style_pad_all(0, lv.STATE.DEFAULT)
scrComplete_btnBack.set_pos(41, 30)
scrComplete_btnBack.set_size(58, 56)
# Set style for scrComplete_btnBack, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrComplete_btnBack.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnBack.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnBack.set_style_radius(8, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnBack.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnBack.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnBack.set_style_text_font(test_font("montserratMedium", 41), lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnBack.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrComplete_btnBack.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)

scrComplete.update_layout()
# Create scrLoader
scrLoader = lv.obj()
scrLoader.set_size(800, 480)
scrLoader.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrLoader, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrLoader.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader.set_style_bg_color(lv.color_hex(0xF3F8FE), lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrLoader_contBG
scrLoader_contBG = lv.obj(scrLoader)
scrLoader_contBG.set_pos(0, -1)
scrLoader_contBG.set_size(800, 480)
scrLoader_contBG.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# Set style for scrLoader_contBG, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrLoader_contBG.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_bg_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_bg_color(lv.color_hex(0x2f3243), lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_bg_grad_dir(lv.GRAD_DIR.NONE, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_contBG.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrLoader_arcLoader
scrLoader_arcLoader = lv.arc(scrLoader)
scrLoader_arcLoader.set_mode(lv.arc.MODE.NORMAL)
scrLoader_arcLoader.set_range(0, 100)
scrLoader_arcLoader.set_bg_angles(0, 360)
scrLoader_arcLoader.set_value(0)
scrLoader_arcLoader.set_rotation(270)
scrLoader_arcLoader.set_pos(283, 98)
scrLoader_arcLoader.set_size(233, 233)
# Set style for scrLoader_arcLoader, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrLoader_arcLoader.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_arc_width(6, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_arc_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_arc_color(lv.color_hex(0x2f3243), lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_radius(10, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Set style for scrLoader_arcLoader, Part: lv.PART.INDICATOR, State: lv.STATE.DEFAULT.
scrLoader_arcLoader.set_style_arc_width(6, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_arc_opa(255, lv.PART.INDICATOR|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_arc_color(lv.color_hex(0xffffff), lv.PART.INDICATOR|lv.STATE.DEFAULT)

# Set style for scrLoader_arcLoader, Part: lv.PART.KNOB, State: lv.STATE.DEFAULT.
scrLoader_arcLoader.set_style_bg_opa(0, lv.PART.KNOB|lv.STATE.DEFAULT)
scrLoader_arcLoader.set_style_pad_all(0, lv.PART.KNOB|lv.STATE.DEFAULT)

# Create scrLoader_tpLoader
scrLoader_tpLoader = lv.textprogress(scrLoader)
scrLoader_tpLoader.set_range_value(0, 100, 0, 0)
scrLoader_tpLoader.set_decimal(0)
scrLoader_tpLoader.set_value(0)
scrLoader_tpLoader.set_pos(316, 194)
scrLoader_tpLoader.set_size(166, 56)
# Set style for scrLoader_tpLoader, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrLoader_tpLoader.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_text_font(test_font("montserratMedium", 33), lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_text_letter_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_pad_top(8, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_tpLoader.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

# Create scrLoader_labelPrompt
scrLoader_labelPrompt = lv.label(scrLoader)
scrLoader_labelPrompt.set_text("正在xxx，请稍后")
scrLoader_labelPrompt.set_long_mode(lv.label.LONG.WRAP)
scrLoader_labelPrompt.set_width(lv.pct(100))
scrLoader_labelPrompt.set_pos(121, 403)
scrLoader_labelPrompt.set_size(558, 56)
# Set style for scrLoader_labelPrompt, Part: lv.PART.MAIN, State: lv.STATE.DEFAULT.
scrLoader_labelPrompt.set_style_border_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_radius(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_text_color(lv.color_hex(0xffffff), lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_text_font(test_font("SourceHanSerifSC_Regular", 33), lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_text_opa(255, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_text_letter_space(1, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_text_line_space(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_text_align(lv.TEXT_ALIGN.CENTER, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_bg_opa(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_pad_top(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_pad_right(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_pad_bottom(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_pad_left(0, lv.PART.MAIN|lv.STATE.DEFAULT)
scrLoader_labelPrompt.set_style_shadow_width(0, lv.PART.MAIN|lv.STATE.DEFAULT)

scrLoader.update_layout()

def scrHome_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: scrHome_contBG width
        scrHome_contBG_anim_width = lv.anim_t()
        scrHome_contBG_anim_width.init()
        scrHome_contBG_anim_width.set_var(scrHome_contBG)
        scrHome_contBG_anim_width.set_time(150)
        scrHome_contBG_anim_width.set_delay(0)
        scrHome_contBG_anim_width.set_custom_exec_cb(lambda e,val: anim_width_cb(scrHome_contBG,val))
        scrHome_contBG_anim_width.set_values(scrHome_contBG.get_width(), 800)
        scrHome_contBG_anim_width.set_path_cb(lv.anim_t.path_ease_out)
        scrHome_contBG_anim_width.set_repeat_count(0)
        scrHome_contBG_anim_width.set_repeat_delay(0)
        scrHome_contBG_anim_width.set_playback_time(0)
        scrHome_contBG_anim_width.set_playback_delay(0)
        scrHome_contBG_anim_width.start()
        #Write animation: scrHome_contBG height
        scrHome_contBG_anim_height = lv.anim_t()
        scrHome_contBG_anim_height.init()
        scrHome_contBG_anim_height.set_var(scrHome_contBG)
        scrHome_contBG_anim_height.set_time(150)
        scrHome_contBG_anim_height.set_delay(0)
        scrHome_contBG_anim_height.set_custom_exec_cb(lambda e,val: anim_height_cb(scrHome_contBG,val))
        scrHome_contBG_anim_height.set_values(scrHome_contBG.get_height(), 150)
        scrHome_contBG_anim_height.set_path_cb(lv.anim_t.path_ease_out)
        scrHome_contBG_anim_height.set_repeat_count(0)
        scrHome_contBG_anim_height.set_repeat_delay(0)
        scrHome_contBG_anim_height.set_playback_time(0)
        scrHome_contBG_anim_height.set_playback_delay(0)
        scrHome_contBG_anim_height.start()
scrHome.add_event_cb(lambda e: scrHome_event_handler(e), lv.EVENT.ALL, None)

def scrHome_contSetup_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        scrHome_contBG.set_style_bg_color(lv.color_hex(0xe12e2e), lv.PART.MAIN)
        #Write animation: scrHome_contBG width
        scrHome_contBG_anim_width = lv.anim_t()
        scrHome_contBG_anim_width.init()
        scrHome_contBG_anim_width.set_var(scrHome_contBG)
        scrHome_contBG_anim_width.set_time(200)
        scrHome_contBG_anim_width.set_delay(0)
        scrHome_contBG_anim_width.set_custom_exec_cb(lambda e,val: anim_width_cb(scrHome_contBG,val))
        scrHome_contBG_anim_width.set_values(scrHome_contBG.get_width(), 800)
        scrHome_contBG_anim_width.set_path_cb(lv.anim_t.path_ease_in)
        scrHome_contBG_anim_width.set_repeat_count(0)
        scrHome_contBG_anim_width.set_repeat_delay(0)
        scrHome_contBG_anim_width.set_playback_time(0)
        scrHome_contBG_anim_width.set_playback_delay(0)
        scrHome_contBG_anim_width.start()
        #Write animation: scrHome_contBG height
        scrHome_contBG_anim_height = lv.anim_t()
        scrHome_contBG_anim_height.init()
        scrHome_contBG_anim_height.set_var(scrHome_contBG)
        scrHome_contBG_anim_height.set_time(200)
        scrHome_contBG_anim_height.set_delay(0)
        scrHome_contBG_anim_height.set_custom_exec_cb(lambda e,val: anim_height_cb(scrHome_contBG,val))
        scrHome_contBG_anim_height.set_values(scrHome_contBG.get_height(), 480)
        scrHome_contBG_anim_height.set_path_cb(lv.anim_t.path_ease_in)
        scrHome_contBG_anim_height.set_repeat_count(0)
        scrHome_contBG_anim_height.set_repeat_delay(0)
        scrHome_contBG_anim_height.set_playback_time(0)
        scrHome_contBG_anim_height.set_playback_delay(0)
        scrHome_contBG_anim_height.start()
scrHome_contSetup.add_event_cb(lambda e: scrHome_contSetup_event_handler(e), lv.EVENT.ALL, None)

def scrHome_contPrint_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        #Write animation: scrHome_contBG width
        scrHome_contBG_anim_width = lv.anim_t()
        scrHome_contBG_anim_width.init()
        scrHome_contBG_anim_width.set_var(scrHome_contBG)
        scrHome_contBG_anim_width.set_time(200)
        scrHome_contBG_anim_width.set_delay(0)
        scrHome_contBG_anim_width.set_custom_exec_cb(lambda e,val: anim_width_cb(scrHome_contBG,val))
        scrHome_contBG_anim_width.set_values(scrHome_contBG.get_width(), 800)
        scrHome_contBG_anim_width.set_path_cb(lv.anim_t.path_ease_in)
        scrHome_contBG_anim_width.set_repeat_count(0)
        scrHome_contBG_anim_width.set_repeat_delay(0)
        scrHome_contBG_anim_width.set_playback_time(0)
        scrHome_contBG_anim_width.set_playback_delay(0)
        scrHome_contBG_anim_width.start()
        #Write animation: scrHome_contBG height
        scrHome_contBG_anim_height = lv.anim_t()
        scrHome_contBG_anim_height.init()
        scrHome_contBG_anim_height.set_var(scrHome_contBG)
        scrHome_contBG_anim_height.set_time(200)
        scrHome_contBG_anim_height.set_delay(0)
        scrHome_contBG_anim_height.set_custom_exec_cb(lambda e,val: anim_height_cb(scrHome_contBG,val))
        scrHome_contBG_anim_height.set_values(scrHome_contBG.get_height(), 105)
        scrHome_contBG_anim_height.set_path_cb(lv.anim_t.path_ease_in)
        scrHome_contBG_anim_height.set_repeat_count(0)
        scrHome_contBG_anim_height.set_repeat_delay(0)
        scrHome_contBG_anim_height.set_playback_time(0)
        scrHome_contBG_anim_height.set_playback_delay(0)
        scrHome_contBG_anim_height.start()
scrHome_contPrint.add_event_cb(lambda e: scrHome_contPrint_event_handler(e), lv.EVENT.ALL, None)

def scrHome_contCopy_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        #Write animation: scrHome_contBG width
        scrHome_contBG_anim_width = lv.anim_t()
        scrHome_contBG_anim_width.init()
        scrHome_contBG_anim_width.set_var(scrHome_contBG)
        scrHome_contBG_anim_width.set_time(200)
        scrHome_contBG_anim_width.set_delay(0)
        scrHome_contBG_anim_width.set_custom_exec_cb(lambda e,val: anim_width_cb(scrHome_contBG,val))
        scrHome_contBG_anim_width.set_values(scrHome_contBG.get_width(), 800)
        scrHome_contBG_anim_width.set_path_cb(lv.anim_t.path_ease_out)
        scrHome_contBG_anim_width.set_repeat_count(0)
        scrHome_contBG_anim_width.set_repeat_delay(0)
        scrHome_contBG_anim_width.set_playback_time(0)
        scrHome_contBG_anim_width.set_playback_delay(0)
        scrHome_contBG_anim_width.start()
        #Write animation: scrHome_contBG height
        scrHome_contBG_anim_height = lv.anim_t()
        scrHome_contBG_anim_height.init()
        scrHome_contBG_anim_height.set_var(scrHome_contBG)
        scrHome_contBG_anim_height.set_time(200)
        scrHome_contBG_anim_height.set_delay(0)
        scrHome_contBG_anim_height.set_custom_exec_cb(lambda e,val: anim_height_cb(scrHome_contBG,val))
        scrHome_contBG_anim_height.set_values(scrHome_contBG.get_height(), 105)
        scrHome_contBG_anim_height.set_path_cb(lv.anim_t.path_ease_out)
        scrHome_contBG_anim_height.set_repeat_count(0)
        scrHome_contBG_anim_height.set_repeat_delay(0)
        scrHome_contBG_anim_height.set_playback_time(0)
        scrHome_contBG_anim_height.set_playback_delay(0)
        scrHome_contBG_anim_height.start()
        lv.scr_load_anim(scrLoader, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)
scrHome_contCopy.add_event_cb(lambda e: scrHome_contCopy_event_handler(e), lv.EVENT.ALL, None)

def scrHome_contScan_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        #Write animation: scrHome_contBG width
        scrHome_contBG_anim_width = lv.anim_t()
        scrHome_contBG_anim_width.init()
        scrHome_contBG_anim_width.set_var(scrHome_contBG)
        scrHome_contBG_anim_width.set_time(200)
        scrHome_contBG_anim_width.set_delay(0)
        scrHome_contBG_anim_width.set_custom_exec_cb(lambda e,val: anim_width_cb(scrHome_contBG,val))
        scrHome_contBG_anim_width.set_values(scrHome_contBG.get_width(), 800)
        scrHome_contBG_anim_width.set_path_cb(lv.anim_t.path_ease_in)
        scrHome_contBG_anim_width.set_repeat_count(0)
        scrHome_contBG_anim_width.set_repeat_delay(0)
        scrHome_contBG_anim_width.set_playback_time(0)
        scrHome_contBG_anim_width.set_playback_delay(0)
        scrHome_contBG_anim_width.start()
        #Write animation: scrHome_contBG height
        scrHome_contBG_anim_height = lv.anim_t()
        scrHome_contBG_anim_height.init()
        scrHome_contBG_anim_height.set_var(scrHome_contBG)
        scrHome_contBG_anim_height.set_time(200)
        scrHome_contBG_anim_height.set_delay(0)
        scrHome_contBG_anim_height.set_custom_exec_cb(lambda e,val: anim_height_cb(scrHome_contBG,val))
        scrHome_contBG_anim_height.set_values(scrHome_contBG.get_height(), 105)
        scrHome_contBG_anim_height.set_path_cb(lv.anim_t.path_ease_in)
        scrHome_contBG_anim_height.set_repeat_count(0)
        scrHome_contBG_anim_height.set_repeat_delay(0)
        scrHome_contBG_anim_height.set_playback_time(0)
        scrHome_contBG_anim_height.set_playback_delay(0)
        scrHome_contBG_anim_height.start()
        lv.scr_load_anim(scrLoader, lv.SCR_LOAD_ANIM.NONE, 200, 200, False)
scrHome_contScan.add_event_cb(lambda e: scrHome_contScan_event_handler(e), lv.EVENT.ALL, None)

def scrComplete_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        #Write animation: scrComplete_contBG width
        scrComplete_contBG_anim_width = lv.anim_t()
        scrComplete_contBG_anim_width.init()
        scrComplete_contBG_anim_width.set_var(scrComplete_contBG)
        scrComplete_contBG_anim_width.set_time(150)
        scrComplete_contBG_anim_width.set_delay(0)
        scrComplete_contBG_anim_width.set_custom_exec_cb(lambda e,val: anim_width_cb(scrComplete_contBG,val))
        scrComplete_contBG_anim_width.set_values(scrComplete_contBG.get_width(), 800)
        scrComplete_contBG_anim_width.set_path_cb(lv.anim_t.path_ease_out)
        scrComplete_contBG_anim_width.set_repeat_count(0)
        scrComplete_contBG_anim_width.set_repeat_delay(0)
        scrComplete_contBG_anim_width.set_playback_time(0)
        scrComplete_contBG_anim_width.set_playback_delay(0)
        scrComplete_contBG_anim_width.start()
        #Write animation: scrComplete_contBG height
        scrComplete_contBG_anim_height = lv.anim_t()
        scrComplete_contBG_anim_height.init()
        scrComplete_contBG_anim_height.set_var(scrComplete_contBG)
        scrComplete_contBG_anim_height.set_time(150)
        scrComplete_contBG_anim_height.set_delay(0)
        scrComplete_contBG_anim_height.set_custom_exec_cb(lambda e,val: anim_height_cb(scrComplete_contBG,val))
        scrComplete_contBG_anim_height.set_values(scrComplete_contBG.get_height(), 150)
        scrComplete_contBG_anim_height.set_path_cb(lv.anim_t.path_ease_out)
        scrComplete_contBG_anim_height.set_repeat_count(0)
        scrComplete_contBG_anim_height.set_repeat_delay(0)
        scrComplete_contBG_anim_height.set_playback_time(0)
        scrComplete_contBG_anim_height.set_playback_delay(0)
        scrComplete_contBG_anim_height.start()
scrComplete.add_event_cb(lambda e: scrComplete_event_handler(e), lv.EVENT.ALL, None)

def scrComplete_btnNext_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(scrHome, lv.SCR_LOAD_ANIM.FADE_ON, 200, 200, False)
        #Write animation: scrComplete_contBG width
        scrComplete_contBG_anim_width = lv.anim_t()
        scrComplete_contBG_anim_width.init()
        scrComplete_contBG_anim_width.set_var(scrComplete_contBG)
        scrComplete_contBG_anim_width.set_time(200)
        scrComplete_contBG_anim_width.set_delay(0)
        scrComplete_contBG_anim_width.set_custom_exec_cb(lambda e,val: anim_width_cb(scrComplete_contBG,val))
        scrComplete_contBG_anim_width.set_values(scrComplete_contBG.get_width(), 800)
        scrComplete_contBG_anim_width.set_path_cb(lv.anim_t.path_ease_in)
        scrComplete_contBG_anim_width.set_repeat_count(0)
        scrComplete_contBG_anim_width.set_repeat_delay(0)
        scrComplete_contBG_anim_width.set_playback_time(0)
        scrComplete_contBG_anim_width.set_playback_delay(0)
        scrComplete_contBG_anim_width.start()
        #Write animation: scrComplete_contBG height
        scrComplete_contBG_anim_height = lv.anim_t()
        scrComplete_contBG_anim_height.init()
        scrComplete_contBG_anim_height.set_var(scrComplete_contBG)
        scrComplete_contBG_anim_height.set_time(200)
        scrComplete_contBG_anim_height.set_delay(0)
        scrComplete_contBG_anim_height.set_custom_exec_cb(lambda e,val: anim_height_cb(scrComplete_contBG,val))
        scrComplete_contBG_anim_height.set_values(scrComplete_contBG.get_height(), 105)
        scrComplete_contBG_anim_height.set_path_cb(lv.anim_t.path_ease_in)
        scrComplete_contBG_anim_height.set_repeat_count(0)
        scrComplete_contBG_anim_height.set_repeat_delay(0)
        scrComplete_contBG_anim_height.set_playback_time(0)
        scrComplete_contBG_anim_height.set_playback_delay(0)
        scrComplete_contBG_anim_height.start()
scrComplete_btnNext.add_event_cb(lambda e: scrComplete_btnNext_event_handler(e), lv.EVENT.ALL, None)

def scrComplete_btnBack_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.CLICKED):
        pass
        lv.scr_load_anim(scrHome, lv.SCR_LOAD_ANIM.FADE_ON, 200, 200, False)
        #Write animation: scrComplete_contBG width
        scrComplete_contBG_anim_width = lv.anim_t()
        scrComplete_contBG_anim_width.init()
        scrComplete_contBG_anim_width.set_var(scrComplete_contBG)
        scrComplete_contBG_anim_width.set_time(200)
        scrComplete_contBG_anim_width.set_delay(0)
        scrComplete_contBG_anim_width.set_custom_exec_cb(lambda e,val: anim_width_cb(scrComplete_contBG,val))
        scrComplete_contBG_anim_width.set_values(scrComplete_contBG.get_width(), 800)
        scrComplete_contBG_anim_width.set_path_cb(lv.anim_t.path_ease_in)
        scrComplete_contBG_anim_width.set_repeat_count(0)
        scrComplete_contBG_anim_width.set_repeat_delay(0)
        scrComplete_contBG_anim_width.set_playback_time(0)
        scrComplete_contBG_anim_width.set_playback_delay(0)
        scrComplete_contBG_anim_width.start()
        #Write animation: scrComplete_contBG height
        scrComplete_contBG_anim_height = lv.anim_t()
        scrComplete_contBG_anim_height.init()
        scrComplete_contBG_anim_height.set_var(scrComplete_contBG)
        scrComplete_contBG_anim_height.set_time(200)
        scrComplete_contBG_anim_height.set_delay(0)
        scrComplete_contBG_anim_height.set_custom_exec_cb(lambda e,val: anim_height_cb(scrComplete_contBG,val))
        scrComplete_contBG_anim_height.set_values(scrComplete_contBG.get_height(), 105)
        scrComplete_contBG_anim_height.set_path_cb(lv.anim_t.path_ease_in)
        scrComplete_contBG_anim_height.set_repeat_count(0)
        scrComplete_contBG_anim_height.set_repeat_delay(0)
        scrComplete_contBG_anim_height.set_playback_time(0)
        scrComplete_contBG_anim_height.set_playback_delay(0)
        scrComplete_contBG_anim_height.start()
scrComplete_btnBack.add_event_cb(lambda e: scrComplete_btnBack_event_handler(e), lv.EVENT.ALL, None)

def scrLoader_event_handler(e):
    code = e.get_code()
    if (code == lv.EVENT.SCREEN_LOADED):
        pass
        scrLoader_arcLoader_load = lv.anim_t()
        scrLoader_arcLoader_load.init()
        scrLoader_arcLoader_load.set_var(scrLoader_arcLoader)
        scrLoader_arcLoader_load.set_time(2000)
        scrLoader_arcLoader_load.set_delay(100)
        scrLoader_arcLoader_load.set_custom_exec_cb(lambda e,val: scrLoader_arcLoader.set_end_angle(val))
        scrLoader_arcLoader_load.set_values(0, 360)
        scrLoader_arcLoader_load.set_repeat_count(0)
        scrLoader_arcLoader_load.start()
        
        scrLoader_tpLoader_load = lv.anim_t()
        scrLoader_tpLoader_load.set_var(scrLoader_tpLoader)
        scrLoader_tpLoader_load.set_time(100)
        scrLoader_tpLoader_load.set_delay(100)
        scrLoader_tpLoader_load.set_custom_exec_cb(lambda e,val: scrLoader_tpLoader.set_value(val))
        scrLoader_tpLoader_load.set_values(0, 100)
        scrLoader_tpLoader_load.set_repeat_count(0)
        scrLoader_tpLoader_load.start()

scrLoader.add_event_cb(lambda e: scrLoader_event_handler(e), lv.EVENT.ALL, None)

# content from custom.py

# Load the default screen
lv.scr_load(scrHome)

while SDL.check():
    time.sleep_ms(5)

