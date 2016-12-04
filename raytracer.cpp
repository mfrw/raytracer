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

int cur;

int main(int argc, char *argv[]) {
	cout <<"Rendering..."<< endl;

	int dpi = 72;
	int width = 640;
	int height = 480;
	int res = width*height;
	rgb_t *pixels = new rgb_t[res];

	for(int i = 0; i < width; i++) {
		for(int j = 0; j < height; j++) {
			cur = j*width + i;
			if((i > 200 && i < 440) && (j > 200 && j < 280)) {
				pixels[cur].r = 203;
				pixels[cur].g = 102;
				pixels[cur].b = 210;
			}
			else {
				pixels[cur].r = 0;
				pixels[cur].g = 0;
				pixels[cur].b = 0;
			}

		}
	}
	savebmp("scene.bmp", width, height, dpi, pixels);
	return 0;
}
