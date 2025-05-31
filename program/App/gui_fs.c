/*
 * FatFS 日志管理函数实现 - 异常索引删除法
 * 需要在文件开头添加 FatFS 相关头文件
 */

#include "ff.h" // FatFS头文件
#include "gui_fs.h"
#include "custom.h"
#include "stdio.h"

#define printf(fmt, ...) do {} while (0)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Winvalid-source-encoding"

/*********************
DEFINES
*********************/
#define LOG_FILE_PATH "logs.txt"
#define MAX_LINE_LENGTH 150 // 足够容纳索引+分隔符+日志文本
#define DELETED_INDEX_MARKER 0 // 标记已删除日志的异常索引值（使用0，长度更短）

/**********************
STATIC VARIABLES
**********************/
static FATFS fs; // FatFS 文件系统对象

/**********************
EXTERNAL VARIABLES
**********************/

extern log_item_t log_items[100];
extern int log_count;
extern int next_index;
extern lv_obj_t *log_list;
extern uint8_t MAX_LOGS;

/**
@brief       初始化 FatFS（添加这个新函数）
@param       无
@retval      FR_OK: 成功, 其他: 失败
*/
FRESULT init_fatfs(void)
{
    FRESULT fr;

    printf("正在初始化FatFS...\n");

    // 只进行挂载，不尝试格式化
    fr = f_mount(&fs, "0:", 1); // "0:" 表示第一个驱动器，立即挂载

    if (fr == FR_OK)
    {
        printf("FatFS初始化成功\n");
    }
    else
    {
        printf("请检查存储设备是否正确连接和格式化\n");
    }

    return fr;
}

/**
@brief       从FatFS加载日志数据并创建UI（修复索引一致性）
@param       ui: UI 结构体指针
@retval      无
*/
void load_from_fatfs(lv_ui *ui)
{
    FIL file;
    FRESULT fr;
    char line_buffer[MAX_LINE_LENGTH];
    char *token;
    int loaded_count = 0;
    int max_loaded_index = 0;

    // 打开日志文件
    fr = f_open(&file, LOG_FILE_PATH, FA_READ);
    if (fr != FR_OK)
    {
        printf("无法打开日志文件: %s (错误代码: %d)\n", LOG_FILE_PATH, fr);
        return;
    }

    printf("开始从FatFS加载日志...\n");

    // 逐行读取文件
    while (f_gets(line_buffer, sizeof(line_buffer), &file) != NULL && loaded_count < MAX_LOGS)
    {
        // 移除行尾的换行符
        size_t len = strlen(line_buffer);
        if (len > 0 && line_buffer[len - 1] == '\n')
        {
            line_buffer[len - 1] = '\0';
        }
        if (len > 1 && line_buffer[len - 2] == '\r')
        {
            line_buffer[len - 2] = '\0';
        }

        // 跳过空行
        if (strlen(line_buffer) == 0)
            continue;

        // 解析格式: "index:log_text"
        char temp_buffer[MAX_LINE_LENGTH];
        strncpy(temp_buffer, line_buffer, sizeof(temp_buffer) - 1);
        temp_buffer[sizeof(temp_buffer) - 1] = '\0';
        
        token = strtok(temp_buffer, ":");
        if (token == NULL)
            continue;

        int index = atoi(token);
        
        // 跳过异常索引（已删除的日志）
        if (index <= 0)
        {
            // 检查是否是删除标记
            char *log_text_check = strtok(NULL, "");
            if (log_text_check != NULL && strstr(log_text_check, "DELETED") != NULL) {
                printf("跳过已删除的日志，索引: %d (DELETED)\n", index);
            } else {
                printf("跳过无效索引: %d\n", index);
            }
            continue;
        }

        // 获取日志文本部分（重新解析原始buffer，因为temp_buffer已被strtok修改）
        char *log_text = strchr(line_buffer, ':');
        if (log_text == NULL)
            continue;
        log_text++; // 跳过冒号

        // 调用带索引参数的函数，不修改next_index
        add_log_item_without_save_with_index(ui, log_text, index);

        // 记录最大索引
        if (index > max_loaded_index) {
            max_loaded_index = index;
        }

        loaded_count++;

        printf("加载日志: 索引=%d, 内容=%.30s...\n", index, log_text);
    }

    // 设置正确的next_index（最大索引+1）
    if (max_loaded_index > 0) {
        next_index = max_loaded_index + 1;
    } else {
        next_index = 1; // 如果没有加载任何日志，从1开始
    }

    // 关闭文件
    f_close(&file);

    printf("从FatFS加载完成，共加载 %d 条有效日志，下一个索引: %d\n", loaded_count, next_index);
}

