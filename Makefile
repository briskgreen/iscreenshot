LIBS=`pkg-config --cflags --libs gtk+-2.0`
IS_LIBS=lib/iscreenshot.o lib/iscreenshot_get_active_window.o lib/iscreenshot_save.o lib/iscreenshot_get_rectangle_window.o lib/iscreenshot_get_root_window.o

is_select:main.o callback.o $(IS_LIBS)
	gcc -o is_select main.o callback.o $(IS_LIBS)

main.o:main.c callback.h
	gcc -c main.c $(LIBS)

callback.o:callback.c callback.h lib/iscreenshot.c 
	gcc -c callback.c $(LIBS)

lib/iscreenshot.o:lib/iscreenshot.h lib/iscreenshot.c 
	gcc -c lib/iscreenshot.c $(LIBS)

lib/iscreenshot_get_active_window.o:lib/iscreenshot_get_active_window.c 
	gcc -c lib/iscreenshot_get_active_window.c $(LIBS)

lib/iscreenshot_get_rectangle_window.o:lib/iscreenshot_get_rectangle_window.c 
	gcc -c lib/iscreenshot_get_rectangle_window.c $(LIBS)

lib/iscreenshot_get_root_window.o:lib/iscreenshot_get_root_window.c 
	gcc -c lib/iscreenshot_get_root_window.c $(LIBS)

lib/iscreenshot_save.o:lib/iscreenshot_save.c
	gcc -c lib/iscreenshot_save.c $(LIBS)

clean:
	rm is_select *.o lib/*.o
