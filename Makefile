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
	$(CC) $(CFLAGS) -o result/country src/country.c src/firewall.c $(LDFLAGS)
tuto_firewall: 
	$(CC) $(CFLAGS) -o result/tuto_firewall src/tuto_firewall.c src/firewall.c $(LDFLAGS)
underdog_ip:
	$(CC) $(CFLAGS) -o result/underdog_ip src/underdog_ip.c src/translate.c $(LDFLAGS)
normal_ip:
	$(CC) $(CFLAGS) -o result/normal_ip src/normal_ip.c src/translate.c $(LDFLAGS)
adn:
	$(CC) $(CFLAGS) -o result/adn src/adn.c src/firewall.c $(LDFLAGS)
metadata:
	$(CC) $(CFLAGS) -o result/metadata src/metadata.c $(LDFLAGS)
battle:
	$(CC) $(CFLAGS) -o battle src/battle/battle.c src/battle/attack.c src/utilities.c src/battle/dragon.c src/battle/sensei.c src/battle/spirit.c src/battle/final.c $(LDFLAGS)
carnivorous: 
	$(CC) $(CFLAGS) -o result/carnivorous src/dave_firewalls/carnivorous.c src/firewall.c $(LDFLAGS)
dipper: 
	$(CC) $(CFLAGS) -o result/dipper src/dave_firewalls/dipper.c src/firewall.c $(LDFLAGS)
mabel: 
	$(CC) $(CFLAGS) -o result/mabel src/dave_firewalls/mabel.c src/firewall.c $(LDFLAGS)
boo: 
	$(CC) $(CFLAGS) -o result/boo src/dave_firewalls/boo.c src/firewall.c $(LDFLAGS)
dave: carnivorous dipper mabel boo
