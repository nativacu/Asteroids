#include "Vector4.hpp"
#include <cmath>

Vector4::Vector4() {
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(float axis_value) {
	x = axis_value;
	y = axis_value;
	z = axis_value;
	w = axis_value;
}

Vector4::Vector4(Vector2& to_change) {
	x = to_change.x;
	y = to_change.y;
	z = 0.0f;
	w = 0.0f;
}

Vector4::Vector4(Vector3& to_vector4) {
	x = to_vector4.x;
	y = to_vector4.y;
	z = to_vector4.z;
	w = 0.0f;
}

Vector4::Vector4(Vector3& to_vector4, float w){
	x = to_vector4.x;
	y = to_vector4.y;
	z = to_vector4.z;
	w = w;
}

Vector4::Vector4(float x_axis, float y_axis, float z_axis, float w) {
	x = x_axis;
	y = y_axis;
	z = z_axis;
	w = w;
}

float Vector4::Length() const {
	return std::sqrt(SquaredLength());
}

float Vector4::SquaredLength() const {
	return x * x + y * y + z * z;
}

void Vector4::Normalize() {

	float inverse_factor = 1.0f / Length();

	x *= inverse_factor;
	y *= inverse_factor;
	z *= inverse_factor;
	length = Length();
}

Vector4& Vector4::operator=(const Vector4& target) {

	x = target.x;
	y = target.y;
	z = target.z;
	w = target.w;

	length = Length();

	return *this;
}

Vector4 Vector4::operator+(const Vector4& to_add) const {
	return Vector4(x + to_add.x, y + to_add.y, z + to_add.z, w + to_add.w);
}

Vector4 Vector4::operator-(const Vector4& to_substract) const {
	return Vector4(x - to_substract.x, y - to_substract.y, z - to_substract.z, w - to_substract.w);
}

Vector4 Vector4::operator*(const Vector4& to_multiply) const {
	return Vector4(x * to_multiply.x, y * to_multiply.y, z * to_multiply.z, w * to_multiply.w);
}

Vector4 Vector4::operator/(const Vector4& to_divide) const {

	if (to_divide.x == 0 || to_divide.y == 0 || to_divide.z == 0 || to_divide.w == 0) {
		throw "Can't divide by zero";
	}

	return Vector4(x / to_divide.x, y / to_divide.y, z / to_divide.z, w / to_divide.w);
}

Vector4 Vector4:: operator*(float scalar) {
	return Vector4(scalar * x, scalar * y, scalar * z, scalar * w);
}


Vector4 operator*(float scalar, const Vector4& to_multiply) {
	return to_multiply * scalar;
}

Vector4 operator*(const Vector4& to_multiply, float scalar) {
	return to_multiply * scalar;
}

Vector4& Vector4::operator+=(const Vector4& to_add) {

	x += to_add.x;
	y += to_add.y;
	z += to_add.z;
	w += to_add.w;

	return *this;
}

Vector4& Vector4::operator-=(const Vector4& to_substract) {

	x -= to_substract.x;
	y -= to_substract.y;
	z -= to_substract.z;
	w -= to_substract.w;

	return *this;
}

Vector4& Vector4::operator*=(const Vector4& to_multiply) {

	x *= to_multiply.x;
	y *= to_multiply.y;
	z *= to_multiply.z;
	w *= to_multiply.w;

	return *this;
}

Vector4& Vector4::operator/=(const Vector4& to_divide)
{
	if (to_divide.x == 0 || to_divide.y == 0 || to_divide.z == 0 || to_divide.w == 0) {
		throw "Can't divide by zero";
	}

	x /= to_divide.x;
	y /= to_divide.y;
	z /= to_divide.z;
	w /= to_divide.w;

	return *this;
}

bool Vector4::operator==(const Vector4& to_compare) const
{
	return x == to_compare.x && y == to_compare.y && z == to_compare.z && w == to_compare.w;
}

bool Vector4::operator!=(const Vector4& to_compare) const
{
	return x != to_compare.x || y != to_compare.y || z != to_compare.z || w != to_compare.w;
}


