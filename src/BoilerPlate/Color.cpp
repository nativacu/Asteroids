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
