#include "Entity.hpp"
#include "MathUtilities.h"
#include <math.h>
#include "ColorScheme.h"
#include <GL/glew.h>
#include <SDL_opengl.h>


Entity::Entity()
{

}


Entity::~Entity(){

}

void Entity::FillVertices(void)
{
}

void Entity::DrawShape() {
	glBegin(GL_LINE_LOOP);

	if (is_colliding_) {
		ColorScheme color;
		glColor4f(color.red.red, color.red.green, color.red.blue, color.red.opacity);
	}
	
	else {
		glColor3f(1, 1, 1);
	}

	for (int i = 0; i < vertices_.size(); i++) {
		glVertex2f(vertices_[i].x, vertices_[i].y);
	}

	glEnd();

	if (is_debugging_) {
		DrawCircle();
	}
}

void Entity::Render(void)
{
	glLoadIdentity();
	glTranslatef(position_.x, position_.y, 0.0f);
	glRotatef(angle_, 0.0f, 0.0f, 1.0f);

	DrawShape();
}

void Entity::Update(float elapsed_time){
	float warp_width = max_width_ / 2;
	float warp_height = max_height_ / 2;

	position_.x += velocity_.x * elapsed_time;
	position_.y += velocity_.y * elapsed_time;

	position_.x = Warp(position_.x, -warp_width, warp_width);
	position_.y = Warp(position_.y, -warp_height, warp_height);
}

float Entity::Warp(float& vertex, float min, float max) {

	if (vertex < min) {
		vertex = max - (min - vertex);
	}

	if (vertex > max) {
		vertex = min - (max - vertex);
	}

	return vertex;
}

void Entity::DrawCircle(void){
	int lineAmount = 100; 
	GLfloat twicePi = 2.0f * 3.14159265f;

	glLoadIdentity();

	glBegin(GL_LINE_LOOP);
	
	for (int i = 0; i <= lineAmount; i++) {
		glVertex2f(
			position_.x + (radius_ * sin(i *  twicePi / lineAmount)),
			position_.y + (radius_ * cos(i * twicePi / lineAmount))
		);
	}
	glEnd();
	glColor3f(1, 1, 1);
}

void Entity::SetWindowDimensions(float width, float height) {
	max_width_ = width;
	min_width_ = -width;
	max_height_ = height;
	min_height_ = -height;
}

float Entity::GetEntitiesDistance(Entity asteroid) {
	Vector2 asteroid_position = asteroid.GetPosition();
	return GetEntitiesDistance(asteroid_position);
}

float Entity::GetEntitiesDistance(Vector2 position) {
	float x_difference = position_.x - position.x;
	float y_difference = position_.y - position.y;
	return sqrt(x_difference * x_difference + y_difference * y_difference);
}

Vector2 Entity::GetPosition(){
	return position_;
}

float Entity::GetRadius() {
	return radius_;
}

void Entity::SetIsDebugging() {
	if (is_debugging_) {
		is_debugging_ = false;
	}
	
	else {
		is_debugging_ = true;
	}
}

bool Entity::GetIsDebugging() {
	return is_debugging_;
}

bool Entity::GetIsColliding() {
	return is_colliding_;
}

void Entity::ApplyImpulse(Vector2 impulse){
	MathUtilities math;
	float angle = math.DegreesToRadians(angle_);
	velocity_.x -= (impulse.x) * sinf(angle);
	velocity_.y += (impulse.y) * cosf(angle);
}

float Entity::GetAngle() {
	return angle_;
}

void Entity::SetIsColliding(bool collide) {
	is_colliding_ = collide;
}

void Entity::SetPosition(Vector2 new_position) {
	position_ = new_position;
}

void Entity::IsColliding(Entity asteroid) {
	float added_radius = radius_ + asteroid.GetRadius();
	float distance = GetEntitiesDistance(asteroid);
	
	if (distance <= added_radius) {
		is_colliding_ = true;
		asteroid.SetIsColliding(true);
	}
}
