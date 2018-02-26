#pragma once
#include "Entity.hpp"
#include "Player.hpp"

class Bullet : public Entity{

private:
	float life_span_ = 50.0f;
	bool is_alive_ = true;
public:
	Bullet(Player);
	~Bullet();
	bool GetIsAlive(void);
	void SetIsAlive(bool);
	void Update(float) override;
	void FillVertices(void) override; 
	Vector2 Bullet::GetBulletPosition(Player ship);
};

