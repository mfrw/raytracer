#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include "vect.h"
#include "color.h"

class sphere {
	vect center;
	double radius;
	color col;

	sphere(void);
	sphere(vect v, double r, color c);

	vect getsphere_cent() {return center;}
	double getshphere_rad() {return radius;}
	color getsphere_col() {return col;}
};

sphere::sphere() {
	center = vect(0,0,0);
	radius = 1.0;
	col = color(0.5, 0.5, 0.5, 0);
}

sphere::sphere(vect v, double r, color c) {
	center = v;
	radius = r;
	col = c;
}



#endif
