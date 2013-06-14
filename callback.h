/*iscreenshot回调函数头文件*/

#ifndef _CALLBACK_H
#define _CALLBACK_H

#include "lib/iscreenshot.h"

typedef void (*callback)(GtkWidget *widget,gpointer data);

typedef struct
{
	gboolean is_root_window;
	gboolean is_active_window;
	gboolean is_rectangle_window;
	time_t is_time;
	int is_index;
}IS_SELECT;

void really_quit(GtkWidget *widget,gpointer data);

#endif
