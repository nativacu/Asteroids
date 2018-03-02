#include "FontManager.hpp"


FontManager::FontManager()
{
}

FontManager::FontManager(int gameScreenWidth, int gameScreenHeight, int fontSize){
	font = TTF_OpenFont("Populaire.ttf", fontSize);
}

bool FontManager::InitFont()
{
	bool result = true;

	if (TTF_Init() == -1) {

		SDL_Log("TTF_Init: %s\n", TTF_GetError());

		result = false;
	}
	return result;
}

unsigned int FontManager::power_two_floor(unsigned int val)
{
	unsigned int power = 2, nextVal = power * 2;
	while ((nextVal *= 2) <= val)
		power *= 2;
	return power * 2;
}

void FontManager::RenderText(std::string message, SDL_Color color, float x, float y, int size)
{
	glLoadIdentity();

	glTranslatef(x, y, 0.f);
	SDL_Surface *surface;
	//Render font to a SDL_Surface

	if ((surface = TTF_RenderText_Blended(font, message.c_str(), color)) == nullptr) {
		TTF_CloseFont(font);
		std::cout << "TTF_RenderText error: " << std::endl;
		return;
	}

	GLuint texId;

	//Generate OpenGL texture
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texId);
	glBindTexture(GL_TEXTURE_2D, texId);

	//Avoid mipmap filtering
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//Find the first power of two for OpenGL image 
	int w = power_two_floor(surface->w) * 2;
	int h = power_two_floor(surface->h) * 2;

	//Create a surface to the correct size in RGB format, and copy the old image
	SDL_Surface * s = SDL_CreateRGBSurface(0, w, h, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

	SDL_BlitSurface(surface, NULL, s, NULL);

	//Copy the created image into OpenGL format

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);
	
	//Draw the OpenGL texture as a Quad

	glBegin(GL_QUADS); {
		glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(0.0f + surface->w, 0.0f, 0.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(0.0f + surface->w, 0.0f + surface->h, 0.0f);
		glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, 0.0f + surface->h, 0.0f);
	} 
	glEnd();

	glDisable(GL_TEXTURE_2D);

	//Cleanup
	SDL_FreeSurface(s);
	SDL_FreeSurface(surface);
	glDeleteTextures(1, &texId);
}


FontManager::~FontManager() {
}