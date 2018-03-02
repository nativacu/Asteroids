#include "MathUtilities.h"

MathUtilities::MathUtilities()
{
}


MathUtilities::~MathUtilities()
{
}

int MathUtilities::FloatToInt(float current_number){

	return static_cast<int>(current_number);
}

int MathUtilities::FloatToEvenInt(float current_number) {
	int result = FloatToInt(current_number);

	if (result % 2 != 00) {
		result = result + 1;
	}

	return result;
}

float MathUtilities::DegreesToRadians(float angle){

	return angle * PI/180;
}

float MathUtilities::RadiansToDegrees(float angle){

	return angle * 180/PI;
}

float MathUtilities::AngularDistanceDegrees(float angle, float angle2)
{
	return Abs(angle-angle2);
}

float MathUtilities::AngularDistanceRadians(float angle, float angle2)
{
	return Abs(angle - angle2);
}

float MathUtilities::Abs(float x)
{
	if(x < 0) {
		x = -1 * x;
	}
	return x;
}


bool MathUtilities::IsPowerOfTwo(int number) {
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
