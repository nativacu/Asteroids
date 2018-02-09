#include "Vector3.hpp"
#include <cmath>

Vector3::Vector3(){
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vector3::Vector3(float axis_value) {
	x = axis_value;
	y = axis_value;
	z = axis_value;
}

Vector3::Vector3(Vector2& to_change) {
	x = to_change.x;
	y = to_change.y;
	z = 0.0f;
}

Vector3::Vector3(Vector2& to_change, float z_axis) {
	x = to_change.x;
	y = to_change.y;
	z = z_axis;
}

Vector3::Vector3(float x_axis, float y_axis, float z_axis) {
	x = x_axis;
	y = y_axis;
	z = z_axis;
}

float Vector3::Length() const {
	return std::sqrt(SquaredLength());
}

float Vector3::SquaredLength() const {
	return x * x + y * y + z * z;
}

void Vector3::Normalize() {

	float inverse_factor = 1.0f / Length();

	x *= inverse_factor;
	y *= inverse_factor;
	z *= inverse_factor;
	length = Length();
	return length;
}

Vector3& Vector3::operator=(const Vector3& target) {

	x = target.x;
	y = target.y;
	z = target.z;
  
	length = Length();

	return *this;
}

Vector3 Vector3::operator+(const Vector3& to_add) const {
	return Vector3(x + to_add.x, y + to_add.y, z + to_add.z);
}

Vector3 Vector3::operator-(const Vector3& to_substract) const {
	return Vector3(x - to_substract.x, y - to_substract.y, z - to_substract.z);
}

Vector3 Vector3::operator*(const Vector3& to_multiply) const {
	return Vector3(x * to_multiply.x, y * to_multiply.y, z * to_multiply.z);
}

Vector3 Vector3::operator/(const Vector3& to_divide) const {

	if (to_divide.x == 0 || to_divide.y == 0 || to_divide.z == 0) {
		throw "Can't divide by zero";
	}
	
	return Vector3(x / to_divide.x, y / to_divide.y, z / to_divide.z);
}

Vector3 Vector3:: operator*(float scalar) {
	return Vector3(scalar * x, scalar * y, scalar * z);
}


Vector3 operator*(float scalar, const Vector3& to_multiply) {
	return to_multiply * scalar;
}

Vector3 operator*(const Vector3& to_multiply, float scalar) {
	return to_multiply * scalar;
}

Vector3& Vector3::operator+=(const Vector3& to_add) {

	x += to_add.x;
	y += to_add.y;
	z += to_add.z;

	return *this;
}

Vector3& Vector3::operator-=(const Vector3& to_substract) {

	x -= to_substract.x;
	y -= to_substract.y;
	z -= to_substract.z;

	return *this;
}

Vector3& Vector3::operator*=(const Vector3& to_multiply) {

	x *= to_multiply.x;
	y *= to_multiply.y;
	z *= to_multiply.z;

	return *this;
}

Vector3& Vector3::operator/=(const Vector3& to_divide)
{
	if (to_divide.x == 0 || to_divide.y == 0 || to_divide.z == 0) {
		throw "Can't divide by zero";
	}

	x /= to_divide.x;
	y /= to_divide.y;
	z /= to_divide.z;

	return *this;
}

bool Vector3::operator==(const Vector3& to_compare) const
{
	return x == to_compare.x && y == to_compare.y && z == to_compare.z;
}

bool Vector3::operator!=(const Vector3& to_compare) const
{
	return x != to_compare.x || y != to_compare.y || z != to_compare.z;
}
