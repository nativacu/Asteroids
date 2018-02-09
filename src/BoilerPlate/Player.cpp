#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player() {
	position.x = 0;
	position.y = 0;
	is_thrusting = false;
}

void Player::Move(Vector2 new_position) {
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
	glLoadIdentity();
	glTranslatef(position.x, position.y, 0.0f);
	glBegin(GL_LINE_LOOP);

	glVertex2f(0.0f , 30.0f);
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

	if (is_thrusting) {
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
}

