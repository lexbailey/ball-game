LIBS = -lGL -lGLU -lglut -lm

all: main

main: ballgame

ballgame: ballgame.o fizz/fizz.o fizz/fizz-collisions.o fizz/fizz-objects.o fizz/fizz-world.o fizz/vector3.o fizz/colours.o fizz/glDrawFuncs.o
	gcc -o $@ $^ ${LIBS}
	
%.o: %.c %.h
	gcc -c -o $@ $<

.PHONY: clean
clean: 
	rm -f *.o
	rm -f ballgame
