/*获取当前活动窗口截图库头文件*/

#ifndef _ISCREENSHOT_GET_ACTIVE_WINDOW_H
#define _ISCREENSHOT_GET_ACTIVE_WINDOW_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <time.h>

GdkPixbuf *iscreenshot_get_active_window(time_t t);
/*参数t表示等候的时间*/

#endif
