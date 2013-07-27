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
/*
 * x x坐标
 * y y坐标
 * widget 宽度
 * height 高度
 * opacity 透明度
 * pressed 鼠标左键是否按下
 */

GdkPixbuf *iscreenshot_get_rectangle_window(GdkColor *color,
		time_t t,double opacity);
/*得到矩形窗口的主函数
 * color 设置选取时的颜色
 * t 设置延迟时间
 * opacity 设置选取时的透明度
 */

void iscreenshot_rect_select_area_move(GtkWidget *widget,
		GdkEventMotion *event,IS_RECT *data);
/*鼠标移动时的动作*/

void iscreenshot_rect_select_area_press(GtkWidget *widget,
		GdkEventButton *event,IS_RECT *data);
/*鼠标左键按下时的动作*/

void iscreenshot_rect_select_area_release(GtkWidget *widget,
		GdkEventButton *event,IS_RECT *data);
/*鼠标左键松开时的动作*/

GdkPixbuf *iscreenshot_rect_select_pixbuf(GdkWindow *root,IS_RECT *data);
/*矩形选取返回内容函数*/

#endif
