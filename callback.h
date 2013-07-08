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
	GdkPixbuf *pixbuf;
}IS_SELECT;

void really_quit(GtkWidget *widget,gpointer data);

void set_select(GtkWidget *widget,IS_SELECT *is_select);

void set_timeout(GtkWidget *widget,IS_SELECT *is_select);

void screenshot(GtkWidget *widget,IS_SELECT *is_select);

#endif
