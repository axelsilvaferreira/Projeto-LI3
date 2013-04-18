CC 		= gcc
CFLAGS	= -Wall -Wextra -O2 #-pedantic -g
OBJS 	= main.o fread.o fwrite.o parser.o est_fase2.o ArrayDinamico.o TabelaHash.o


PARSER_LI3: $(OBJS)
	$(CC) $(CFLAGS) -o PARSER_LI3 $(OBJS)

main.o: main.c fread.c fwrite.c  #A.h A.c
	$(CC) $(CFLAGS) -c main.c

fread.o: fread.h fread.c
	$(CC) $(CFLAGS) -c fread.c

fwrite.o: fwrite.h fwrite.h
	$(CC) $(CFLAGS) -c fwrite.c

parser.o: parser.h parser.c
	$(CC) $(CFLAGS) -c parser.c

est_fase2.o: est_fase2.h est_fase2.c
	$(CC) $(CFLAGS) -c est_fase2.c

ArrayDinamico.o: ArrayDinamico.h

TabelaHash.o: TabelaHash.h

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