/**
@brief       保存日志到FatFS（优先重用异常索引位置）- 修复索引问题
@param       log_text: 要保存的日志文本
@retval      无
*/
void save_to_fatfs(const char *log_text)
{
    FIL file;
    FRESULT fr;
    UINT bytes_written;
    char write_buffer[MAX_LINE_LENGTH];
    char line_buffer[MAX_LINE_LENGTH];
    char *token;
    FSIZE_t file_pos = 0;
    FSIZE_t line_start_pos = 0;
    bool found_deleted_slot = false;
    int current_index = next_index; // 使用当前的next_index，因为在add_log_item中已经递增了

    if (log_text == NULL)
    {
        printf("错误: 日志文本为空\n");
        return;
    }

    // 格式化要写入的内容
    snprintf(write_buffer, sizeof(write_buffer), "%d:%s\n", current_index, log_text);
    size_t new_line_length = strlen(write_buffer);

    // 先尝试以读写模式打开文件，查找可重用的异常索引位置
    fr = f_open(&file, LOG_FILE_PATH, FA_READ | FA_WRITE);
    if (fr == FR_OK)
    {
        printf("查找可重用的删除位置...\n");
        
        // 逐行读取，查找异常索引位置（标记为"0:DELETED"的行）
        while (f_gets(line_buffer, sizeof(line_buffer), &file) != NULL) {
            line_start_pos = file_pos;
            size_t original_line_length = strlen(line_buffer);
            
            // 解析索引
            char temp_buffer[MAX_LINE_LENGTH];
            strncpy(temp_buffer, line_buffer, sizeof(temp_buffer) - 1);
            temp_buffer[sizeof(temp_buffer) - 1] = '\0';
            
            token = strtok(temp_buffer, ":");
            if (token != NULL) {
                int index = atoi(token);
                char *content = strtok(NULL, "");
                
                // 找到删除标记位置（索引为0且内容包含DELETED），且新行长度不超过原行长度
                if (index == DELETED_INDEX_MARKER && content != NULL && 
                    strstr(content, "DELETED") != NULL && new_line_length <= original_line_length) {
                    found_deleted_slot = true;
                    printf("找到可重用位置，原标记: 0:DELETED，位置: %lu\n", (unsigned long)line_start_pos);
                    
                    // 定位到行开始位置
                    fr = f_lseek(&file, line_start_pos);
                    if (fr == FR_OK) {
                        // 构造新行，保持原行长度
                        char padded_buffer[MAX_LINE_LENGTH];
                        memset(padded_buffer, ' ', sizeof(padded_buffer));
                        
                        // 写入新内容
                        size_t write_len = strlen(write_buffer);
                        memcpy(padded_buffer, write_buffer, write_len);
                        
                        // 保持原行的换行符
                        if (original_line_length > 0 && line_buffer[original_line_length - 1] == '\n') {
                            if (write_buffer[write_len - 1] == '\n') {
                                // 新内容已有换行符，用空格填充到原长度
                                for (size_t i = write_len; i < original_line_length - 1; i++) {
                                    padded_buffer[i] = ' ';
                                }
                                padded_buffer[original_line_length - 1] = '\n';
                                padded_buffer[original_line_length] = '\0';
                            } else {
                                // 新内容无换行符，添加空格填充和换行符
                                for (size_t i = write_len; i < original_line_length - 1; i++) {
                                    padded_buffer[i] = ' ';
                                }
                                padded_buffer[original_line_length - 1] = '\n';
                                padded_buffer[original_line_length] = '\0';
                            }
                        } else {
                            padded_buffer[original_line_length] = '\0';
                        }
                        
                        // 写入重用位置
                        fr = f_write(&file, padded_buffer, strlen(padded_buffer), &bytes_written);
                        if (fr == FR_OK) {
                            f_sync(&file);
                            printf("日志已保存到重用位置: 索引=%d, 字节数=%u\n", current_index, bytes_written);
                        } else {
                            printf("写入重用位置失败 (错误代码: %d)\n", fr);
                        }
                    }
                    break;
                }
            }
            
            file_pos = f_tell(&file);
        }
        
        f_close(&file);
    }

    // 如果没找到可重用位置，或者读写模式打开失败，则追加到文件末尾
    if (!found_deleted_slot || fr != FR_OK)
    {
        printf("追加到文件末尾...\n");
        
        fr = f_open(&file, LOG_FILE_PATH, FA_WRITE | FA_OPEN_APPEND);
        if (fr != FR_OK)
        {
            // 如果文件不存在，创建新文件
            fr = f_open(&file, LOG_FILE_PATH, FA_WRITE | FA_CREATE_NEW);
            if (fr != FR_OK)
            {
                printf("无法创建日志文件: %s (错误代码: %d)\n", LOG_FILE_PATH, fr);
                return;
            }
        }

        // 写入文件末尾
        fr = f_write(&file, write_buffer, strlen(write_buffer), &bytes_written);
        if (fr != FR_OK)
        {
            printf("追加写入日志文件失败 (错误代码: %d)\n", fr);
        }
        else
        {
            printf("日志已追加到FatFS: 索引=%d, 字节数=%u\n", current_index, bytes_written);
        }

        f_sync(&file);
        f_close(&file);
    }
}

