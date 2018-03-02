#pragma once
#include "Vector2.hpp"
#include <utility>
#include "Entity.hpp"
#include "Bullet.hpp"

class Asteroid : public Entity{

public:
	enum SizeOptions { kSmall = 1, kMedium, kBig }; //Asteroid Size options
	Asteroid();
	Asteroid(SizeOptions);
	Asteroid(int);
	~Asteroid();
	void FillVertices(void) override;
	void Update(float) override;
	int GetSize(void);
	bool GetWasShot();
	void WasShot(Bullet);
	void SetWasShot(bool);
	void ApplyImpulse(Vector2) override;
	void SetIsDebugging() override;

private:
	SizeOptions size_;
	bool was_shot_ = false;
	float rotation_angle_ = 120.0f;
};


