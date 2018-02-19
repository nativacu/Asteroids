#include "Asteroid.hpp"

Asteroid::Asteroid(){
	position_ = Vector2::Origin;
	size_ = SizeOptions::kMedium; //Sets Medium as default Asteroid size
	FillVertices();
}

Asteroid::Asteroid(SizeOptions size) {
	position_ = Vector2::Origin;
	FillVertices();
	size_ = size;

}


Asteroid::~Asteroid(){

}

int Asteroid::GetSize() {
	return size_;
}


void Asteroid::FillVertices() {
	vertices_.push_back(Vector2(0.0f * size_, 20.0f * size_ ));
	vertices_.push_back(Vector2(5.0f * size_, 20.0f * size_));
	vertices_.push_back(Vector2(10.0f * size_, 17.0f * size_));
	vertices_.push_back(Vector2(10.0f * size_, 10.0f * size_));
	vertices_.push_back(Vector2(15.0f * size_, 5.0f * size_));
	vertices_.push_back(Vector2(20.0f * size_, 5.0f * size_));
	vertices_.push_back(Vector2(25.0f * size_, 0.0f * size_));
	vertices_.push_back(Vector2(30.0f * size_, -10.0f * size_));
	vertices_.push_back(Vector2(27.0f * size_, -10.0f * size_));
	vertices_.push_back(Vector2(25.0f * size_, -15.0f * size_));
	vertices_.push_back(Vector2(23.0f * size_, -25.0f * size_));
	vertices_.push_back(Vector2(30.0f * size_, -30.0f * size_));
	vertices_.push_back(Vector2(30.0f * size_, -33.0f * size_));
	vertices_.push_back(Vector2(26.0f * size_, -33.0f * size_));
	vertices_.push_back(Vector2(20.0f * size_, -45.0f * size_));
	vertices_.push_back(Vector2(10.0f * size_, -40.0f * size_));
	vertices_.push_back(Vector2(0.0f * size_, -43.0f * size_));
	vertices_.push_back(Vector2(-15.0f * size_, -35.0f * size_));
	vertices_.push_back(Vector2(-15.0f * size_, -25.0f * size_));
	vertices_.push_back(Vector2(-17.0f * size_, -25.0f * size_));
	vertices_.push_back(Vector2(-20.0f * size_, -20.0f * size_));
	vertices_.push_back(Vector2(-25.0f * size_, -10.0f * size_));
	vertices_.push_back(Vector2(-22.0f * size_, -5.0f * size_));
	vertices_.push_back(Vector2(-15.0f * size_, -3.0f * size_));
	vertices_.push_back(Vector2(-10.0f * size_, 5.0f * size_));
	vertices_.push_back(Vector2(-7.0f * size_, 10.0f * size_));
	vertices_.push_back(Vector2(-5.0f * size_, 10.0f * size_));
}