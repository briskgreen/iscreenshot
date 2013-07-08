#include "callback.h"

void really_quit(GtkWidget *widget,gpointer data)
{
	GtkWidget *dialog;
	GtkWidget *label;
	guint status;

	dialog=gtk_dialog_new();

	gtk_window_set_title(GTK_WINDOW(dialog),"Really Quit");
	gtk_window_set_icon_from_file("img/64x64/quit.png",NULL);
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

vois set_select(GtkWidget *widget,IS_SELECT *is_select)
{
	printf("%d\n",is_select->is_index);
}
