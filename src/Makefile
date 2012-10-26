.PHONY : build clean

CC := gcc
CFLAGS := -Wall $(shell pkg-config --cflags gtk+-2.0)
LIBS := $(shell pkg-config --libs gtk+-2.0)

binary = ami-desktop
objects = main.o ami-desktop.o

build : $(objects)
	$(CC) -o $(binary) $(CFLAGS) $(objects) $(LIBS)

$(objects) : %.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm $(binary) $(objects)
