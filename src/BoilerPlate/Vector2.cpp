#include "Vector2.hpp"
#include <cmath>

Vector2::Vector2(){
	x = 0.0f;
	y = 0.0f;
	length = 0.0f;
}

Vector2::Vector2(float axis_value) {
	x = axis_value;
	y = axis_value;
	length = Length();
}

Vector2::Vector2(float x_axis, float y_axis) {
	x = x_axis;
	y = y_axis;
	length = Length();
}

float Vector2::Length() const{
	return std::sqrt(SquaredLength());
}

float Vector2::SquaredLength() const {
	return x * x + y * y;
}

float Vector2::Normalize() {

	float inverse_factor = 1.0f / Length();
	
	x *= inverse_factor;
	y *= inverse_factor;

	length = Length();

	return length;
}

Vector2& Vector2::operator=(const Vector2& target) {
	
	x = target.x;
	y = target.y;
	Length();

	return *this;
}

Vector2 Vector2::operator+(const Vector2& to_add) const{
	return Vector2(x + to_add.x, y + to_add.y);
}

Vector2 Vector2::operator-(const Vector2& to_substract) const {
	return Vector2(x - to_substract.x, y - to_substract.y);
}

Vector2 Vector2::operator*(const Vector2& to_multiply) const {
	return Vector2(x * to_multiply.x, y * to_multiply.y);
}

Vector2 Vector2::operator/(const Vector2& to_divide) const {

	if (to_divide.x == 0) {
		throw "Can't divide by zero";
	}

	if (to_divide.y == 0) {
		throw "Can't divide by zero";
	}

	return Vector2(x / to_divide.x, y / to_divide.y);
}

Vector2 Vector2:: operator*(float scalar) {
	return Vector2(scalar * x, scalar * y);
}


Vector2 operator*(float scalar, const Vector2& to_multiply){
	return to_multiply * scalar;
}

Vector2 operator*(const Vector2& to_multiply, float scalar) {
	return to_multiply * scalar;
}

Vector2& Vector2::operator+=(const Vector2& to_add){

	x += to_add.x;
	y += to_add.y;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& to_substract){

	x -= to_substract.x;
	y -= to_substract.y;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& to_multiply){

	x *= to_multiply.x;
	y *= to_multiply.y;

	return *this;
}

Vector2& Vector2::operator/=(const Vector2& to_divide)
{
	if (to_divide.x == 0 || to_divide.y == 0) {
		throw "Can't divide by zero";
	}

	x /= to_divide.x;
	y /= to_divide.y;

	return *this;
}

bool Vector2::operator==(const Vector2& to_compare) const
{
	return x == to_compare.x && y == to_compare.y;
}

bool Vector2::operator!=(const Vector2& to_compare) const
{
	return x != to_compare.x || y != to_compare.y;
}