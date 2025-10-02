#pragma once
#include "Actor.h"

class TestCollisionActor : public Actor
{
public :
	TestCollisionActor() = delete;
	TestCollisionActor(ResourceID InID) : Actor(InID) {};

	float Radius = 25.0f;

	float Width = 50.0f;
	float Height = 50.0f;

	void PrintTestResult(const TestCollisionActor* InTarget);

private:
	bool CheckCircltToCircleCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo);
	bool CheckRectToRectCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo);
	bool CheckCircleToRectCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo);
};

