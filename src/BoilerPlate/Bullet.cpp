#include "Bullet.hpp"

Bullet::Bullet(Player ship){
	MathUtilities m;
	angle_ = ship.GetAngle();
	position_ = GetBulletPosition(ship);
	FillVertices();
	radius_ = 2.0f;
	velocity_ = 50.0f;
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

	ApplyImpulse(Vector2(8.0f));
	Entity::Update(delta_time);
}

bool Bullet::GetIsAlive() {
	return is_alive_;
}

void Bullet::SetIsAlive(bool is_alive) {
	is_alive_ = is_alive;
}

Vector2 Bullet::GetBulletPosition(Player ship) {

	MathUtilities m;
	float radians = m.degrees_to_radians(angle_);
	Vector2 ship_position = ship.GetPosition();
	float ship_radius = ship.GetRadius();
	Vector2 position;
	position.x += ship_position.x  + ship_radius * -sinf(radians);
	position.y += ship_position.y + ship_radius * cosf(radians);
	
	return  position;
}