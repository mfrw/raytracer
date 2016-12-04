#ifndef PLAIN_H
#define PLAIN_H

#include <math.h>
#include "object.h"
#include "vect.h"
#include "color.h"

class plane:public object {
	vect normal;
	double distance;
	color col;

	public:
	plane(void);
	plane(vect v, double r, color c);

	vect getplane_norm() {return normal;}
	double getplane_dist() {return distance;}
	color getplane_col() {return col;}

	vect getnormalat(vect point) {
		return normal;
	}

	double find_int(ray r) {
		vect ray_dir = r.getray_direction();	
		double a = ray_dir.dot_product(normal);
		if (a == 0) {
			//ray is || to plane
			return -1;
		}
		else {
			double b = normal.dot_product(r.getray_origin().vect_add(normal.vect_mult(distance).negative()));
			return -1*b/a;
		}

	}
};

plane::plane() {
	normal = vect(1,0,0);
	distance = 0.0;
	col = color(0.5, 0.5, 0.5, 0);
}

plane::plane(vect v, double r, color c) {
	normal = v;
	distance = r;
	col = c;
}



#endif
