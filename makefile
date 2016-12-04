


ray : raytracer.o
	g++ -O3 raytracer.o -o ray

raytracer.o : raytracer.cpp
	g++ -O3 -c raytracer.cpp
clean:
	rm -f ray *.o
