/*获取整个屏幕库头文件*/

#ifndef _ISCREENSHOT__GET_ROOT_WINDOW_H
#define _ISCREENSHOT_GET_ROOT_WINDOW_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

GdkPixbuf *iscreenshot_get_root_window(time_t t);

#endif
