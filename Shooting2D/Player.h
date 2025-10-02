#pragma once
#include <unordered_map>
#include "enums.h"
#include "Actor.h"

class Player : public Actor
{
public:
	Player() = delete;
	Player(ResourceID InID);

	virtual void OnTick(float InDeltaTime) override;
	virtual void OnRender(Gdiplus::Graphics* InGraphics) override;

	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	inline float GetSpeed() const { return Speed; }
	inline void SetSpeed(float InSpeed) { Speed = InSpeed; }

private:
	// 플레이어의 이동 속도
	float Speed = 200.0f;

	// 플레이어 키 입력 상태
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;
};