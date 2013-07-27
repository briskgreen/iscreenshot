#include "iscreenshot_get_active_window.h"

void set_size(int *x,int *y,int *width,int *height,int _width,int _height)
{
	if(*x < 0)
	{
		*width += *x;
		*x = 0;
	}
	/*如果活动窗口当前在根窗口的x坐标小于0
	 * 即当前活动窗口的左侧不在当前屏幕范围内
	 * 则将当前活动窗口的宽度送去相应像素并将
	 * x坐标置0
	 */
	if(*y < 0)
	{
		*height += *y;
		*y = 0;
	}
	/*与上面类似，只不过这里的情况是窗口顶部超过屏幕*/

	if(*x + *width > _width)
		*width = _width - *x;
		//*width = *x + *width - _width;
	/*如果当前活动窗口的x坐标加上当前活动窗口的宽度
	 * 大于根窗口的宽度，则将宽度设置为根窗口减去当
	 * 前活动窗口的x坐标
	 */

	if(*y + *height > _height)
		*height = _height - *y;
		//*height = *y + *height - _height;
	/*如果当前活动窗口的底部超过了屏幕
	 * 则将高度设置为根窗口的高度减去
	 * 活动窗口的y坐标
	 */
}

GdkPixbuf *iscreenshot_get_active_window(time_t t)
{
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

	width+=_x*2; //加上两边窗口边框大小
	height+=_y+_x; //加上窗口底部边框大小
	set_size(&x,&y,&width,&height,_width,_height);
	/*确定活动窗口的宽和高
	 * x 当前活动窗口在根窗口的x坐标
	 * y 当前活动窗口在根窗口的y坐标
	 * width 当前活动窗口的宽度
	 * height 当前活动窗口的高度
	 * _width 根窗口的宽度
	 * _height 根窗口的高度
	 */

	pixbuf=gdk_pixbuf_get_from_drawable(NULL,
			gdk_get_default_root_window(),NULL,
			x,y,0,0,
			width,height);

	return pixbuf;
}
