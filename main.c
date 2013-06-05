#include "callback.h"

void change_path(const char *path);
void init_data(IS_SELECT *is_select);
void create_title_screen(GtkWidget *vbox);

int main(int argc,char **argv)
{
	GtkWidget *win;
	GtkWidget *table;
	GtkWidget *button;
	GtkWidget *select;
	GtkWidget *combobox;
	GtkWidget *vbox;
	GtkWidget *frame;
	IS_SELECT is_select;

	change_path(argv[0]);
	init_data(&is_select);
	gtk_init(&argc,&argv);

	win=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(win),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(win),"IScreenshot");
	gtk_window_set_icon_from_file(GTK_WINDOW(win),
			"img/64x64/iscreenshot.png",NULL);
	g_signal_connect(G_OBJECT(win),"delete_event",
			G_CALLBACK(really_quit),NULL);

	vbox=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(win),vbox);

	create_title_screen(vbox);

	table=gtk_table_new(5,3,TRUE);
}

void change_path(const char *path)
{
	int len=strlen(path);
	char temp[PATH_MAX]={0};

	while(--len)
		if(path[len] == '/')
			break;

	if(len == 0)
		return;

	while(len != -1)
	{
		temp[len] = path[len];
		--len;
	}

	if(chdir(temp) == -1)
	{
		perror(temp);
		exit(-1);
	}
}

void init_data(IS_SELECT *is_select)
{
	is_select->is_root_window=FALSE;
	is_select->is_active_window=FALSE;
	is_select->is_rectangle_window=FALSE;
	is_select->is_time=0;
}

void create_title_screen(GtkWidget *vbox)
{
	GtkWidget *image;
	GtkWidget *frame;
	GtkWidget *hbox;
	GtkWidget *label;

	frame=gtk_frame_new("IScreenshot");
	image=gtk_image_new_from_file("image/iscreenshot.png");
	hbox=gtk_hbox_new(TRUE,10);
	label=gtk_label_new("Screenshot\nTake a screenshot");

	gtk_box_pack_start(GTK_BOX(hbox),image,FALSE,FALSE,0);
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
	gtk_container_add(GTK_CONTAINER(frame),hbox);
	gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,0);

	gtk_widget_show_all(frame);
}
