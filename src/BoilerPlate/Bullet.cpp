#include "Bullet.hpp"
float kImpulse = 60.0f;
float kRadius = 2.0f;
float kLifeSpan = 28.0f;

Bullet::Bullet(Player ship){
	MathUtilities m;
	life_span_ = kLifeSpan;
	angle_ = ship.GetAngle();
	position_ = GetBulletPosition(ship);
	FillVertices();
	radius_ = kRadius;
}

Bullet::~Bullet(){

}

void Bullet::FillVertices() {
	vertices_.push_back(Vector2(1.5f, 2.0f));
	vertices_.push_back(Vector2(-1.5f, 2.0f));
	vertices_.push_back(Vector2(-1.5f, -2.0f));
	vertices_.push_back(Vector2(1.5f, -2.0f));
}

void Bullet::Update(float delta_time) {
	if (life_span_ > 0)
		life_span_--;

	if (life_span_ == 0) {
		is_alive_ = false;
	}

	ApplyImpulse(Vector2(kImpulse));
	Entity::Update(delta_time);
}

bool Bullet::GetIsAlive() {
	return is_alive_;
}

void Bullet::SetIsAlive(bool is_alive) {
	is_alive_ = is_alive;
}

Vector2 Bullet::GetBulletPosition(Player ship) {

	MathUtilities math_util;
	float radians = math_util.DegreesToRadians(angle_);
	Vector2 ship_position = ship.GetPosition();
	float ship_radius = ship.GetRadius();
	Vector2 position;
	position.x += ship_position.x  + ship_radius * -sinf(radians);
	position.y += ship_position.y + ship_radius * cosf(radians);
	
	return  position;
}