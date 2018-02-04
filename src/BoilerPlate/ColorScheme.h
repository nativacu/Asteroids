#pragma once
#include "Color.h"

struct ColorScheme{
	ColorScheme();
	void change_background(Color new_background);

	Color red;
	Color yellow;
	Color green;
	Color blue;
	Color orange;
};

