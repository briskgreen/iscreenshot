/*得到屏幕矩形截图库头文件*/

#ifndef _ISCREENSHOT_GET_RECTANGLE_WINDOW_H
#define _ISCREENSHOT_GET_RECTANGLE_WINDOW_H

#include <stdlib.h>
#include <gtk/gtk.h>
#include <time.h>

typedef struct
{
	int x;
	int y;
	int width;
	int height;
	double opacity;
	gboolean pressed;
}IS_RECT;

GdkPixbuf *iscreenshot_get_rectangle_window(GdkColor *color,
		time_t t,double opacity);

void iscreenshot_rect_select_area_move(GtkWidget *widget,
		GdkEventMotion *event,IS_RECT *data);

void iscreenshot_rect_select_area_press(GtkWidget *widget,
		GdkEventButton *event,IS_RECT *data);

void iscreenshot_rect_select_area_release(GtkWidget *widget,
		GdkEventButton *event,IS_RECT *data);

GdkPixbuf *iscreenshot_rect_select_pixbuf(GdkWindow *root,IS_RECT *data);

#endif
