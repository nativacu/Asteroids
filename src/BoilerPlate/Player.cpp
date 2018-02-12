#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player() {
	position_ = Vector2::Origin;
}

void Player::Move(Vector2 new_position) {
	float warp_width = max_width_ / 2 + ship_width_;
	float warp_height = max_height_ / 2 + ship_height_;

	position_ += new_position;
	
	//Warping
	Warp(position_.x, -warp_width , warp_width);
	Warp(position_.y, -warp_height, warp_height);
}

void Player::Warp(float& vertex, float min, float max){

	if (vertex < min){
		vertex = max - (min - vertex);
	}

	if (vertex > max) { 
		vertex = min - (max - vertex);
	}

}

void Player::Render()
{
	glLoadIdentity();
	glTranslatef(position_.x, position_.y, 0.0f);
	glBegin(GL_LINE_LOOP);

	glVertex2f(0.0f, 30.0f);
	glVertex2f(-40.0f, -40.0f);
	glVertex2f(-7.5f, -30.0f);
	glVertex2f(0.0f, -40.0f);
	glVertex2f(7.5f, -30.0f);
	glVertex2f(40.0f, -40.0f);
	glVertex2f(0.0f, 30.0f);
	glVertex2f(7.5f, -30.0f);
	glVertex2f(0.0f, 30.0f);
	glVertex2f(-7.5f, -30.0f);

	glEnd();
	if (is_moving_up_) {
		Thrust();
	}
}

void Player::Thrust() {
		glBegin(GL_LINE_LOOP);
		glVertex2f(-20.0f, -50.0f);
		glVertex2f(-20.0f, -60.0f);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex2f(0.0f, -50.0f);
		glVertex2f(0.0f, -70.0f);
		glEnd();

		glBegin(GL_LINE_LOOP);
		glVertex2f(20.0f, -50.0f);
		glVertex2f(20.0f, -60.0f);
		glEnd();
}

