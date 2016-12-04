#ifndef COLOR_H
#define COLOR_H

class color {
	double red, green, blue, special;
	public:
	color() {
		red = 0.5;
		green = 0.5;
		blue = 0.5;
	}

	color(double r , double g, double b, double s) {
		red = r;
		green = g;
		blue = b;
		special = s;
	}

	double getcolor_red() {return red;}
	double getcolor_green() {return green;}
	double getcolor_blue() {return blue;}
	double getcolor_special() {return special;}

	double setcolor_red(double color) {red = color;}
	double setcolor_green(double color) {green = color;}
	double setcolor_blue(double color) {blue = color;}
	double setcolor_special(double color) {special = color;}

};

#endif
	
