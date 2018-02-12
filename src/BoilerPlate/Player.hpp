#pragma once
#include "Vector2.hpp"

class Player {

	Vector2 position_;
	float max_width_ = 1136.0f;
	float max_height_ = 640.0f;
	float ship_width_ = 50.0f;
	float ship_height_ = 60.0f;
	bool is_moving_up_;

public:
	Player();
	void Render(void);
	void Move(Vector2);
	void Update(void);
	void Warp(float&, float,  float);
	void Thrust(void);
	void MoveForward(void);
	void RotateLeft(void);
	void RotateRight(void);

	//Properties for is_moving_up member
	__declspec (property (put = SetIsMovingUp, get = GetIsMovingUp))
		bool moving_up;
	void SetIsMovingUp(bool is_up_key_pressed)
	{
		is_moving_up_ = is_up_key_pressed;
	}

	bool GetIsMovingUp() const
	{
		return is_moving_up_;
	}

	//Properties for max_width member
	__declspec (property (put = SetMaxWidth, get = GetMaxWidth))
		float window_width;
	void SetMaxWidth(float new_width)
	{
		max_width_ = new_width;
	}

	float GetMaxWidth() const
	{
		return max_width_;
	}

	//Properties for max_height member
	__declspec (property (put = SetMaxHeight, get = GetMaxHeight))
		float window_height;
	void SetMaxHeight(float new_height)
	{
		max_height_ = new_height;
	}

	float GetMaxHeight() const
	{
		return max_height_;
	}
};