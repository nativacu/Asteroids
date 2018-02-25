#include "Entity.hpp"
#include "MathUtilities.h"


Entity::Entity()
{
	min_width_ = -max_width_;
	min_height_ = -max_height_;
}


Entity::~Entity(){

}

void Entity::FillVertices(void)
{
}

void Entity::DrawShape() {
	int lineAmount = 100;
	GLfloat twicePi = 2.0f * 3.14159265f;
	glBegin(GL_LINE_LOOP);

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
}

void Entity::SetWindowDimensions(float new_width, float new_height) {
	max_width_ = new_width;
	min_width_ = -new_width;
	max_height_ = new_height;
	min_height_ = -new_height;
}