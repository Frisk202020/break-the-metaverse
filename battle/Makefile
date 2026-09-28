CC = gcc
CFLAGS = -Wall -g -O0 -I.

mod_objects = $(foreach f,$(2),$(1)/obj/$(f).o)
mod_sources = $(foreach f,$(2),$(1)/src/$(f).c)

.SECONDEXPANSION:
%.t.o: $$(subst obj,test,$$(subst .t.o,.c,$$@))
	$(CC) $(CFLAGS) -c $< -o $@

%.o: $$(subst obj,src,$$(subst .o,.c,$$@))
	$(CC) $(CFLAGS) -c $< -o $@

str_objects = str print
str: $(call mod_objects,util,$(str_objects)) util/obj/str.t.o
	$(CC) $(CFLAGS) $^ -o util/dist/str

util_all = action character_base str print
dragon_all = game_manager main server

dragon: $(call mod_objects,util,$(util_all)) $(call mod_objects,dragon,$(dragon_all))
	$(CC) $(CFLAGS) $^ -o dragon/dist/dragon