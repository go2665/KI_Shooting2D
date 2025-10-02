#pragma once
#include "Actor.h"

class Bomb : public Actor
{
public:
	Bomb() = delete;
	Bomb(ResourceID resourceId) : Actor(resourceId) {};

	virtual void OnInitialize() override;
	virtual void OnTick(float deltaTime) override;

	virtual void OnOverlap(Actor* other) override;	

	// Getters
	// Setters
	void SetDropAcceleration(float newAcceleration) { dropAcceleration = newAcceleration; }

private:		
	float dropAcceleration = 200.0f; // 드랍 가속도(초당 픽셀 단위)
	float dropSpeed = 0.0f; // 현재 드랍 속도
	float lifetime = 5.0f; // 폭탄의 수명(초 단위)
};