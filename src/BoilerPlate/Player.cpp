#include "Player.hpp"
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

Player::Player() {
	position.x = 0;
	position.y = 0;
}

void Player::Move(Vector2& new_position) {
	position += new_position;
	//Warping
	if (position.x >= 618.0f || position.x <= -618.0f) {  //half of the gameplay screen - 50 equals 618
		position.x *= -1;
	}

	if (position.y >= 370.0f || position.y <= -370.0f) { //half of the gameplay screen + 50 equals 370
		position.y *= -1;
	}
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

