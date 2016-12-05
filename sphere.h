#ifndef SPHERE_H
#define SPHERE_H

#include <math.h>
#include "object.h"
#include "vect.h"
#include "color.h"

class sphere:public object {
	vect center;
	double radius;
	color col;

	public:
	sphere(void);
	sphere(vect v, double r, color c);

	vect getsphere_cent() {return center;}
	double getshphere_rad() {return radius;}
	color getsphere_col() {return col;}

	vect getnormalat(vect point) {
		vect normal_vect = point.vect_add(center.negative()).normalize();
		return normal_vect;
	}
	double find_int(ray r) {
		vect ray_origin = r.getray_origin();
		double ray_origin_x = ray_origin.getvectx();
		double ray_origin_y = ray_origin.getvecty();
		double ray_origin_z = ray_origin.getvectz();

		vect ray_direction = r.getray_direction();
		double ray_dir_x = ray_direction.getvectx();
		double ray_dir_y = ray_direction.getvecty();
		double ray_dir_z = ray_direction.getvectz();

		vect sphere_center = center;
		double sphere_center_x = sphere_center.getvectx();
		double sphere_center_y = sphere_center.getvecty();
		double sphere_center_z = sphere_center.getvectz();

		double a = 1;
		double b = (2*(ray_origin_x - sphere_center_x) *ray_dir_x) + (2*(ray_origin_y - sphere_center_y) *ray_dir_y) + (2*(ray_origin_z - sphere_center_z) *ray_dir_z);
		double c = pow(ray_origin_x - sphere_center_x, 2) + pow(ray_origin_y - sphere_center_y, 2) + pow(ray_origin_z - sphere_center_z, 2) - radius*radius;
		
		double discriminant = b*b - 4*c;
		if(discriminant > 0) {
			// ray intersects
			// there may be two of those so do the math
			double root1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;
			if(root1 > 0) {
				// first root is the smalles positive root
				return root1;
			}
			else {
				double root2 = ((sqrt(discriminant) -b)/2) - 0.000001;
				return root2;
			}
		}
		else {
			// ray missed the sphere
			return -1;
		}
	}
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
