#pragma once
#include "Vector2.hpp"
#include <utility>
#include <vector>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

//Contains all shared members and functions of the Player and Asteroid classes
class Entity
{
protected:
	Vector2 position_;
	std::vector<Vector2> vertices_;

public:
	Entity();
	~Entity();
	virtual void FillVertices(void);
	void DrawShape(void);			//Draws the vertices contained in the vector member
	virtual void Render(void);		//Renders drawn shape
	void Update(void);
};

