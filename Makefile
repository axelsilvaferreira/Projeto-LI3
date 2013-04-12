CC 		= gcc
CFLAGS	= -Wall -O2 -g
OBJS 	= main.o A.o

all:
	make PARSER_LI3
	make cleanObj
	@echo "> make cleanAll - cleans all files created by command \"make\" and both \"E.txt\" \"D.txt.\" created by the program."

PARSER_LI3: $(OBJS)
	$(CC) $(CFLAGS) -o PARSER_LI3 $(OBJS)

main.o: main.c A.h A.c
	$(CC) $(CFLAGS) -c main.c

A.o: A.h A.c
	$(CC) $(CFLAGS) -c A.c
	
.PHONY: clean
cleanObj:
	rm *.o
	@echo "Object Files Removed"
cleanAll:
	rm PARSER_LI3
	rm E.txt
	rm D.txt
	@echo "All files removed by cleanAll"