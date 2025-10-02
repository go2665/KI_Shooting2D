#pragma once
#include "Component.h"
#include "enums.h"

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(Actor* InOwner, CollisionType InType = CollisionType::Circle, PhysicsLayer InLayer = PhysicsLayer::None)
		:Component(InOwner), Collision(InType), Layer(InLayer)
	{
	}

	bool IsCollision(PhysicsComponent* InOther) const;

	inline float GetRadius() const { return Data1; }	// 원형 충돌의 반지름 반환
	inline float GetWidth() const { return Data1; }		// 사각형 충돌의 너비 반환
	inline float GetHeight() const { return Data2; }	// 사각형 충돌의 높이 반환
	inline CollisionType GetCollisionType() const { return Collision; } // 충돌 타입 반환
	inline PhysicsLayer GetLayer() const { return Layer; } // 물리 레이어 반환

	inline void SetRadius(float radius) { Data1 = radius; } // 원형 충돌의 반지름 설정
	inline void SetWidth(float width) { Data1 = width; }	// 사각형 충돌의 너비 설정
	inline void SetHeight(float height) { Data1 = height; } // 사각형 충돌의 높이 설정

private:
	static bool CheckCircltToCircleCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);
	static bool CheckRectToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);
	static bool CheckCircleToRectCollision(const PhysicsComponent* InFrom, const PhysicsComponent* InTo);

	CollisionType Collision = CollisionType::Circle;
	PhysicsLayer Layer = PhysicsLayer::None;
	float Data1 = 0.0f;
	float Data2 = 0.0f;
};

