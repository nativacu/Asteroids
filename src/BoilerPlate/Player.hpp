#pragma once
#include "Vector2.hpp"

const float MAX_WIDTH = 568.0f + 50.0f;
const float MAX_HEIGHT = 320.0f + 60.0f;

class Player {

	Vector2 position;
	float max_width = 1136.0f;
	float max_height = 640.0f;

public:
  
	Player();
	void Render(void);
	void Move(Vector2&);
	void Update(void);
	void Warp(float&, float,  float);
	void MoveForward(void);
	void RotateLeft(void);
	void RotateRight(void);
};