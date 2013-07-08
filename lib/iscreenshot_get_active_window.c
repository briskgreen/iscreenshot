#include "iscreenshot_get_active_window.h"

void set_size(int *x,int *y,int *width,int *height,int _width,int _height)
{
	if(*x < 0)
	{
		*width += *x;
		*x = 0;
	}

	if(*x + *width > _width)
		*width = *x + *width - _width;

	if(*y + *height > _height)
		*height = *y + *height - _height;
}

GdkPixbuf *iscreenshot_get_active_window(time_t t)
{
	//GdkPixbuf *pixbuf=malloc(sizeof(GdkPixbuf));
	GdkPixbuf *pixbuf;
	GdkScreen *screen;
	GdkWindow *win;
	int width;
	int height;
	int _height;
	int _width;
	int x,y;
	int _x,_y;

	if(sleep(t) == -1)
		error_quit("Sleep");

	gtk_init(NULL,NULL);

	screen=gdk_screen_get_default();
	_width=gdk_screen_get_width(screen);
	_height=gdk_screen_get_height(screen);
	win=gdk_screen_get_active_window(screen);
	width=gdk_window_get_width(win);
	height=gdk_window_get_height(win);

	gdk_window_get_root_origin(win,&x,&y);
	gdk_window_get_position(win,&_x,&_y);

	width+=_x*2;
	height+=_y+_x;
	set_size(&x,&y,&width,&height,_width,_height);

	pixbuf=gdk_pixbuf_get_from_drawable(NULL,
			gdk_get_default_root_window(),NULL,
			x,y,0,0,
			width,height);

	return pixbuf;
}