/**
@brief       通过修改索引为异常值来"删除"日志（改进版本）
@param       log_index: 要删除的日志索引
@retval      无
*/
void delete_from_fatfs(int log_index)
{
    FIL file;
    FRESULT fr;
    char line_buffer[MAX_LINE_LENGTH];
    char *token;
    FSIZE_t file_pos = 0;
    FSIZE_t line_start_pos = 0;
    bool found = false;
    UINT bytes_written;
    
    printf("开始标记删除日志，索引: %d\n", log_index);
    
    // 以读写模式打开文件
    fr = f_open(&file, LOG_FILE_PATH, FA_READ | FA_WRITE);
    if (fr != FR_OK) {
        printf("无法打开日志文件 (错误代码: %d)\n", fr);
        return;
    }
    
    // 逐行读取文件，查找目标日志
    while (f_gets(line_buffer, sizeof(line_buffer), &file) != NULL) {
        // 记录当前行的开始位置
        line_start_pos = file_pos;
        
        // 解析行格式获取索引
        char temp_buffer[MAX_LINE_LENGTH];
        strncpy(temp_buffer, line_buffer, sizeof(temp_buffer) - 1);
        temp_buffer[sizeof(temp_buffer) - 1] = '\0';
        
        token = strtok(temp_buffer, ":");
        if (token != NULL) {
            int current_index = atoi(token);
            
            // 找到目标日志
            if (current_index == log_index) {
                found = true;
                printf("找到目标日志，索引: %d，位置: %lu\n", log_index, (unsigned long)line_start_pos);
                
                // 定位到行开始位置
                fr = f_lseek(&file, line_start_pos);
                if (fr != FR_OK) {
                    printf("定位文件位置失败 (错误代码: %d)\n", fr);
                    break;
                }
                
                // 计算原行长度
                size_t original_len = strlen(line_buffer);
                
                // 构造删除标记，简单用"0:DELETED"覆盖，剩余空间用空格填充
                char new_line[MAX_LINE_LENGTH];
                memset(new_line, ' ', sizeof(new_line));
                new_line[0] = '0';
                new_line[1] = ':';
                new_line[2] = 'D';
                new_line[3] = 'E';
                new_line[4] = 'L';
                new_line[5] = 'E';
                new_line[6] = 'T';
                new_line[7] = 'E';
                new_line[8] = 'D';
                
                // 保持原行的换行符
                if (original_len > 0) {
                    if (line_buffer[original_len - 1] == '\n') {
                        new_line[original_len - 1] = '\n';
                        new_line[original_len] = '\0';
                    } else {
                        new_line[original_len] = '\0';
                    }
                } else {
                    new_line[9] = '\n';
                    new_line[10] = '\0';
                }
                
                // 写入修改后的行
                fr = f_write(&file, new_line, strlen(new_line), &bytes_written);
                if (fr == FR_OK) {
                    f_sync(&file);
                    printf("成功标记删除日志，索引 %d -> 0 (DELETED)\n", log_index);
                } else {
                    printf("写入修改失败 (错误代码: %d)\n", fr);
                }
                break;
            }
        }
        
        // 更新文件位置
        file_pos = f_tell(&file);
    }
    
    f_close(&file);
    
    if (!found) {
        printf("未找到索引为 %d 的日志\n", log_index);
    }
}



/**
@brief       清空所有日志文件（可选的辅助函数）
@param       无
@retval      无
*/
void clear_all_logs_fatfs(void)
{
    FRESULT fr;

    fr = f_unlink(LOG_FILE_PATH);
    if (fr == FR_OK)
    {
        printf("已清空FatFS中的所有日志\n");
    }
    else if (fr == FR_NO_FILE)
    {
        printf("日志文件不存在，无需清空\n");
    }
    else
    {
        printf("清空日志文件失败 (错误代码: %d)\n", fr);
    }
}

/**
@brief       获取FatFS中的有效日志数量（修改版本，排除已删除日志）
@param       无
@retval      日志数量，-1表示错误
*/
int get_fatfs_log_count(void)
{
    FIL file;
    FRESULT fr;
    char line_buffer[MAX_LINE_LENGTH];
    char *token;
    int count = 0;

    fr = f_open(&file, LOG_FILE_PATH, FA_READ);
    if (fr != FR_OK)
    {
        return -1;
    }

    while (f_gets(line_buffer, sizeof(line_buffer), &file) != NULL)
    {
        if (strlen(line_buffer) > 0 && strchr(line_buffer, ':') != NULL)
        {
            // 解析索引，只计算有效日志
            char temp_buffer[MAX_LINE_LENGTH];
            strncpy(temp_buffer, line_buffer, sizeof(temp_buffer) - 1);
            temp_buffer[sizeof(temp_buffer) - 1] = '\0';
            
            token = strtok(temp_buffer, ":");
            if (token != NULL) {
                int index = atoi(token);
                char *content = strtok(NULL, "");
                
                // 只计算有效日志（排除删除标记"0:DELETED"）
                if (index > 0 && !(index == DELETED_INDEX_MARKER && content != NULL && strstr(content, "DELETED") != NULL)) {
                    count++;
                }
            }
        }
    }

    f_close(&file);
    return count;
}

#pragma GCC diagnostic pop