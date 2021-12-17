FLAGS=-Wall -g
CC=gcc
AR=ar
OBJECTS_MAIN=main.o

all: stringProg
libclassstr.a:my_string.o
	$(AR) -rcs libclassstr.a my_string.o
my_string.o: my_string.h my_string.c
	$(CC) $(FLAGS) -c my_string.c
stringProg:$(OBJECTS_MAIN) libclassstr.a
	$(CC) $(FLAGS) -o stringProg $(OBJECTS_MAIN) libclassstr.a
main.o: main.c my_string.h
	$(CC) $(FLAGS) -c main.c
.PHONY: clean all 
clean:
	rm -f stringProg *.o *.a
