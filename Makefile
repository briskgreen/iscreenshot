LIBS=`pkg-config --cflags --libs gtk+-2.0`
IS_LIBS=iscreenshot.o iscreenshot_get_active_window.o iscreenshot_save.o iscreenshot_get_rectangle_window.o iscreenshot_get_root_window.o

iscreenshot:main.o callback.o $(IS_LIBS)
	gcc -o iscreenshot main.o callback.o $(IS_LIBS) $(LIBS)

main.o:main.c callback.h
	gcc -c main.c $(LIBS)

callback.o:callback.c callback.h lib/iscreenshot.c 
	gcc -c callback.c $(LIBS)

iscreenshot.o:lib/iscreenshot.h lib/iscreenshot.c 
	gcc -c lib/iscreenshot.c $(LIBS)

iscreenshot_get_active_window.o:lib/iscreenshot_get_active_window.c 
	gcc -c lib/iscreenshot_get_active_window.c $(LIBS)

iscreenshot_get_rectangle_window.o:lib/iscreenshot_get_rectangle_window.c 
	gcc -c lib/iscreenshot_get_rectangle_window.c $(LIBS)

iscreenshot_get_root_window.o:lib/iscreenshot_get_root_window.c 
	gcc -c lib/iscreenshot_get_root_window.c $(LIBS)

iscreenshot_save.o:lib/iscreenshot_save.c
	gcc -c lib/iscreenshot_save.c $(LIBS)

clean:
	rm iscreenshot *.o

install:
	install.sh

uninstall:
	rm -rf /usr/local/iscreenshot/
