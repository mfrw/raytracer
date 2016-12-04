#ifndef VECT_H
#define VECT_H

#include <math.h>

class vect {
	double x, y, z;

	public:

	vect();
	vect(double i, double j, double k);

	double getvectx() {return x;}
	double getvecty() {return y;}
	double getvectz() {return z;}

	double magnitude() {
		return sqrt((x*x) + (y*y) + (z*z));
	}
	vect normalize() {
		double magnitude = sqrt((x*x)+(y*y)+(z*z));
		return vect(x/magnitude, y/magnitude, z/magnitude);
	}
	vect negative() {
		return vect(-x, -y, -z);
	}

	double dot_product(vect v) {
		return x*v.getvectx() + y*v.getvecty() + z*v.getvectz();
	}

	vect cross_product(vect v) {
		return vect(y*v.getvectz() - z*v.getvecty(), z*v.getvectx() - x*v.getvectz(), x*v.getvecty() - y*v.getvectx());
	}

	vect vect_add(vect v) {
		return vect( x+v.getvectx(), y+getvecty(), z+getvectz());
	}

	vect vect_mult(double scalar) {
		return vect(x*scalar, y*scalar, z*scalar);
	}

};

vect::vect(void) {
}

vect::vect (double i, double j, double k) {
	x = i; y = j; z = k;
}



#endif

