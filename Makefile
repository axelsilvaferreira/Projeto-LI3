CC 		= gcc
CFLAGS	= -Wall -Wextra -O2 #-pedantic -g
OBJS 	= main.o A.o


PARSER_LI3: $(OBJS)
	$(CC) $(CFLAGS) -o PARSER_LI3 $(OBJS)

main.o: main.c A.h A.c
	$(CC) $(CFLAGS) -c main.c

A.o: A.h A.c
	$(CC) $(CFLAGS) -c A.c

all:
	make PARSER_LI3
	#make clean
	#@echo "> make cleanAll - cleans all files created by command \"make\" and both \"E.txt\" \"D.txt.\" created by the program."

	
.PHONY: clean
clean:
	rm *.o
	@echo "Object Files Removed"
cleanAll:
	rm PARSER_LI3
	rm E.txt
	rm D.txt
	@echo "All files removed by cleanAll"
