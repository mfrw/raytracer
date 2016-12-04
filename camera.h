#ifndef CAMERA_H
#define CAMERA_H

#include "vect.h"

class camera {
	vect campos, camdir, camright, camdown;
	public:
	camera();
	camera(vect pos, vect dir, vect right, vect down) {
		campos = pos;
		camdir = dir;
		camright = right;
		camdown = down;
	}
	vect getcpos() {return campos;}
	vect getcdir() {return camdir;}
	vect getcrt() {return camright;}
	vect getcdwn() {return camdown;}
};

#endif

