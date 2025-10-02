#pragma once

class Actor;	// 전방선언
class Component
{
public:
	Component(Actor* InOwner) : Owner(InOwner) {};
	virtual ~Component() = default;

	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	virtual void OnTick(float InDeltaTime) {};

	inline Actor* GetOwner() const { return Owner; }

protected:
	Actor* Owner = nullptr;	// 이 컴포넌트가 들어있는 액터
};