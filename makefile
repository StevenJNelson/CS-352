CC=gcc
CFLAGS= -g

all: output

run: output
	./output

output: main.c
	$(CC) $(CFLAGS) main.c $(FLIBS) -o output

clean:
	rm -rf *.o run output
