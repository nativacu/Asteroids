#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player() {
	position.x = 0;
	position.y = 0;
}

void Player::Move(Vector2& new_position) {
	position += new_position;
}

void Player::Render()
{
	glBegin(GL_LINE_LOOP);
	glVertex2f(50 + position.x, 50 + position.y);
	glVertex2f(50 + position.x, -50 + position.y);
	glVertex2f(-50 + position.x, -50 + position.y);
	glVertex2f(-50 + position.x, 50 + position.y);
	glEnd();
}

