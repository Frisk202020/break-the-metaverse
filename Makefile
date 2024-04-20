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
	- find . -maxdepth 1 -executable -type f \( ! -name "Makefile" \) -delete

country: 
	$(CC) $(CFLAGS) -o country src/country.c src/firewall.c $(LDFLAGS)
tuto_firewall: 
	$(CC) $(CFLAGS) -o tuto_firewall src/tuto_firewall.c src/firewall.c $(LDFLAGS)