bin/main: bin/main_window bin/list_item
	gcc `pkg-config --cflags gtk+-3.0` src/main.c -fopenmp -o bin/main bin/main_window bin/list_item \
~/programming_projects/c/general/bin/general_helper	~/programming_projects/c/general/bin/general_list \
 `pkg-config --libs gtk+-3.0`

bin/main_window :
	gcc `pkg-config --cflags gtk+-3.0` -c src/main_window.c \
`pkg-config --libs gtk+-3.0` -fopenmp -o bin/main_window

bin/list_item :
	gcc `pkg-config --cflags gtk+-3.0` -c src/list_item.c -fopenmp \
`pkg-config --libs gtk+-3.0` -o bin/list_item

clean:
	if [ $(shell find 'bin' -type d -empty) ]; then\
		echo 'bin is clean';\
	else\
		echo 'cleaning bin ...';\
		rm -r bin/*;\
	fi

all:
	make clean
	make
