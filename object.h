#ifndef OBJ_H
#define OBJ_H

#include <math.h>
#include "vect.h"
#include "color.h"

class object {
	public:
	object(void);

	color getobject_col() {return color(0,0,0,0);}

	double find_int(ray r) {
		return 0;
	}

};

object::object(void){
}

#endif
