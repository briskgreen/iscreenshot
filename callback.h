/*iscreenshot回调函数头文件*/

#ifndef _CALLBACK_H
#define _CALLBACK_H

#include "lib/iscreenshot.h"

typedef void (*callback)(GtkWidget *widget,gpointer data);

typedef struct
{
	IS_SELECT *is_select;
	GtkWidget *select[4];
}DATA;

void really_quit(GtkWidget *widget,gpointer data);

#endif
