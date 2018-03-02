#pragma once
#include <iostream>
#include <SDL_ttf.h>

class Font{

private:
	SDL_Color color_;
	TTF_Font* font_;

public:
	Font();
	~Font();
	Font(TTF_Font*, SDL_Color);
	bool FontInit();
	void RenderText(std::string, SDL_Color, float, float, int);
	unsigned int PowerTwoFloor(unsigned int);
};

