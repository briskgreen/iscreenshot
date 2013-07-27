#include "iscreenshot_get_rectangle_window.h"

GdkPixbuf *iscreenshot_get_rectangle_window(GdkColor *color,
		time_t t,double opacity)
{
	GtkWidget *win;
	GdkScreen *screen;
	IS_RECT data;

	gtk_init(NULL,NULL);

	if(sleep(t) == -1)
		error_quit("Sleep");

	screen=gdk_screen_get_default();
	win=gtk_window_new(GTK_WINDOW_POPUP);
	gtk_widget_set_app_paintable(win,TRUE);
	//设置当前窗口可画

	data.pressed=FALSE;
	data.opacity=opacity;
	gtk_widget_add_events(win,
			GDK_BUTTON_MOTION_MASK|GDK_BUTTON_PRESS_MASK|
			GDK_BUTTON_RELEASE_MASK);

	g_signal_connect(G_OBJECT(win),"button_press_event",
			G_CALLBACK(iscreenshot_rect_select_area_press),&data);
	g_signal_connect(G_OBJECT(win),"button_release_event",
			G_CALLBACK(iscreenshot_rect_select_area_release),
			&data);
	g_signal_connect(G_OBJECT(win),"motion_notify_event",
			G_CALLBACK(iscreenshot_rect_select_area_move),&data);

	if(color != NULL)
		gtk_widget_modify_bg(win,GTK_STATE_NORMAL,color);

	gtk_window_set_opacity(GTK_WINDOW(win),0);
	gtk_window_resize(GTK_WINDOW(win),
			gdk_screen_get_width(screen),
			gdk_screen_get_height(screen));
	//将窗口最大化并设置全透明，为得是能够侦听鼠标信号

	gdk_window_set_cursor(gdk_get_default_root_window(),
			gdk_cursor_new(GDK_CROSSHAIR));
	gdk_flush();
	//更新鼠标光标图案

	gtk_widget_show_all(win);

	gtk_main();

	usleep(10000);
	gdk_window_set_cursor(gdk_get_default_root_window(),
			gdk_cursor_new(GDK_LEFT_PTR));
	gdk_flush();
	//将光标图标还原

	return iscreenshot_rect_select_pixbuf(gdk_get_default_root_window(),&data);
}

void iscreenshot_rect_select_area_press(GtkWidget *widget,
		GdkEventButton *event,IS_RECT *data)
{
	if(data->pressed == TRUE)
		return;

	gtk_window_move(GTK_WINDOW(widget),-100,-100);
	gtk_window_resize(GTK_WINDOW(widget),10,10);
	//将窗口移动到屏幕不可见的地方
	gtk_window_set_opacity(GTK_WINDOW(widget),data->opacity);

	data->pressed=TRUE;
	data->x=event->x_root;
	data->y=event->y_root;
}

void iscreenshot_rect_select_area_release(GtkWidget *widget,
		GdkEventButton *event,IS_RECT *data)
{
	if(!data->pressed)
		return;

	data->width=ABS(data->x - event->x_root);
	data->height=ABS(data->y - event->y_root);
	data->x=MIN(data->x,event->x_root);
	data->y=MIN(data->y,event->y_root);
	data->pressed=FALSE;
	//得到鼠标当前的位置

	gtk_widget_destroy(widget);
	gtk_main_quit();
}

void iscreenshot_rect_select_area_move(GtkWidget *widget,
		GdkEventMotion *event,IS_RECT *data)
{
	GdkRectangle draw;

	if(!data->pressed)
		return;

	draw.width=ABS(data->x - event->x_root);
	draw.height=ABS(data->y - event->y_root);
	draw.x=MIN(data->x,event->x_root);
	draw.y=MIN(data->y,event->y_root);

	if(draw.width <= 0 || draw.height <= 0)
	{
		gtk_window_move(GTK_WINDOW(widget),-100,-100);
		gtk_window_resize(GTK_WINDOW(widget),10,10);

		return;
	}

	gtk_window_move(GTK_WINDOW(widget),draw.x,draw.y);
	gtk_window_resize(GTK_WINDOW(widget),draw.width,draw.height);
	//将窗口移动到相应位置并画出来
}

GdkPixbuf *iscreenshot_rect_select_pixbuf(GdkWindow *root,IS_RECT *data)
{
	//GdkPixbuf *pixbuf=malloc(sizeof(GdkPixbuf));
	GdkPixbuf *pixbuf;

	pixbuf=gdk_pixbuf_get_from_drawable(NULL,root,NULL,
			data->x,data->y,0,0,
			data->width,data->height);

	return pixbuf;
}
