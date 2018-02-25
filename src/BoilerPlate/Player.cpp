#include "Player.hpp"
#include <math.h>
#include "MathUtilities.h"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

MathUtilities kMathUtil;
Player::Player() {
	position_ = Vector2::Origin;
	angle_ = 0.0f;
	is_moving_left_ = false;
	is_moving_up_ = false;
	FillVertices();
	radius_ = 40.0f;
}


void Player::Render()
{
	glLoadIdentity();
	glTranslatef(position_.x, position_.y, 0.0f);
	glRotatef(angle_, 0.0f, 0.0f, 1.0f);
	
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

void Player::Update(float elapsed_time){

	float current_speed = velocity_.Length();
	
	if (current_speed > kMaxSpeed) {
		Vector2 min_velocity = velocity_/current_speed;

		velocity_.x = kMathUtil.clamp_value(velocity_.x, min_velocity.x, kMaxSpeed);
		velocity_.y = kMathUtil.clamp_value(velocity_.y, min_velocity.y, kMaxSpeed);
	}

	if (!is_moving_up_) {
		velocity_ *= 0.99;
	}

	Entity::Update(elapsed_time);
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
	angle_ += kDefaultMove;
	is_moving_left_ = false;
}

void Player::RotateRight(void) {
	angle_ -= kDefaultMove;
	is_moving_right_ = false;
}

void Player::SetIsMovingUp(bool is_moving_up){
	is_moving_up_ = is_moving_up;
}

void Player::SetIsMovingLeft(bool is_moving_left) {
	is_moving_left_ = is_moving_left;
}

void Player::SetIsMovingRight(bool is_moving_right) {
	is_moving_right_ = is_moving_right;
}

void Player::MoveForward(void) {

	float radians = kMathUtil.degrees_to_radians(angle_);
	
	//Adding a constant value to the current position
	position_.x -=  kDefaultMove * float(sin(radians)); 
	position_.y +=  kDefaultMove * float(cos(radians));

	ApplyImpulse(Vector2(kDefaultThrust, kDefaultThrust));

}

void Player::FillVertices() {
	vertices_.push_back(Vector2(0.0f, 21.0f));
	vertices_.push_back(Vector2(-28.0f, -28.0f));
	vertices_.push_back(Vector2(-5.25f, -21.0f));
	vertices_.push_back(Vector2(0.0f, -28.0f));
	vertices_.push_back(Vector2(5.25f, -21.0f));
	vertices_.push_back(Vector2(28.0, -28.0f));
	vertices_.push_back(Vector2(0.0f, 21.0f));
	vertices_.push_back(Vector2(5.25f, -21.0f));
	vertices_.push_back(Vector2(0.0f, 21.0f));
	vertices_.push_back(Vector2(-5.25f, -21.0f));

	thruster_vertices_.push_back(Vector2(-14.0f, -35.0f));
	thruster_vertices_.push_back(Vector2(-14.0f, -42.0f));
	thruster_vertices_.push_back(Vector2(0.0f, -35.0f));
	thruster_vertices_.push_back(Vector2(0.0f, -49.0f));
	thruster_vertices_.push_back(Vector2(14.0f, -35.0f));
	thruster_vertices_.push_back(Vector2(14.0f, -42.0f));
}

bool Player::ApplyImpulse(Vector2 impulse) {
	if (ship_mass_ > 0) {
		velocity_.x -= (impulse.x / ship_mass_) * sinf(kMathUtil.degrees_to_radians(angle_));
		velocity_.y += (impulse.y / ship_mass_) * cosf(kMathUtil.degrees_to_radians(angle_));
		return true;
	}

	else {
		return false;
	}
}