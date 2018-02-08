#pragma once
#include "Vector2.hpp"
class Player {

	Vector2 position;

public:
	Player();
	void Render(void);
	void Move(Vector2&);
	void Update(void);

	void MoveForward(void);
	void RotateLeft(void);
	void RotateRight(void);
};