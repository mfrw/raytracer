#ifndef LIGHT_H
#define LIGHT_H

#include "vect.h"
#include "color.h"

class light {
	vect position;
	color c;
	public:
	light();
	light(vect v, color c);

	vect getlight_pos() {return position;}
	color getligt_col() {return c;}
};

light::light(void) {
	position = vect(0,0,0);
	c = color(1, 1, 1, 0);
}
light::light(vect v, color col) {
	position = v;
	c = col;
}
#endif


