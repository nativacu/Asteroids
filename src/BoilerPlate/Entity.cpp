#include "Entity.hpp"



Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::FillVertices(void)
{
}

void Entity::DrawShape() {
	
	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < vertices_.size(); i++) {
		glVertex2f(vertices_[i].x, vertices_[i].y);
	}

	glEnd();
}

void Entity::Render(void)
{
	glLoadIdentity();
	glTranslatef(position_.x, position_.y, 0.0f);

	DrawShape();
}
