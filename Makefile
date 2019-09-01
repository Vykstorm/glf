CFLAGS = -I/usr/include/GL -Wall
LIBS = -L/usr/X11R6/lib -lglut -lGLU -lGL -lXmu -lXt -lX11 -lXi -lm
CC = libtool gcc

all: test

glf.o: glf.c
	$(CC) $(CFLAGS) -c glf.c

test: test.o glf.o
	$(CC) $(CFLAGS) test.o glf.o -o test $(LIBS)

clean:
	rm -f test
	rm -f *~
	rm -f *.o *.lo *.a *.la
	rm -rf .libs
