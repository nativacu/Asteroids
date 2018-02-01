#include "ColorScheme.h"
#include <GL/glew.h>

ColorScheme::ColorScheme(){
	red.set_red(0.8f);
	red.set_opacity(0.4f);

	blue.set_red(0.2f);
	blue.set_green(0.4f);
	blue.set_blue(0.6f);
	blue.set_opacity(0.4f);

	yellow.set_red(0.9f);
	yellow.set_green(0.9f);
	yellow.set_blue(0.1f);
	yellow.set_opacity(0.3f);

	green.set_red(0.4f);
	green.set_green(0.7f);
	green.set_blue(0.3f);
	green.set_opacity(0.3f);

	orange.set_red(0.8f);
	orange.set_green(0.3f);
	orange.set_blue(0.1f);
	orange.set_opacity(0.5f);
}

void ColorScheme::change_background(Color new_background)
{
	glClearColor(new_background.get_red(), new_background.get_green(), new_background.get_blue(), new_background.get_opacity());
}
