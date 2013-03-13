CC=gcc
CFLAGS=-Wall -O2
OBJS=main.o A.o

dblp: $(OBJS)
	$(CC) $(CFLAGS) -o dblp $(OBJS)
main.o: main.c A.h A.c
	$(CC) $(CFLAGS) -c main.c
A.o: A.h A.c
	$(CC) $(CFLAGS) -c A.c