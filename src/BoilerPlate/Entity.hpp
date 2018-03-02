#pragma once
#include "Vector2.hpp"
#include <utility>
#include "MathUtilities.h"
#include <vector>

//Contains all shared members and functions of the Player and Asteroid classes
class Entity
{
protected:
	
	std::vector<Vector2> vertices_;
	Vector2	velocity_;
	Vector2 position_;
	float radius_;
	float angle_;
	float max_width_ = 1136.0f;
	float min_width_;
	float max_height_ = 640.0f;
	float min_height_;
	bool is_debugging_ = false;
	bool is_colliding_ = false;

public:
	Entity();
	~Entity();
	virtual void FillVertices(void);
	void DrawShape(void);			//Draws the vertices contained in the vector member
	virtual void Render(void);		//Renders drawn shape
	virtual void Update(float);
	float Warp(float&, float, float);
	void DrawCircle(void);
	virtual void SetIsDebugging();
	void SetWindowDimensions(float, float);
	float GetEntitiesDistance(Entity);
	float GetEntitiesDistance(Vector2);
	Vector2 GetPosition();
	void SetPosition(Vector2);
	bool GetIsDebugging();
	float GetRadius();
	void IsColliding(Entity);
	bool GetIsColliding(void);
	virtual void ApplyImpulse(Vector2);
	float GetAngle(void);
	void SetIsColliding(bool);
};

