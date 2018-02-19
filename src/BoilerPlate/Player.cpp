#include "Player.hpp"
#include <math.h>
#include "MathUtilities.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player() {
	position_ = Vector2::Origin;
	ship_angle_ = 0.0f;
	is_moving_left_ = false;
	is_moving_up_ = false;
	FillVertices();
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
	glRotatef(ship_angle_, 0.0f, 0.0f, 1.0f);
	
	if (is_moving_left_) {
		RotateLeft();
	}

	else if (is_moving_right_) {
		RotateRight();
	}

	else if (is_moving_up_) {
		Thrust();
	}

	DrawShape();
}

void Player::Thrust() {

	//Draws all Thruster vertices
	for (int i = 0; i < kTotalThrusterPoints; i += 2) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(thruster_vertices_[i].x, thruster_vertices_[i].y);
		glVertex2f(thruster_vertices_[i + 1].x, thruster_vertices_[i + 1].y);
		glEnd();
	}
}

//Adds or substracts from current angle to achieve ship rotation
void Player::RotateLeft(void){
	ship_angle_ += kDefaultMove;
	is_moving_left_ = false;
}

void Player::RotateRight(void) {
	ship_angle_ -= kDefaultMove;
	is_moving_right_ = false;
}

void Player::MoveForward(void) {
	float warp_width = max_width_ / 2 + ship_width_;
	float warp_height = max_height_ / 2 + ship_height_;

	float radians = MathUtilities().degrees_to_radians(ship_angle_);
	
	//Adding a constant value to the current position
	position_.x -=  kDefaultMove * float(sin(radians)); 
	position_.y +=  kDefaultMove * float(cos(radians));

	//Warping
	Warp(position_.x, -warp_width, warp_width);
	Warp(position_.y, -warp_height, warp_height);
}

void Player::FillVertices() {
	vertices_.push_back(Vector2(0.0f, 30.0f));
	vertices_.push_back(Vector2(-40.0f, -40.0f));
	vertices_.push_back(Vector2(-7.5f, -30.0f));
	vertices_.push_back(Vector2(0.0f, -40.0f));
	vertices_.push_back(Vector2(7.5f, -30.0f));
	vertices_.push_back(Vector2(40.0f, -40.0f));
	vertices_.push_back(Vector2(0.0f, 30.0f));
	vertices_.push_back(Vector2(7.5f, -30.0f));
	vertices_.push_back(Vector2(0.0f, 30.0f));
	vertices_.push_back(Vector2(-7.5f, -30.0f));

	thruster_vertices_.push_back(Vector2(-20.0f, -50.0f));
	thruster_vertices_.push_back(Vector2(-20.0f, -60.0f));
	thruster_vertices_.push_back(Vector2(0.0f, -50.0f));
	thruster_vertices_.push_back(Vector2(0.0f, -70.0f));
	thruster_vertices_.push_back(Vector2(20.0f, -50.0f));
	thruster_vertices_.push_back(Vector2(20.0f, -60.0f));
}