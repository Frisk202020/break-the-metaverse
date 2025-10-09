_GUI = $(if $(NOGUI),,-D GUI -Werror)
_DEBUG = $(if $(DEBUG),-D DEBUG,)
_OPT = $(if $(OPT),-O3 -flto,)
CC = gcc
CFLAGS = -g -std=c99  -Werror $(_OPT) $(_GUI) $(_DEBUG) -I./include
LDFLAGS = -lm

%.o: ./src/%.c
	$(CC) $(CFLAGS) -o $@ -c $^

clean:
	- rm -f *.o
	- find . -maxdepth 2 -executable -type f \( ! -name "Makefile" \) -delete

battle:
	$(CC) $(CFLAGS) -o battle src/battle/battle.c src/battle/attack.c src/utilities.c src/battle/dragon.c src/battle/sensei.c src/battle/spirit.c src/battle/final.c $(LDFLAGS)
