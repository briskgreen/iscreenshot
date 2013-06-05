/*iscreenshot库头文件
 *定义一些全局变量和数据结构
 */

#ifndef _ISCREENSHOT_H
#define _ISCREENSHOT_H

#include "iscreenshot_get_root_window.h"
#include "iscreenshot_get_active_window.h"
#include "iscreenshot_get_rectangle_window.h"
#include "iscreenshot_save_to_file.h"
#include <gtk/gtk.h>

typedef struct
{
	gboolean is_root_window;
	gboolean is_active_window;
	gboolean is_rectangle_window;
	time_t is_time;
}IS_SELECT;

#endif