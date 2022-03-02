# Makefile for project
#

# Basic stuff
SHELL = /bin/sh

top_srcdir = .
srcdir = .
prefix = /usr
exec_prefix = ${prefix}
bindir = $(exec_prefix)/bin
infodir = $(prefix)/info
libdir = $(prefix)/lib
mandir = $(prefix)/man/man1
includedir = $(prefix)/include

CC = gcc
# CC = g++
DEFS = -DHAVE_CONFIG_H
#CFLAGS = -g -O2 -Wall
CFLAGS =
#Флаг -g необходим для отладки!!!
#Флаг -w отключает warning!!!
# CPPFLAGS = -g
CPPFLAGS = -g -w
# Флаг линковщика -lm подключает математические функции
LDFLAGS = -v -lm
LIBS = -lm 
BASELIBS = -lm 
X11_INC = 
X11_LIB = 
# CAIRO_LIBS = $(shell pkg-config --cflags --libs cairo)
FPIC = -fPIC
SOFLAGS = -shared
# NIXDBF_LIBS = -L/home/xhermit/dev/prj/work/nixdbf/lib/ -lnixdbf

# Directories
TOPSRCDIR = .
TOPOBJDIR = .
SRCDIR    = .
# CAIRO_INCLUDEDIR = $(includedir)/cairo
# NIXDBF_INCLUDEDIR = /home/xhermit/dev/prj/work/nixdbf/include

# CPPFLAGS += $(CXX_FLAGS)
# CPPFLAGS += -I$(NIXDBF_INCLUDEDIR)
# LDFLAGS += $(NIXDBF_LIBS)


# ВНИМАНИЕ! Сначала ставиться -o <выходной файл> затем <объектные файлы> и лишь в конце <флаги линковщика>
test: test.o version.o logfunc.o strfunc.o toolfunc.o filefunc.o sllist.o
	$(CC) -o test ./obj/test.o ./obj/version.o ./obj/logfunc.o ./obj/strfunc.o ./obj/toolfunc.o ./obj/filefunc.o ./obj/sllist.o $(LDFLAGS)

main.o: ./src/main.c
	$(CC) -c  $(CFLAGS) $(CPPFLAGS) ./src/main.c
	mv main.o ./obj/main.o

test.o: ./src/test.c
	$(CC) -c  $(CFLAGS) $(CPPFLAGS) ./src/test.c
	mv test.o ./obj/test.o

version.o: ./src/version.c
	$(CC) -c  $(CFLAGS) $(CPPFLAGS) ./src/version.c
	mv version.o ./obj/version.o

logfunc.o: ./src/logfunc.c
	$(CC) -c  $(CFLAGS) $(CPPFLAGS) ./src/logfunc.c
	mv logfunc.o ./obj/logfunc.o

strfunc.o: ./src/strfunc.c
	$(CC) -c  $(CFLAGS) $(CPPFLAGS) ./src/strfunc.c
	mv strfunc.o ./obj/strfunc.o

toolfunc.o: ./src/toolfunc.c
	$(CC) -c  $(CFLAGS) $(CPPFLAGS) ./src/toolfunc.c
	mv toolfunc.o ./obj/toolfunc.o

filefunc.o: ./src/filefunc.c
	$(CC) -c  $(CFLAGS) $(CPPFLAGS) ./src/filefunc.c
	mv filefunc.o ./obj/filefunc.o

sllist.o: ./src/sllist.c
	$(CC) -c  $(CFLAGS) $(CPPFLAGS) ./src/sllist.c
	mv sllist.o ./obj/sllist.o


clean:
	rm -f ./src/*.o ./obj/*.o ./*.o gl_view test

