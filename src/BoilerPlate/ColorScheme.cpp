#include "ColorScheme.h"
#include <GL/glew.h>

ColorScheme::ColorScheme(){
	ColorScheme::red = Color(0.0f, 0.8f, 0.0f, 0.4f);
	ColorScheme::blue = Color(0.2f, 0.4f, 0.6f, 0.4f);
	ColorScheme::yellow = Color(0.9f,0.9f,0.1f,0.3f);
	ColorScheme::green = Color(0.4f, 0.7f, 0.3f, 0.3f);
	ColorScheme::orange = Color(0.8f,0.3f,0.1f,0.5f);
}

void ColorScheme::change_background(Color new_background)
{
	glClearColor(new_background.red, new_background.green, new_background.blue, new_background.opacity);
}
