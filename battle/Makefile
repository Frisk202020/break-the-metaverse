_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99  -Werror $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lm

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

battle:
	$(CC) $(CFLAGS) -o main src/main.c src/attack.c src/utilities.c src/dragon.c src/sensei.c src/spirit.c src/final.c $(LDFLAGS)

clean:
	- rm -f *.o
	- find . -maxdepth 2 -executable -type f \( ! -name "Makefile" \) -delete
