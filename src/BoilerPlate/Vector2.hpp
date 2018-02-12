#pragma once
#ifndef VECTOR_2_H
#define VECTOR_2_H

struct Vector2 {
	//Static
	static Vector2 Origin;

	//Components
	float x;
	float y;
	float length;

	//Constructor
	Vector2();
	Vector2(float);
	Vector2(float, float);

	//Functions
	float Length() const;
	float SquaredLength() const;
	void Normalize();

	//Operator Overloads
	Vector2& operator= (const Vector2&);

	Vector2 operator+(const Vector2&) const;
	Vector2 operator-(const Vector2&) const;
	Vector2 operator*(const Vector2&) const;
	Vector2 operator/(const Vector2&) const;
	Vector2 operator*(float);
	friend Vector2 operator*(float, const Vector2&);
	friend Vector2 operator*(const Vector2&, float);

	Vector2& operator+=(const Vector2&);
	Vector2& operator-=(const Vector2&);
	Vector2& operator*=(const Vector2&);
	Vector2& operator/=(const Vector2&);

	bool operator==(const Vector2&) const;
	bool operator!=(const Vector2&) const;

};

#endif
