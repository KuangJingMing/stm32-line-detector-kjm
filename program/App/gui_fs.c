/*
 * FatFS ��־������ʵ�� - �쳣����ɾ����
 * ��Ҫ���ļ���ͷ��� FatFS ���ͷ�ļ�
 */

#include "ff.h" // FatFSͷ�ļ�
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
#define MAX_LINE_LENGTH 150 // �㹻��������+�ָ���+��־�ı�
#define DELETED_INDEX_MARKER 0 // �����ɾ����־���쳣����ֵ��ʹ��0�����ȸ��̣�

/**********************
STATIC VARIABLES
**********************/
static FATFS fs; // FatFS �ļ�ϵͳ����

/**********************
EXTERNAL VARIABLES
**********************/

extern log_item_t log_items[100];
extern int log_count;
extern int next_index;
extern lv_obj_t *log_list;
extern uint8_t MAX_LOGS;

/**
@brief       ��ʼ�� FatFS���������º�����
@param       ��
@retval      FR_OK: �ɹ�, ����: ʧ��
*/
FRESULT init_fatfs(void)
{
    FRESULT fr;

    printf("���ڳ�ʼ��FatFS...\n");

    // ֻ���й��أ������Ը�ʽ��
    fr = f_mount(&fs, "0:", 1); // "0:" ��ʾ��һ������������������

    if (fr == FR_OK)
    {
        printf("FatFS��ʼ���ɹ�\n");
    }
    else
    {
        printf("����洢�豸�Ƿ���ȷ���Ӻ͸�ʽ��\n");
    }

    return fr;
}

/**
@brief       ��FatFS������־���ݲ�����UI���޸�����һ���ԣ�
@param       ui: UI �ṹ��ָ��
@retval      ��
*/
void load_from_fatfs(lv_ui *ui)
{
    FIL file;
    FRESULT fr;
    char line_buffer[MAX_LINE_LENGTH];
    char *token;
    int loaded_count = 0;
    int max_loaded_index = 0;

    // ����־�ļ�
    fr = f_open(&file, LOG_FILE_PATH, FA_READ);
    if (fr != FR_OK)
    {
        printf("�޷�����־�ļ�: %s (�������: %d)\n", LOG_FILE_PATH, fr);
        return;
    }

    printf("��ʼ��FatFS������־...\n");

    // ���ж�ȡ�ļ�
    while (f_gets(line_buffer, sizeof(line_buffer), &file) != NULL && loaded_count < MAX_LOGS)
    {
        // �Ƴ���β�Ļ��з�
        size_t len = strlen(line_buffer);
        if (len > 0 && line_buffer[len - 1] == '\n')
        {
            line_buffer[len - 1] = '\0';
        }
        if (len > 1 && line_buffer[len - 2] == '\r')
        {
            line_buffer[len - 2] = '\0';
        }

        // ��������
        if (strlen(line_buffer) == 0)
            continue;

        // ������ʽ: "index:log_text"
        char temp_buffer[MAX_LINE_LENGTH];
        strncpy(temp_buffer, line_buffer, sizeof(temp_buffer) - 1);
        temp_buffer[sizeof(temp_buffer) - 1] = '\0';
        
        token = strtok(temp_buffer, ":");
        if (token == NULL)
            continue;

        int index = atoi(token);
        
        // �����쳣��������ɾ������־��
        if (index <= 0)
        {
            // ����Ƿ���ɾ�����
            char *log_text_check = strtok(NULL, "");
            if (log_text_check != NULL && strstr(log_text_check, "DELETED") != NULL) {
                printf("������ɾ������־������: %d (DELETED)\n", index);
            } else {
                printf("������Ч����: %d\n", index);
            }
            continue;
        }

        // ��ȡ��־�ı����֣����½���ԭʼbuffer����Ϊtemp_buffer�ѱ�strtok�޸ģ�
        char *log_text = strchr(line_buffer, ':');
        if (log_text == NULL)
            continue;
        log_text++; // ����ð��

        // ���ô����������ĺ��������޸�next_index
        add_log_item_without_save_with_index(ui, log_text, index);

        // ��¼�������
        if (index > max_loaded_index) {
            max_loaded_index = index;
        }

        loaded_count++;

        printf("������־: ����=%d, ����=%.30s...\n", index, log_text);
    }

    // ������ȷ��next_index���������+1��
    if (max_loaded_index > 0) {
        next_index = max_loaded_index + 1;
    } else {
        next_index = 1; // ���û�м����κ���־����1��ʼ
    }

    // �ر��ļ�
    f_close(&file);

    printf("��FatFS������ɣ������� %d ����Ч��־����һ������: %d\n", loaded_count, next_index);
}

