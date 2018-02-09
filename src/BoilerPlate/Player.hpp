#pragma once
#include "Vector2.hpp"

class Player {

	Vector2 position;
	float max_width = 1136.0f;
	float max_height = 640.0f;

public:
	bool is_thrusting;

	Player();
	void Render(void);
	void Move(Vector2);
	void Update(void);
	void Warp(float&, float,  float);
	void MoveForward(void);
	void RotateLeft(void);
	void RotateRight(void);
};