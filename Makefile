CC 		= gcc
CFLAGS	= -Wall -Wextra -O2 #-pedantic -g
OBJS 	= main.o fread.o fwrite.o parser.o F.o


PARSER_LI3: $(OBJS)
	$(CC) $(CFLAGS) -o PARSER_LI3 $(OBJS)

main.o: main.c fread.h fwrite.h parser.h F.h
	$(CC) $(CFLAGS) -c main.c

fread.o: fread.h fread.c
	$(CC) $(CFLAGS) -c fread.c

fwrite.o: fwrite.h fwrite.h
	$(CC) $(CFLAGS) -c fwrite.c

parser.o: parser.h parser.c
	$(CC) $(CFLAGS) -c parser.c

F.o: F.h F.c
	$(CC) $(CFLAGS) -c F.c


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
	rm G.csv
	@echo "All files removed by cleanAll"
