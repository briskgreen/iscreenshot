iscreenshot
===========

Copyright © 2013-07 By 炕头哥

一款简单的截图工具

简介
iscreenshot使用libiscreenshot开发
libiscreenshot是使用Gtk2开发的一个简单的截图开发包
而iscreenshot作为libiscreenshot库使用的一个简单示例

许可协议
iscreenshot以及libiscreenshot都采用LGPL许可协议，具体
的许可内容请参考下面的地址
http://www.gnu.org/licenses/lgpl.html

libiscreenshot接口
libiscreenshot的接口非常简单虽然函数的名字比较长
但取其意，理解起来非常直观比如iscreenshot_get_active_window
从字面上就很容易明白它是截取当前活动窗口的函数

libiscreenshot接口列表及相关头文件
libiscreenshot有个总的头文件用来包含libiscreenshot所有需要的函数的头文件
该头文件名为iscreenshot.h

#include <lib/iscreenshot.h>
void error_quit(const char *msg);
打印错误信息并退出程序的函数，msg为附加信息

#include <lib/iscreenshot_get_root_window.h>
GdkPixbuf *iscreenshot_get_root_window(time_t t);
截取当前根窗口也就是整个屏幕的函数
t为延迟时间
返回截取的图

#include <lib/iscreenshot_get_active_window.h>
GdkPixbuf *iscreenshot_get_active_window(time_t t);
截取当前活动窗口的函数
参数t为延迟时间
返回截取的图

#include <lib/iscreenshot_get_rectangle_window.h>
typedef struct
{
	int x;
	int y;
	int width;
	int height;
	double opacity;
	gboolean pressed;
}IS_RECT;

 * x x坐标
 * y y坐标
 * widget 宽度
 * height 高度
 * opacity 透明度
 * pressed 鼠标左键是否按下


GdkPixbuf *iscreenshot_get_rectangle_window(GdkColor *color,
		time_t t,double opacity);
得到矩形窗口的主函数
color 设置选取时的颜色
t 设置延迟时间
opacity 设置选取时的透明度

#include <lib/iscreenshot_save.h>

void iscreenshot_save(GdkPixbuf *pixbuf);
保存截图主界面

void iscreenshot_save_to_file(GtkWidget *widget,GdkPixbuf *pixbuf);
保存截图到磁盘

void iscreenshot_save_to_clipboard(GtkWidget *widget,GdkPixbuf *pixbuf);
保存截图到剪贴板

void iscreenshot_save_only_show(GtkWidget *widget,GdkPixbuf *pixbuf);
只显示截图

作者:炕头哥
联系作者:briskgreen@163.com
