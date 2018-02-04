#pragma once
#ifndef VECTOR_3_H
#define VECTOR_3_H

#include "Vector2.hpp"
struct Vector3 {

	//Components
	float x;
	float y;
	float z;
	float length;

	//Constructor
	Vector3();
	Vector3(float);
	Vector3(Vector2&);
	Vector3(Vector2&, float);
	Vector3(float, float, float);

	//Functions
	float Length() const;
	float SquaredLength() const;
	float Normalize();

	//Operator Overloads
	Vector3& operator= (const Vector3&);

	Vector3 operator+(const Vector3&) const;
	Vector3 operator-(const Vector3&) const;
	Vector3 operator*(const Vector3&) const;
	Vector3 operator/(const Vector3&) const;
	Vector3 operator*(float);
	friend Vector3 operator*(float, const Vector3&);
	friend Vector3 operator*(const Vector3&, float);

	Vector3& operator+=(const Vector3&);
	Vector3& operator-=(const Vector3&);
	Vector3& operator*=(const Vector3&);
	Vector3& operator/=(const Vector3&);

	bool operator==(const Vector3&) const;
	bool operator!=(const Vector3&) const;

};

#endif