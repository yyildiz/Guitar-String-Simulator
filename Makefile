all: GuitarHero

GuitarHero: GuitarHero.o GuitarString.o RingBuffer.o
	g++ GuitarHero.o GuitarString.o RingBuffer.o -o GuitarHero -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window


RingBuffer.o: RingBuffer.cpp
	g++ -g -c RingBuffer.cpp -Wall -ansi -pedantic

GuitarString.o: GuitarString.cpp
	g++ -g -c GuitarString.cpp -Wall -ansi -pedantic -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window

GuitarHero.o: GuitarHero.cpp
	g++ -g -c GuitarHero.cpp -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window

clean:
	rm *.o GuitarHero
