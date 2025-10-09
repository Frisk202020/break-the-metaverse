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
	g++ -Wall -std=c++20 -g Action.cpp Character.cpp main.cpp State.cpp Stats.cpp utilities.cpp -o battle