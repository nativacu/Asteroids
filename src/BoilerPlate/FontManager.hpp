#pragma once
#include <string>
#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_ttf.h>

class FontManager
{
private:
	TTF_Font * font;
public:
	FontManager();
	FontManager(int gameScreenWidth, int gameScreenHeight, int fontSize);
	bool InitFont();
	unsigned int power_two_floor(unsigned int val);
	void RenderText(std::string message, SDL_Color color, float x, float y, int size);
	~FontManager();
};

