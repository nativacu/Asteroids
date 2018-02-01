#include "Color.h"

Color::Color()
{
	red = 0.0f;
	green = 0.0f;
	blue = 0.0f;
	opacity = 0.0f;
}

Color::Color(float redV, float greenV, float blueV, float opacityV) {
	red = redV;
	green = greenV;
	blue = blueV;
	opacity = opacityV;
}

Color::~Color()
{
}

void Color::set_red(float new_Red) {
	red = new_Red;
}

void Color::set_green(float new_Green) {
	green = new_Green;
}

void Color::set_blue(float new_Blue) {
	blue = new_Blue;
}

void Color::set_opacity(float new_Opacity) {
	opacity = new_Opacity;
}

float Color::get_red(){
	return red;
}

float Color::get_green() {
	return green;
}

float Color::get_blue() {
	return blue;
}



float Color::get_opacity() {
	return opacity;
}