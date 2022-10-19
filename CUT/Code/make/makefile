#compiler
GCC = gcc
#output file
LFLAGS = -o
#binary file directory
BIN = ../bin
#source file directory
SRC = ../src



server: smain.o  
  	gcc ../obj/smain.o  -o ../bin/server
  
client: cmain.o
	gcc ../obj/cmain.o ../header/cheader.h -o ../bin/client

smain.o: ../src/smain.c
	gcc ../src/smain.c -c -Wall -o ../obj/smain.o

cmain.o: ../src/cmain.c
	gcc  ../src/cmain.c -c -Wall  -o ../obj/cmain.o
