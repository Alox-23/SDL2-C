all:
	gcc -Wall -Wextra -O2 -o main main.c `sdl2-config --cflags --libs`
	./main