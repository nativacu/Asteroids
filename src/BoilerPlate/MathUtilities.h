#pragma once
const float PI = 3.14159265f;
class MathUtilities
{
public:
	MathUtilities();
	~MathUtilities();

	//Function for getting the nearest int of a given float
	int float_to_int(float current_number);

	//Function for getting the nearest even int of a given float
	int float_to_even_int(float current_number);

	//Template function that results in the maximum of the given values whether they are 2, 3 or 4 (or 0 if there's none)
	template <class number> number get_max(number x, number y);
	template <class number> number get_max(number x, number y, number z);
	template <class number> number get_max(number s, number x, number y, number z);

	//Template function that results in the minimum of the given values whether they are 2, 3 or 4 (or 0 if there's none)
	template <class number> number get_min(number x, number y);
	template <class number> number get_min(number x, number y, number z);
	template <class number> number get_min(number s, number x, number y, number z);

	//Template function for clamping a given value into the provided limits
	template <class number> number clamp_value(number x, number min, number max);

	//Function for converting degrees to radians
	float degrees_to_radians(float angle);

	//Function for converting radians to degrees
	float radians_to_degrees(float angle);

	//Function for calculating the angular distance of two given angles in degrees 
	float angular_distance_deg(float angle, float angle2);
	float angular_distance_rad(float angle, float angle2);

	//Return the absolute value of a given number
	float abs(float x);

	//Function to determine if a number is a power of two
	bool is_power_of_two(int number);

	//Function to interpolate a float (or an int) between a start value and an end value, at a fraction specified from start (0.0) to end (1.0)
	template <class number> number interpolate(number min, number max, float fraction);

};

template<class number>
inline number MathUtilities::get_max(number x, number y)
{
	if (x < y) {
		return y;
	}

	if (x == y) {
		return NULL;
	}

	else {
		return x;
	}
}


template<class number>
inline number MathUtilities::get_max(number x, number y, number z) {
	number max = x;
	if (y > max) {
		max = y;
	}

	if (z > max) {
		max = z;
	}

	if (x == y && y == z) {
		max = NULL;
	}

	return max;
}


template<class number>
inline number MathUtilities::get_max(number s, number x, number y, number z) {
	number max = s;

	if (x > max) {
		max = x;
	}

	if (y > max) {
		max = y;
	}

	if (z > max) {
		max = z;
	}

	if (x == y && y == z && z == s) {
		max = NULL;
	}
	return max;
}

template<class number>
inline number MathUtilities::get_min(number x, number y)
{
	if (x > y) {
		return y;
	}

	if (x == y) {
		return NULL;
	}

	else {
		return x;
	}
	return number();
}

template<class number>
inline number MathUtilities::get_min(number x, number y, number z)
{
	number min = x;
	if (y < min) {
		min = y;
	}
	
	if (z < min) {
		min = z;
	}

	if (x == y && y == z) {
		min = NULL;
	}

	return min;
}

template<class number>
inline number MathUtilities::get_min(number s, number x, number y, number z)
{
	number min = s;

	if (x < min) {
		min = x;
	}

	if (y < min) {
		min = y;
	}

	if (z < min) {
		min = z;
	}

	if (s == x && x == y && y == x) {
		min = NULL;
	}

	return min;
}

template<class number>
inline number MathUtilities::clamp_value(number x, number min, number max)
{
	if (x < min) {
		x = min;
	}

	if (x > max) {
		x = max;
	}

	return x;
}

template<class number>
inline number MathUtilities::interpolate(number min, number max, float fraction)
{
	return min + (max - min) * fraction;
}
