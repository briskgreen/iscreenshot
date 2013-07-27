#include "iscreenshot_get_root_window.h"

GdkPixbuf *iscreenshot_get_root_window(time_t t)
{
	GdkPixbuf *pixbuf;
	GdkWindow *win;
	int width;
	int height;

	if(sleep(t) == -1)
		error_quit("Sleep");

	gtk_init(NULL,NULL);

	win=gdk_get_default_root_window();
	width=gdk_window_get_width(win);
	height=gdk_window_get_height(win);

	pixbuf=gdk_pixbuf_get_from_drawable(NULL,win,NULL,
			0,0,0,0,
			width,height);

	return pixbuf;
}
