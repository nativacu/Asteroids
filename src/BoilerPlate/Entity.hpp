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
	Vector2	velocity_;
	float max_width_ = 1136.0f;
	float min_width_;
	float max_height_ = 640.0f;
	float min_height_;
	float radius_;
	float angle_;

public:
	bool is_debugging_ = false;  //Change
	Entity();
	~Entity();
	virtual void FillVertices(void);
	void DrawShape(void);			//Draws the vertices contained in the vector member
	virtual void Render(void);		//Renders drawn shape
	virtual void Update(float);
	float Warp(float&, float, float);
	void DrawCircle(void);
	void SetWindowDimensions(float, float);
};

