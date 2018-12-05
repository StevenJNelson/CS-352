CC=gcc
CFLAGS= -g

all: output

run: output
	./output

output: edwarddj_nelsonsj.c
	$(CC) $(CFLAGS) edwarddj_nelsonsj.c $(FLIBS) -o output

clean:
	rm -rf *.o run output
