#pragma once
#include "Actor.h"

class BombSpawner : public Actor
{
public:
	BombSpawner() = delete;
	BombSpawner(ResourceID resourceId) : Actor(resourceId) {};

	virtual void OnInitialize() override;
	virtual void OnTick(float deltaTime) override;

private:
	float initialDelay = 2.0f;			// 초기 폭탄 생성 지연 시간
	float spawnInterval = 0.1f;			// 초당 폭탄 생성 간격

	bool hasInitialDelayPassed = false;	// 초기 지연 시간이 지났는지 여부
	float timeSinceLastSpawn = 0.0f;	// 마지막 폭탄 생성 이후 경과 시간
};

