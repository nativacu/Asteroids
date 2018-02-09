#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player() {
	position.x = 0;
	position.y = 0;
}

void Player::Move(Vector2& new_position) {
	float half_width = max_width / 2 + 50;
	float half_height = max_height / 2 + 60;
	position += new_position;
	
	//Warping
	Warp(position.x, -half_width , half_width);
	Warp(position.y, -half_height, half_height);
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
	glBegin(GL_LINE_LOOP);

	glVertex2f(0.0f + position.x, 50.0f + position.y);
	glVertex2f(-60.0f + position.x, -60.0f + position.y);
	glVertex2f(-10.0f + position.x, -50.0f + position.y);
	glVertex2f(0.0f + position.x, -60.0f + position.y);
	glVertex2f(10.0f + position.x, -50.0f + position.y);
	glVertex2f(60.0f + position.x, -60.0f + position.y);
	glVertex2f(0.0f + position.x, 50.0f + position.y);
	glVertex2f(10.0f + position.x, -50.0f + position.y);
	glVertex2f(0.0f + position.x, 50.0f + position.y);
	glVertex2f(-10.0f + position.x, -50.0f + position.y);
	
	glEnd();
}

