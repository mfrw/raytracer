


ray : raytracer.o
	g++ -O3 raytracer.o -o ray

raytracer.o : raytracer.cpp vect.h ray.h camera.h color.h light.h plane.h sphere.h object.h
	g++ -O3 -c raytracer.cpp
clean:
	rm -f ray *.o
