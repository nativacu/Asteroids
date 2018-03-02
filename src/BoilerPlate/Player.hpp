#pragma once
#include <utility> 
#include "Vector2.hpp"
#include "Entity.hpp"

const int kTotalThrusterPoints = 6;
const float kDefaultMove = 6.0f;
const float kDefaultThrust = 4.5f;
const float kMaxSpeed = 200.0f;
const float kFrictionCoefficient = 0.99f;

class Player : public Entity{

private:
	float ship_width_ = 50.0f;
	float ship_height_ = 60.0f;
	float ship_mass_ = 1.5f;
	bool is_alive_ = true;
	bool respawned_;
	bool is_moving_up_;
	bool is_moving_left_;
	bool is_moving_right_;
	std::vector<Vector2> thruster_vertices_;

public:
	Player();
	void Render(void) override;
	void Update(float elapsed_time) override;
	void Thrust(void);
	void MoveForward(void);
	void RotateLeft(void);
	void RotateRight(void);
	void SetIsMovingUp(bool);
	void SetIsMovingLeft(bool);
	void SetIsMovingRight(bool);
	void FillVertices(void) override;
	void ApplyImpulse(Vector2) override;
	bool GetIsAlive(void);
	void SetIsAlive(bool);
	bool GetRespawned(void);
	void SetRespawned(bool);
	std::vector<Vector2> GetVertices();
};