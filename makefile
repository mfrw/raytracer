


ray : raytracer.o
	g++ -O3 raytracer.o

raytracer.o : raytracer.cpp
	g++ -O3 raytracer.cpp
clean:
	rm -f ray
