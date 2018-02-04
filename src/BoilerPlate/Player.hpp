#pragma once
#include "Vector2.hpp"
class Player {

	Vector2 position;

public:
	Player();
	void Render();
	void Move(Vector2&);
	void Update();
};