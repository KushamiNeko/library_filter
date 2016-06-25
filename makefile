#bin/main : bin/gl_helper bin/pattern_alpha
#	gcc `pkg-config --cflags gtk+-3.0 glew` \
#-o bin/main bin/gl_helper bin/pattern_alpha bin/pattern_alpha_model bin/rectangle \
#~/programming_projects/c/general/bin/general_helper \
#-lstbi -lm src/main.c `pkg-config --libs gtk+-3.0 glew`
#
#
#bin/pattern_alpha: bin/pattern_alpha_model bin/gl_helper
#	gcc `pkg-config --cflags gtk+-3.0 glew` -c src/source/pattern_alpha.c \
#`pkg-config --libs gtk+-3.0 glew` -o bin/pattern_alpha
#
#
#bin/pattern_alpha_model: bin/rectangle
#	gcc `pkg-config --cflags gtk+-3.0 glew` -c src/source/pattern_alpha_model.c -o bin/pattern_alpha_model \
#		`pkg-config --libs gtk+-3.0 glew`
#
#bin/gl_helper :
#	gcc `pkg-config --cflags glew` -c src/source/gl_helper.c \
#`pkg-config --libs glew` -o bin/gl_helper
#
#bin/rectangle:
#	gcc -c src/source/rectangle.c -o bin/rectangle

bin/main: bin/main_window bin/list_item
	gcc -O3 `pkg-config --cflags gtk+-3.0` src/main.c -fopenmp -o bin/main bin/main_window bin/list_item \
	~/programming_projects/c/general/bin/general_helper	~/programming_projects/c/general/bin/general_list \
 	`pkg-config --libs gtk+-3.0`

bin/main_window :
	gcc -O3 `pkg-config --cflags gtk+-3.0` -c src/source/main_window.c \
`pkg-config --libs gtk+-3.0` -fopenmp -o bin/main_window

bin/list_item :
	gcc -O3 `pkg-config --cflags gtk+-3.0` -c src/source/list_item.c -fopenmp \
`pkg-config --libs gtk+-3.0` -o bin/list_item

clean:
	rm -r bin/*

all:
	make clean
	make
