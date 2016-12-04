#ifndef RAY_H
#define RAY_H

#include "vect.h"

class ray{
	vect origin, direction;

	public:

	ray() {
		origin = vect(0, 0, 0);
		direction = vect(1, 0, 0);
	}

	ray(vect o, vect d) {
		origin = o;
		direction = d;
	}

	vect getray_origin() {return origin;}
	vect getray_direction() {return direction;}
};



#endif