/**
@brief       ������־��FatFS�����������쳣����λ�ã�- �޸���������
@param       log_text: Ҫ�������־�ı�
@retval      ��
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
    int current_index = next_index; // ʹ�õ�ǰ��next_index����Ϊ��add_log_item���Ѿ�������

    if (log_text == NULL)
    {
        printf("����: ��־�ı�Ϊ��\n");
        return;
    }

    // ��ʽ��Ҫд�������
    snprintf(write_buffer, sizeof(write_buffer), "%d:%s\n", current_index, log_text);
    size_t new_line_length = strlen(write_buffer);

    // �ȳ����Զ�дģʽ���ļ������ҿ����õ��쳣����λ��
    fr = f_open(&file, LOG_FILE_PATH, FA_READ | FA_WRITE);
    if (fr == FR_OK)
    {
        printf("���ҿ����õ�ɾ��λ��...\n");
        
        // ���ж�ȡ�������쳣����λ�ã����Ϊ"0:DELETED"���У�
        while (f_gets(line_buffer, sizeof(line_buffer), &file) != NULL) {
            line_start_pos = file_pos;
            size_t original_line_length = strlen(line_buffer);
            
            // ��������
            char temp_buffer[MAX_LINE_LENGTH];
            strncpy(temp_buffer, line_buffer, sizeof(temp_buffer) - 1);
            temp_buffer[sizeof(temp_buffer) - 1] = '\0';
            
            token = strtok(temp_buffer, ":");
            if (token != NULL) {
                int index = atoi(token);
                char *content = strtok(NULL, "");
                
                // �ҵ�ɾ�����λ�ã�����Ϊ0�����ݰ���DELETED���������г��Ȳ�����ԭ�г���
                if (index == DELETED_INDEX_MARKER && content != NULL && 
                    strstr(content, "DELETED") != NULL && new_line_length <= original_line_length) {
                    found_deleted_slot = true;
                    printf("�ҵ�������λ�ã�ԭ���: 0:DELETED��λ��: %lu\n", (unsigned long)line_start_pos);
                    
                    // ��λ���п�ʼλ��
                    fr = f_lseek(&file, line_start_pos);
                    if (fr == FR_OK) {
                        // �������У�����ԭ�г���
                        char padded_buffer[MAX_LINE_LENGTH];
                        memset(padded_buffer, ' ', sizeof(padded_buffer));
                        
                        // д��������
                        size_t write_len = strlen(write_buffer);
                        memcpy(padded_buffer, write_buffer, write_len);
                        
                        // ����ԭ�еĻ��з�
                        if (original_line_length > 0 && line_buffer[original_line_length - 1] == '\n') {
                            if (write_buffer[write_len - 1] == '\n') {
                                // ���������л��з����ÿո���䵽ԭ����
                                for (size_t i = write_len; i < original_line_length - 1; i++) {
                                    padded_buffer[i] = ' ';
                                }
                                padded_buffer[original_line_length - 1] = '\n';
                                padded_buffer[original_line_length] = '\0';
                            } else {
                                // �������޻��з�����ӿո����ͻ��з�
                                for (size_t i = write_len; i < original_line_length - 1; i++) {
                                    padded_buffer[i] = ' ';
                                }
                                padded_buffer[original_line_length - 1] = '\n';
                                padded_buffer[original_line_length] = '\0';
                            }
                        } else {
                            padded_buffer[original_line_length] = '\0';
                        }
                        
                        // д������λ��
                        fr = f_write(&file, padded_buffer, strlen(padded_buffer), &bytes_written);
                        if (fr == FR_OK) {
                            f_sync(&file);
                            printf("��־�ѱ��浽����λ��: ����=%d, �ֽ���=%u\n", current_index, bytes_written);
                        } else {
                            printf("д������λ��ʧ�� (�������: %d)\n", fr);
                        }
                    }
                    break;
                }
            }
            
            file_pos = f_tell(&file);
        }
        
        f_close(&file);
    }

    // ���û�ҵ�������λ�ã����߶�дģʽ��ʧ�ܣ���׷�ӵ��ļ�ĩβ
    if (!found_deleted_slot || fr != FR_OK)
    {
        printf("׷�ӵ��ļ�ĩβ...\n");
        
        fr = f_open(&file, LOG_FILE_PATH, FA_WRITE | FA_OPEN_APPEND);
        if (fr != FR_OK)
        {
            // ����ļ������ڣ��������ļ�
            fr = f_open(&file, LOG_FILE_PATH, FA_WRITE | FA_CREATE_NEW);
            if (fr != FR_OK)
            {
                printf("�޷�������־�ļ�: %s (�������: %d)\n", LOG_FILE_PATH, fr);
                return;
            }
        }

        // д���ļ�ĩβ
        fr = f_write(&file, write_buffer, strlen(write_buffer), &bytes_written);
        if (fr != FR_OK)
        {
            printf("׷��д����־�ļ�ʧ�� (�������: %d)\n", fr);
        }
        else
        {
            printf("��־��׷�ӵ�FatFS: ����=%d, �ֽ���=%u\n", current_index, bytes_written);
        }

        f_sync(&file);
        f_close(&file);
    }
}

/**
@brief       ͨ���޸�����Ϊ�쳣ֵ��"ɾ��"��־���Ľ��汾��
@param       log_index: Ҫɾ������־����
@retval      ��
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
    
    printf("��ʼ���ɾ����־������: %d\n", log_index);
    
    // �Զ�дģʽ���ļ�
    fr = f_open(&file, LOG_FILE_PATH, FA_READ | FA_WRITE);
    if (fr != FR_OK) {
        printf("�޷�����־�ļ� (�������: %d)\n", fr);
        return;
    }
    
    // ���ж�ȡ�ļ�������Ŀ����־
    while (f_gets(line_buffer, sizeof(line_buffer), &file) != NULL) {
        // ��¼��ǰ�еĿ�ʼλ��
        line_start_pos = file_pos;
        
        // �����и�ʽ��ȡ����
        char temp_buffer[MAX_LINE_LENGTH];
        strncpy(temp_buffer, line_buffer, sizeof(temp_buffer) - 1);
        temp_buffer[sizeof(temp_buffer) - 1] = '\0';
        
        token = strtok(temp_buffer, ":");
        if (token != NULL) {
            int current_index = atoi(token);
            
            // �ҵ�Ŀ����־
            if (current_index == log_index) {
                found = true;
                printf("�ҵ�Ŀ����־������: %d��λ��: %lu\n", log_index, (unsigned long)line_start_pos);
                
                // ��λ���п�ʼλ��
                fr = f_lseek(&file, line_start_pos);
                if (fr != FR_OK) {
                    printf("��λ�ļ�λ��ʧ�� (�������: %d)\n", fr);
                    break;
                }
                
                // ����ԭ�г���
                size_t original_len = strlen(line_buffer);
                
                // ����ɾ����ǣ�����"0:DELETED"���ǣ�ʣ��ռ��ÿո����
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
                
                // ����ԭ�еĻ��з�
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
                
                // д���޸ĺ����
                fr = f_write(&file, new_line, strlen(new_line), &bytes_written);
                if (fr == FR_OK) {
                    f_sync(&file);
                    printf("�ɹ����ɾ����־������ %d -> 0 (DELETED)\n", log_index);
                } else {
                    printf("д���޸�ʧ�� (�������: %d)\n", fr);
                }
                break;
            }
        }
        
        // �����ļ�λ��
        file_pos = f_tell(&file);
    }
    
    f_close(&file);
    
    if (!found) {
        printf("δ�ҵ�����Ϊ %d ����־\n", log_index);
    }
}



/**
@brief       ���������־�ļ�����ѡ�ĸ���������
@param       ��
@retval      ��
*/
void clear_all_logs_fatfs(void)
{
    FRESULT fr;

    fr = f_unlink(LOG_FILE_PATH);
    if (fr == FR_OK)
    {
        printf("�����FatFS�е�������־\n");
    }
    else if (fr == FR_NO_FILE)
    {
        printf("��־�ļ������ڣ��������\n");
    }
    else
    {
        printf("�����־�ļ�ʧ�� (�������: %d)\n", fr);
    }
}

/**
@brief       ��ȡFatFS�е���Ч��־�������޸İ汾���ų���ɾ����־��
@param       ��
@retval      ��־������-1��ʾ����
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
            // ����������ֻ������Ч��־
            char temp_buffer[MAX_LINE_LENGTH];
            strncpy(temp_buffer, line_buffer, sizeof(temp_buffer) - 1);
            temp_buffer[sizeof(temp_buffer) - 1] = '\0';
            
            token = strtok(temp_buffer, ":");
            if (token != NULL) {
                int index = atoi(token);
                char *content = strtok(NULL, "");
                
                // ֻ������Ч��־���ų�ɾ�����"0:DELETED"��
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