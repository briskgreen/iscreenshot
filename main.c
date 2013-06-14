#include "callback.h"

void change_path(const char *path);
void init_data(IS_SELECT *is_select);
void create_title_screen(GtkWidget *vbox);
void create_radio_button(GtkWidget *frame,IS_SELECT *is_select);
void create_select_time(GtkWidget *frame,IS_SELECT *is_select);

int main(int argc,char **argv)
{
	GtkWidget *win;
	GtkWidget *button;
	GtkWidget *vbox;
	GtkWidget *hbox;
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

	frame=gtk_frame_new("Select");
	hbox=gtk_hbox_new(FALSE,0);
	gtk_box_pack_start(GTK_BOX(vbox),frame,FALSE,FALSE,0);
	gtk_container_add(GTK_CONTAINER(frame),hbox);

	frame=gtk_frame_new("Region to capture");
	gtk_box_pack_start(GTK_BOX(hbox),frame,FALSE,FALSE,0);
	create_radio_button(frame,&is_select);

	frame=gtk_frame_new("Delay before capturing");
	gtk_box_pack_start(GTK_BOX(hbox),frame,FALSE,FALSE,0);
	create_select_time(frame,&is_select);
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
	is_select->is_index=1;
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

void create_radio_button(GtkWidget *frame,IS_SELECT *is_select)
{
	GtkWidget *radio;
	GtkWidget *vboxl
	GSlist *group;
	int i;
	const char *label[]={"Get Root Window",
	"Get Active Window",
	"Get Rectrangle Window",NULL};
	/*callback func[3]={set_get_root_window,
	set_get_active_window,
	set_get_rectangle_window};*/

	vbox=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(frame),vbox);

	radio=gtk_radio_button_new_with_label(NULL,label[0]);
	g_signal_connect(G_OBJECT(radio),"pressed",
			G_CALLBACK(set_select),is_select);
	gtk_box_pack_start(GTK_BOX(vbox),radio,FALSE,FALSE,0);

	for(i=1;label[i-1] != NULL;++i)
	{
		group=gtk_radio_button_get_group(GTK_RADIO_BUTTON(radio));
		radio=gtk_radio_button_new_with_label(group,label[i]);

		is_select->is_index=i+1;
		g_signal_connect(G_OBJECT(radio),"pressed",
				G_CALLBACK(set_select),is_select);

		gtk_box_pack_start(GTK_BOX(vbox),radio,FALSE,FALSE,0);
	}

	gtk_widget_show_all(frame);
}

void create_select_time(GtkWidget *frame,IS_SELECT *is_select)
{
	GtkWidget *hbox;
	GtkWidget *spin;
	GtkWidget *labek;

	hbox=gtk_hbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(frame),hbox,FALSE,FALSE,0);

	spin=gtk_spin_button_new_with_range(0,60,TRUE);
	gtk_box_pack_start(GTK_BOX(hbox),spin,FALSE,FALSE,0);
	label=gtk_label_new("Seconds");
	gtk_box_pack_start(GTK_BOX(hbox),label,FALSE,FALSE,0);
	g_signal_connect(G_OBJECT(spin),"value_changed",
			G_CALLBACK(set_timeout),is_select);

	gtk_widget_show_all(frame);
}
