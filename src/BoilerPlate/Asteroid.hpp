#pragma once
#include "Vector2.hpp"
#include <utility>
#include "Entity.hpp"

class Asteroid : public Entity{

public:
	enum SizeOptions { kSmall = 1, kMedium, kBig }; //Asteroid Size options
	Asteroid();
	Asteroid(SizeOptions);
	~Asteroid();
	void FillVertices(void) override;
	void Update(float) override;
	int GetSize(void);
	void ApplyImpulse(Vector2);

private:
	SizeOptions size_;
	float rotation_angle_ = 120.0f;
};


