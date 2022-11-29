run: sphere_mc main
	./main 65536
	./sphere_mc example-data.dat

main: main.o sphere.o
	g++ -g3 -01 -o main main.o sphere.o

sphere_mc: sphere_mc.o sphere.o
	g++ -g3 -01 -o sphere_mc sphere_mc.o sphere.o

%.o: %.cpp
	g++ -g3 -O1 -c -std=c++11 -o $@ $<

clean:
	rm -f *.o sphere_mc main example-data.dat
