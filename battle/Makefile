CC = gcc
CFLAGS = -Werror -I.

.SECONDEXPANSION:
%.t.o: $$(subst obj,test,$$(subst .t.o,.c,$$@))
	$(CC) $(CFLAGS) -c $< -o $@

%.o: $$(subst obj,src,$$(subst .o,.c,$$@))
	$(CC) $(CFLAGS) -c $< -o $@

str: util/obj/str.o util/obj/str.t.o
	$(CC) $(CFLAGS) $^ -o util/dist/str