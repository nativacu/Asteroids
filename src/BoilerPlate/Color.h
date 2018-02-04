#pragma once
struct Color
{	

	//RGBA scale of colors
	float red;
	float green;
	float blue;
	float opacity;

	Color();
	Color(float red, float green, float blue, float alpha);
	~Color();
};

