#include "Player.hpp"
#include <math.h>
#include "MathUtilities.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player() {
	position_ = Vector2::Origin;
	ship_angle_ = 0.0f;
	is_moving_left_ = false;

	ship_points_[0] = std::make_pair(0.0f, 30.0f);
	ship_points_[1] = std::make_pair(-40.0f, -40.0f);
	ship_points_[2] = std::make_pair(-7.5f,-30.0f);
	ship_points_[3] = std::make_pair(0.0f, -40.0f);
	ship_points_[4] = std::make_pair(7.5f, -30.0f);
	ship_points_[5] = std::make_pair(40.0f, -40.0f); 
	ship_points_[6] = std::make_pair(0.0f, 30.0f);
	ship_points_[7] = std::make_pair(7.5f, -30.0f);
	ship_points_[8] = std::make_pair(0.0f, 30.0f);
	ship_points_[9] = std::make_pair(-7.5f, -30.0f);

	thruster_points_[0] = std::make_pair(-20.0f, -50.0f);
	thruster_points_[1] = std::make_pair(-20.0f, -60.0f);
	thruster_points_[2] = std::make_pair(0.0f, -50.0f);
	thruster_points_[3] = std::make_pair(0.0f, -70.0f);
	thruster_points_[4] = std::make_pair(20.0f, -50.0f);
	thruster_points_[5] = std::make_pair(20.0f, -60.0f);
}

void Player::Move(Vector2 new_position) {
	float warp_width = max_width_ / 2 + ship_width_;
	float warp_height = max_height_ / 2 + ship_height_;

	position_ += new_position;
}

void Player::Update(void)
{

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

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < kTotalShipPoints; i++) {
		glVertex2f(ship_points_[i].first, ship_points_[i].second);
	}

	glEnd();
}

void Player::Thrust() {

	for (int i = 0; i < kTotalThrusterPoints; i += 2) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(thruster_points_[i].first, thruster_points_[i].second);
		glVertex2f(thruster_points_[i + 1].first, thruster_points_[i + 1].second);
		glEnd();
	}
}


void Player::RotateLeft(void){
	ship_angle_ += 5.0f;
	is_moving_left_ = false;
}

void Player::RotateRight(void) {
	ship_angle_ -= 5.0f;
	is_moving_right_ = false;
}

void Player::MoveForward(void) {
	float warp_width = max_width_ / 2 + ship_width_;
	float warp_height = max_height_ / 2 + ship_height_;

	float radians = MathUtilities().degrees_to_radians(ship_angle_);
	position_.x -=  kDefaultMove * float(sin(radians));
	position_.y +=  kDefaultMove * float(cos(radians));

	//Warping
	Warp(position_.x, -warp_width, warp_width);
	Warp(position_.y, -warp_height, warp_height);
}
