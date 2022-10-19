#compiler
GCC = gcc
#output file
LFLAGS = -o
#binary file directory
BIN = ../bin
#source file directory
SRC = ../src
#object file directory
OBJ = ../obj
#header file directory
HDR = ../header

#compile all source file
all: buildserver buildclient search

buildserver: $(OBJ)/smain.o  
  	$(GCC) $(LFLAGS) $(BIN)/server $(OBJ)/smain.o  $(HDR)/sheader.h
  
buildclient: $(OBJ)/cmain.o
	$(GCC) $(LFLAGS) $(BIN)/client $(OBJ)/cmain.o $(HDR)/cheader.h

$(OBJ)/smain.o: $(SRC)/smain.c
	$(GCC) -c $(LFLAGS) $(OBJ)/smain.o $(SRC)/smain.c

$(OBJ)/cmain.o: $(SRC)/cmain.c
	$(GCC) -c $(LFLAGS) $(OBJ)/cmain.o  $(SRC)/cmain.c

search: $(SRC)/search_main.c
	$(GCC) -c $(LFLAGS) $(SRC)/search_main.c
