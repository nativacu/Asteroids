#pragma once
class Color
{	
private:

	//RGBA scale of colors
	float red;
	float green;
	float blue;
	float opacity;

public:
	Color();
	Color(float red, float green, float blue, float alpha);
	~Color();

	//Getters for each component of the color
	float get_red();
	float get_green();
	float get_blue();
	float get_opacity();

	//Setters for each component of the color
	void set_red(float new_Red);
	void set_green(float new_Green);
	void set_blue(float new_Blue);
	void set_opacity(float new_Opacity);
};

