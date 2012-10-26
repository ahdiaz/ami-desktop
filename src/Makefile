.PHONY : build clean

CC := gcc
CFLAGS := -Wall $(shell pkg-config --cflags glib-2.0 gtk+-3.0)
LIBS := $(shell pkg-config --libs glib-2.0 gtk+-3.0)
#LDFLAGS := $(shell pkg-config --libs glib-2.0 gtk+-3.0)

binary = ami-desktop
objects = main.o ami-desktop.o

build : $(objects)
	$(CC) -o $(binary) $(CFLAGS) $(objects) $(LIBS)

$(objects) : %.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	rm $(binary) $(objects)
