CC=gcc
CFLAGS=-Wall -O2 -g
OBJS=main.o A.o

all:
	#@touch E.txt
	#@echo "touch E.txt Created"
	#@touch D.txt
	#@echo "touch D.txt Created"
	@echo "> make clean - cleans all the object files"
	@echo "> make cleanAll - cleans all files created by command \"make\"."
	make dblp
	make clean

dblp: $(OBJS)
	$(CC) $(CFLAGS) -o dblp $(OBJS)
main.o: main.c A.h A.c
	$(CC) $(CFLAGS) -c main.c
A.o: A.h A.c
	$(CC) $(CFLAGS) -c A.c

#.PHONY: clean
clean:
	rm *.o
	#@echo "Object Files Removed"