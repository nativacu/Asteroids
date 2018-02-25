#include "Asteroid.hpp"
#include "MathUtilities.h"
#include <time.h>

Asteroid::Asteroid(){
	size_ = SizeOptions::kBig; //Sets Big as default Asteroid size
	FillVertices();
	velocity_ = 0.0f;
	radius_ = 42.0f * size_;
	position_.x = rand() % static_cast<int>(max_width_) + radius_;
	position_.y = rand() % static_cast<int>(max_height_) + radius_;
	angle_ = rand() % 360 + 10;
	ApplyImpulse(Vector2(90.0f));
}

Asteroid::Asteroid(SizeOptions size) {
	size_ = size;
	Asteroid();
}

Asteroid::~Asteroid(){

}

int Asteroid::GetSize() {
	return size_;
}

void Asteroid::ApplyImpulse(Vector2 impulse){
	velocity_.x -= (impulse.x) * sinf(MathUtilities().degrees_to_radians(angle_)) + size_;
	velocity_.y += (impulse.y) * cosf(MathUtilities().degrees_to_radians(angle_)) + size_;
}


void Asteroid::FillVertices() {
	vertices_.push_back(Vector2(0.0f * size_, 21.8 * size_));
	vertices_.push_back(Vector2(13.8f * size_, 17.25f * size_));
	vertices_.push_back(Vector2(20.7f * size_, 6.9f * size_));
	vertices_.push_back(Vector2(27.3f * size_, -12.0f * size_));
	vertices_.push_back(Vector2(17.25 * size_, -20.7f * size_));
	vertices_.push_back(Vector2(6.9f * size_, -24.84f * size_));
	vertices_.push_back(Vector2(0.0f * size_, -21.85 * size_));
	vertices_.push_back(Vector2(-10.35 * size_, -21.85 * size_));
	vertices_.push_back(Vector2(-13.8f * size_, -20.7f * size_));
	vertices_.push_back(Vector2(-20.7f * size_, -17.25 * size_));
	vertices_.push_back(Vector2(-24.15 * size_, -13.8f * size_));
	vertices_.push_back(Vector2(-27.6 * size_, 0.0f * size_));
	vertices_.push_back(Vector2(-24.15 * size_, 6.9f * size_));
	vertices_.push_back(Vector2(-17.25f * size_, 10.35f * size_));
	vertices_.push_back(Vector2(-13.8f * size_, 17.25f * size_));
}

void Asteroid::Update(float delta_time){
	angle_ += rotation_angle_ * delta_time;
	Entity::Update(delta_time);
}


