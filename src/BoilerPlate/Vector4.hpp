#pragma once

#ifndef VECTOR_4_H
#define VECTOR_4_H

#include "Vector2.hpp"
#include "Vector3.hpp"

struct Vector4 {

	//Components
	float x;
	float y;
	float z;
	Vector2 w;
	float length;

	//Constructor
	Vector4();
	Vector4(float);
	Vector4(Vector2&);
	Vector4(Vector3&);
	Vector4(Vector3&, Vector2&);
	Vector4(float, float, float, Vector2&);

	//Functions
	float Length() const;
	float SquaredLength() const;
	void Normalize();

	//Operator Overloads
	Vector4& operator= (const Vector4&);
	Vector4 operator+(const Vector4&) const;
	Vector4 operator-(const Vector4&) const;
	Vector4 operator*(const Vector4&) const;
	Vector4 operator/(const Vector4&) const;
	Vector4 operator*(float);
	friend Vector4 operator*(float, const Vector4&);
	friend Vector4 operator*(const Vector4&, float);

	Vector4& operator+=(const Vector4&);
	Vector4& operator-=(const Vector4&);
	Vector4& operator*=(const Vector4&);
	Vector4& operator/=(const Vector4&);

	bool operator==(const Vector4&) const;
	bool operator!=(const Vector4&) const;

};

#endif
