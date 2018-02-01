#include "MathUtilities.h"

MathUtilities::MathUtilities()
{
}


MathUtilities::~MathUtilities()
{
}

int MathUtilities::float_to_int(float current_number){

	return static_cast<int>(current_number);
}

int MathUtilities::float_to_even_int(float current_number) {
	int result = float_to_int(current_number);

	if (result % 2 != 00) {
		result = result + 1;
	}

	return result;
}

float MathUtilities::degrees_to_radians(float angle){

	return angle * PI/180;
}

float MathUtilities::radians_to_degrees(float angle){

	return angle * 180/PI;
}

float MathUtilities::angular_distance_deg(float angle, float angle2)
{
	return abs(angle-angle2);
}

float MathUtilities::angular_distance_rad(float angle, float angle2)
{
	return abs(angle - angle2);
}

float MathUtilities::abs(float x)
{
	if(x < 0) {
		x = -1 * x;
	}
	return x;
}


bool MathUtilities::is_power_of_two(int number) {
	int res;
	if (number % 2 != 0) {
		return false;
	}
	while (number > 2) {
		res = number % 2;
		if (res != 0) {
			return false;
		}
		else {
			number /= 2;
		}
	}
	return true;
}
