#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "vect.h"
#include "ray.h"
#include "camera.h"
#include "light.h"
#include "sphere.h"
#include "object.h"
#include "plane.h"

using namespace std;

struct rgb_t {
	double r, g, b;
};

void savebmp(const char *filename, int w, int h, int dpi, rgb_t *color_d) {
	FILE *f;
	int res = w*h;
	int s = 4*res;
	int fsize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = m * dpi;

	unsigned char bmp_fheader[14] = {'B', 'M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmp_iheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};
	bmp_fheader[2] = (unsigned char)(fsize);
	bmp_fheader[3] = (unsigned char)(fsize >> 8);
	bmp_fheader[4] = (unsigned char)(fsize >> 16);
	bmp_fheader[5] = (unsigned char)(fsize >> 24);

	bmp_iheader[4] = (unsigned char)(w);
	bmp_iheader[5] = (unsigned char)(w >> 8);
	bmp_iheader[6] = (unsigned char)(w >> 16);
	bmp_iheader[7] = (unsigned char)(w >> 24);

	bmp_iheader[8] = (unsigned char)(h);
	bmp_iheader[9] = (unsigned char)(h >> 8);
	bmp_iheader[10] = (unsigned char)(h >> 16);
	bmp_iheader[11] = (unsigned char)(h >> 24);

	bmp_iheader[21] = (unsigned char)(s);
	bmp_iheader[22] = (unsigned char)(s >> 8);
	bmp_iheader[23] = (unsigned char)(s >> 16);
	bmp_iheader[24] = (unsigned char)(s >> 24);

	bmp_iheader[25] = (unsigned char)(ppm);
	bmp_iheader[26] = (unsigned char)(ppm >> 8);
	bmp_iheader[27] = (unsigned char)(ppm >> 16);
	bmp_iheader[28] = (unsigned char)(ppm >> 24);

	bmp_iheader[29] = (unsigned char)(ppm);
	bmp_iheader[30] = (unsigned char)(ppm >> 8);
	bmp_iheader[31] = (unsigned char)(ppm >> 16);
	bmp_iheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");
	fwrite(bmp_fheader, 1, 14, f);
	fwrite(bmp_iheader, 1, 40, f);


	for (int i = 0; i < res; i++) {
		rgb_t rgb = color_d[i];
		double r = color_d[i].r * 255;
		double g = color_d[i].g * 255;
		double b = color_d[i].b * 255;

		unsigned char color[3] = {(int)floor(b), (int)floor(g), (int)floor(b)};
		fwrite(color, 1, 3, f);
	}
	fclose(f);
}
int winning_obj_index(vector<double> object_intersections) {
	// return the index of the winning ints
	int index_of_min_val;

	if(object_intersections.size() == 0) {
		return -1;
	}
	else if (object_intersections.size() == 1) {
		if(object_intersections.at(0) > 0)
			return 0;
		else
			return -1;
	}
	else {
		double max = 0;
		for (int i = 0; i < object_intersections.size(); i++) {
			if(max < object_intersections.at(i)) {
				max = object_intersections.at(i);
			}
		}
		if(max > 0) {
			for (int index = 0; index < object_intersections.size(); index++) {
				if((object_intersections.at(index) > 0) && (object_intersections.at(index) <= max)) {
					max = object_intersections.at(index);
					index_of_min_val = index;
				}
			}
			return index_of_min_val;
		}
		else {
			return -1;
		}
	}
}

int cur;


int main(int argc, char *argv[]) {
	cout <<"Rendering..."<< endl;

	int dpi = 72;
	int width = 640;
	int height = 480;
	double aspectratio = (double)width/(double)height;
	int res = width*height;
	rgb_t *pixels = new rgb_t[res];

	vect campos(2.0, 1.5, -4.0);


	vect o(0, 0, 0); // origin
	vect x(1, 0, 0);
	vect y(0, 1, 0);
	vect z(0 ,0, 1);
	vect look_at(0, 0, 0);
	vect new_sphere_loc(1.75, -0.25, 0);

	vect diff_btw(campos.getvectx() - look_at.getvectx(), campos.getvecty() - look_at.getvecty(), campos.getvectz() - look_at.getvectz());

	vect camdir = diff_btw.negative().normalize();
	vect camright = y.cross_product(camdir).normalize();
	vect camdown = camright.cross_product(camdir);
	camera scene_cam(campos, camdir, camright, camdown);
	color white_light(1.0, 1.0, 1.0, 0);
	color pretty_green(0.5, 1.0, 0.5, 0.3);
	color gray(0.5, 0.5, 0.5, 0);
	color black(0,0,0,0);
	color maroon(0.5, 0.25, 0.25, 0);

	vect light_position(-7, 10, -10);
	light scene_light(light_position, white_light);


	double xamnt, yamnt;
	sphere scene_sphere(o, 1, pretty_green);
	plane scene_plane(y, -1, maroon);
	vector<object*> scene_objects;
	scene_objects.push_back(dynamic_cast<object*>(&scene_plane));
	scene_objects.push_back(dynamic_cast<object*>(&scene_sphere));

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			cur = j*width + i;
			// start with no anti-aliasing
			if(width > height) {
				xamnt = ((i+0.5)/width) *aspectratio - ((width-height)/2);
				yamnt = ((height - j) + 0.5)/height;
			}
			else if(height > width) {
				xamnt = (i + 0.5)/width;
				yamnt = (((height - j) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
			}
			else {
				xamnt = (i+0.5)/width;
				yamnt = ((height - j) + 0.5)/height;
			}
			vect cam_ray_origin = scene_cam.getcpos();
			vect cam_ray_direction = camdir.vect_add(camright.vect_mult(xamnt - 0.5).vect_add(camdown.vect_mult(yamnt-0.5))).normalize();
			ray cam_ray(cam_ray_origin, cam_ray_direction);

			vector<double> intersections;
			for (int index = 0; index < scene_objects.size(); index++) {
				intersections.push_back(scene_objects.at(index)->find_int(cam_ray));
			}

			int index_of_winning_object = winning_obj_index(intersections);

			if(index_of_winning_object == -1) {
				pixels[cur].r = 0;
				pixels[cur].g = 0;
				pixels[cur].b = 0;
			}
			else {
				color this_color = scene_objects.at(index_of_winning_object)->get_col();
				pixels[cur].r = this_color.getcolor_red();
				pixels[cur].g = this_color.getcolor_green();
				pixels[cur].b = this_color.getcolor_blue();
			}

		}
	}

	savebmp("scene.bmp", width, height, dpi, pixels);
	return 0;
}
