run: main
	./main

main: main.o sphere.o functions.o
	g++ -g3 -O1 -o main main.o sphere.o functions.o

%.o: %.cpp
	g++ -g3 -O1 -c -std=c++11 -o $@ $<

clean:
	rm -f *.o main