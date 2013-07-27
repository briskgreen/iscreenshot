#include "callback.h"

void really_quit(GtkWidget *widget,gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *label;
	guint status;

	dialog=gtk_dialog_new();

	gtk_window_set_title(GTK_WINDOW(dialog),"Really Quit");
	gtk_window_set_icon_from_file(GTK_WINDOW(dialog),"img/64x64/quit.png",NULL);
	label=gtk_label_new("Are You Really Want To Quit Application Now?\nClick OK To Quit,Click NO To Continue!");

	gtk_box_pack_start(GTK_BOX(GTK_DIALOG(dialog)->vbox),label,
			FALSE,FALSE,5);
	gtk_widget_show(label);
	gtk_dialog_add_buttons(GTK_DIALOG(dialog),
			GTK_STOCK_NO,GTK_RESPONSE_NO,
			GTK_STOCK_OK,GTK_RESPONSE_OK,
			NULL);

	status=gtk_dialog_run(GTK_DIALOG(dialog));

	switch(status)
	{
		case GTK_RESPONSE_NO:
			break;

		case GTK_RESPONSE_OK:
			gtk_main_quit();

		default:
			break;
	}

	gtk_widget_destroy(dialog);
}

void set_get_root_window(GtkWidget *widget,gpointer data)
{
	IS_SELECT *is_select=(IS_SELECT *)data;

	is_select->is_index=1;
}

void set_get_active_window(GtkWidget *widget,gpointer data)
{
	IS_SELECT *is_select=(IS_SELECT *)data;

	is_select->is_index=2;
}

void set_get_rectangle_window(GtkWidget *widget,gpointer data)
{
	IS_SELECT *is_select=(IS_SELECT *)data;

	is_select->is_index=3;
}

void set_timeout(GtkWidget *widget,IS_SELECT *is_select)
{
	is_select->is_time=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(widget));
}

void screenshot(GtkWidget *widget,IS_SELECT *is_select)
{
	GdkPixbuf *pixbuf;
	GdkColor color;

	gtk_widget_destroy(is_select->win);
	gtk_main_quit();

	bzero(&color,sizeof(GdkColor));

	switch(is_select->is_index)
	{
		case 1:
			pixbuf=iscreenshot_get_root_window(is_select->is_time);
			break;
		case 2:
			pixbuf=iscreenshot_get_active_window(is_select->is_time);
			break;
		case 3:
			pixbuf=iscreenshot_get_rectangle_window(
					&color,is_select->is_time,0.8);
			break;
		default:
			return;
	}

	iscreenshot_save(pixbuf);
}
