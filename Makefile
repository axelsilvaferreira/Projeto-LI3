CC=gcc
CFLAGS=-Wall -O2 -g
OBJS=main.o A.o

all:
	make dblp
	make cleanObj
	@echo "> make cleanAll - cleans all files created by command \"make\"."

dblp: $(OBJS)
	$(CC) $(CFLAGS) -o dblp $(OBJS)
main.o: main.c A.h A.c
	$(CC) $(CFLAGS) -c main.c
A.o: A.h A.c
	$(CC) $(CFLAGS) -c A.c

.PHONY: clean
cleanObj:
	rm *.o
	@echo "Object Files Removed"
