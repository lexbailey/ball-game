LIBS = -lGL

all: main

main: fizz

fizz: fizz.o fizz-collisions.o fizz-objects.o fizz-world.o vector3.o colours.o glDrawFuncs.o

	
%.o: %.c %.h
	gcc -c -o $@ $<

.PHONY: clean
clean: 
	rm -f *.o
