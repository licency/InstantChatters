server: smain.o  
  gcc ../obj/smain.o  -o ../bin/server

smain.o: ../src/smain.c
	gcc ../src/smain.c -c -Wall -o ../obj/smain.o

client: cmain.o
	gcc ../obj/cmain.o ../header/cheader.h -o ../bin/client

cmain.o: ../src/cmain.c
	gcc  ../src/cmain.c -c -Wall  -o ../obj/cmain.o
