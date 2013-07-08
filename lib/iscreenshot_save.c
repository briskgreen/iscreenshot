#include "iscreenshot_save.h"

void iscreenshot_save(GdkPixbuf *pixbuf)
{
	GtkWidget *win;
	GtkWidget *vbox;
	GtkWidget *hbox;
	GtkWidget *box;
	GtkWidget *save_to_file;
	GtkWidget *save_to_clipboard;
	GtkWidget *cancel;
	GtkWidget *show;
	GtkWidget *image;
	GdkPixbuf *temp;

	gtk_init(NULL,NULL);

	win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(win),"IScreenShot Save");
	gtk_window_set_icon_from_file(GTK_WINDOW(win),"img/64x64/save.png",NULL);
	g_signal_connect(G_OBJECT(win),"delete_event",G_CALLBACK(gtk_main_quit),NULL);

	box=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(win),box);
	hbox=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(box),hbox,FALSE,FALSE,0);
	vbox=gtk_vbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox),vbox,FALSE,FALSE,0);

	save_to_file=gtk_button_new_with_label("Save To File");
	gtk_box_pack_start(GTK_BOX(vbox),save_to_file,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(save_to_file),"clicked",
			G_CALLBACK(iscreenshot_save_to_file),pixbuf);

	save_to_clipboard=gtk_button_new_with_label("Save To Clipboard");
	gtk_box_pack_start(GTK_BOX(vbox),save_to_clipboard,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(save_to_clipboard),"clicked",
			G_CALLBACK(iscreenshot_save_to_clipboard),pixbuf);

	show=gtk_button_new_with_label("Only Show");
	gtk_box_pack_start(GTK_BOX(vbox),show,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(show),"clicked",
			G_CALLBACK(iscreenshot_save_only_show),pixbuf);

	cancel=gtk_button_new_with_label("Cancel");
	gtk_box_pack_start(GTK_BOX(vbox),cancel,FALSE,FALSE,5);
	g_signal_connect(G_OBJECT(cancel),"clicked",
			G_CALLBACK(gtk_main_quit),NULL);

	temp=gdk_pixbuf_scale_simple(pixbuf,200,130,GDK_INTERP_BILINEAR);
	image=gtk_image_new_from_pixbuf(temp);
	gtk_box_pack_end(GTK_BOX(hbox),image,FALSE,FALSE,10);

	gtk_widget_show_all(win);
	gtk_main();
}

void iscreenshot_save_to_file(GtkWidget *widget,GdkPixbuf *pixbuf)
{
	GtkWidget *file;
	gint status;
	char *name="IScreenShot ";
	char *png=".png";
	char *file_name;
	char *temp;
	time_t t;

	t=time(NULL);
	temp=ctime(&t);
	file_name=malloc(strlen(name)+strlen(temp)+strlen(png));
	bzero(file_name,strlen(name)+strlen(temp)+strlen(png));
	strncpy(file_name,name,strlen(name));
	strncat(file_name,temp,strlen(temp)-1);
	strncat(file_name,png,strlen(png));

	file=gtk_file_chooser_dialog_new("Save File",NULL,
			GTK_FILE_CHOOSER_ACTION_SAVE,
			GTK_STOCK_CANCEL,GTK_RESPONSE_CANCEL,
			GTK_STOCK_OK,GTK_RESPONSE_OK,NULL);
	gtk_file_chooser_set_current_folder(GTK_FILE_CHOOSER(file),
			getcwd(NULL,0));
	gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER(file),file_name);
	status=gtk_dialog_run(GTK_DIALOG(file));

	switch(status)
	{
		case GTK_RESPONSE_OK:
			temp=gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file));
			gdk_pixbuf_save(pixbuf,temp,"png",NULL,
					"quality","100",NULL);
			break;
		case GTK_RESPONSE_CANCEL:
		default:
			break;
	}

	free(file_name);
	gtk_widget_destroy(file);
	gtk_main_quit();
}

void iscreenshot_save_to_clipboard(GtkWidget *widget,GdkPixbuf *pixbuf)
{
	GtkClipboard *clip;

	clip=gtk_clipboard_get(gdk_atom_intern_static_string("CLIPBOARD"));
	gtk_clipboard_clear(clip);
	gtk_clipboard_set_image(clip,pixbuf);

	gtk_main_quit();
}

void iscreenshot_save_only_show(GtkWidget *widget,GdkPixbuf *pixbuf)
{}
