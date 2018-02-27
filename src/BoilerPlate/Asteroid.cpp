#include "Asteroid.hpp"
#include "MathUtilities.h"
#include <time.h>

Asteroid::Asteroid(){
	size_ = SizeOptions::kBig; //Sets Big as default Asteroid size
	FillVertices();
	velocity_ = 0.0f;
	radius_ = 25.8f * size_;
	position_.x = rand() % static_cast<int>(max_width_) + radius_;
	position_.y = rand() % static_cast<int>(max_height_) + radius_;
	angle_ = rand() % 360 + 44;
	ApplyImpulse(Vector2(90.0f));
	is_colliding_ = false;
	was_shot_ = false;
}

Asteroid::Asteroid(SizeOptions size) {
	size_ = size;
	FillVertices();
	velocity_ = 0.0f;
	radius_ = 25.8f * size_;
	position_.x = rand() % static_cast<int>(max_width_) + radius_;
	position_.y = rand() % static_cast<int>(max_height_) + radius_;
	angle_ = rand() % 360 + 44;
	ApplyImpulse(Vector2(90.0f));
	is_colliding_ = false;
	was_shot_ = false;
}

Asteroid::Asteroid(int size) {
	if (size == 3) {
		size_ = kBig;
	}
	if (size == 2) {
		size_ = kMedium;
	}
	else{
		size_ = kSmall;
	}
	
	FillVertices();
	velocity_ = 0.0f;
	radius_ = 25.8f * size_;
	position_.x = rand() % static_cast<int>(max_width_) + radius_;
	position_.y = rand() % static_cast<int>(max_height_) + radius_;
	angle_ = rand() % 360 + 44;
	ApplyImpulse(Vector2(90.0f));
	is_colliding_ = false;
	was_shot_ = false;
}

Asteroid::~Asteroid(){

}

int Asteroid::GetSize() {
	if (size_ == kBig) {
		return 3;
	}
	if (size_ == kMedium) {
		return 2;
	}
	else {
		return 1;
	}
}

void Asteroid::ApplyImpulse(Vector2 impulse){
	velocity_.x -= (impulse.x) * sinf(MathUtilities().degrees_to_radians(angle_)) + size_;
	velocity_.y += (impulse.y) * cosf(MathUtilities().degrees_to_radians(angle_)) + size_;
}


void Asteroid::FillVertices() {
	float origin_offset = 3.0f;
	vertices_.push_back(Vector2(0.0f * size_ + origin_offset, 21.8 * size_ + origin_offset));
	vertices_.push_back(Vector2(13.8f * size_ + origin_offset, 17.25f * size_ + origin_offset));
	vertices_.push_back(Vector2(20.7f * size_ + origin_offset, 10.9f * size_ + origin_offset));
	vertices_.push_back(Vector2(24.6f * size_ + origin_offset, -12.0f * size_ + origin_offset));
	vertices_.push_back(Vector2(17.25 * size_ + origin_offset, -20.7f * size_ + origin_offset));
	vertices_.push_back(Vector2(10.35f * size_ + origin_offset, -24.6f * size_ + origin_offset));
	vertices_.push_back(Vector2(0.0f * size_ + origin_offset, -21.85 * size_ + origin_offset));
	vertices_.push_back(Vector2(-12.0 * size_ + origin_offset, -21.85 * size_ + origin_offset));
	vertices_.push_back(Vector2(-13.8f * size_ + origin_offset, -20.7f * size_ + origin_offset));
	vertices_.push_back(Vector2(-20.7f * size_ + origin_offset, -17.25 * size_ + origin_offset));
	vertices_.push_back(Vector2(-21.85 * size_ + origin_offset, -13.8f * size_ + origin_offset));
	vertices_.push_back(Vector2(-24.6 * size_ + origin_offset, 0.0f * size_ + origin_offset));
	vertices_.push_back(Vector2(-20.7 * size_ + origin_offset, 10.9f * size_ + origin_offset));
	vertices_.push_back(Vector2(-17.25f * size_ + origin_offset, 10.35f * size_ + origin_offset));
	vertices_.push_back(Vector2(-13.8f * size_ + origin_offset, 17.25f * size_ + origin_offset));
}

void Asteroid::Update(float delta_time){
	angle_ += rotation_angle_ * delta_time;
	Entity::Update(delta_time);
}

void Asteroid::WasShot(Bullet bullet) {
	float added_radius = radius_ + bullet.GetRadius();
	float distance = GetEntitiesDistance(bullet);

	if (distance <= added_radius) {
		was_shot_ = true;
	}
}


bool Asteroid::GetWasShot() {
	return was_shot_;
}

void Asteroid::SetWasShot(bool shot) {
	was_shot_ = shot;
}