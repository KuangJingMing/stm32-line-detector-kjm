#ifndef GUI_FS_H__
#define GUI_FS_H__

#include "gui_guider.h"

#include "ff.h"

void delete_from_fatfs(int log_index);
void save_to_fatfs(const char *log_text);
void load_from_fatfs(lv_ui *ui);
FRESULT init_fatfs(void);

#endif
