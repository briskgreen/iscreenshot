/*保存截图库头文件*/

#ifndef _ISCREENSHOT_SAVE_H
#define _ISCREENSHOT_SAVE_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void iscreenshot_save(GdkPixbuf *pixbuf);

void iscreenshot_save_to_file(GtkWidget *widget,GdkPixbuf *pixbuf);

void iscreenshot_save_to_clipboard(GtkWidget *widget,GdkPixbuf *pixbuf);

void iscreenshot_save_only_show(GtkWidget *widget,GdkPixbuf *pixbuf);

#endif
