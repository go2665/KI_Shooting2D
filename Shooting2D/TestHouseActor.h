#pragma once
#include "Actor.h"
class TestHouseActor : public Actor
{
public:
	TestHouseActor(ResourceID _);
	virtual ~TestHouseActor();
	virtual void OnRender(Gdiplus::Graphics* InGraphics);

private:	
	static constexpr int HouseVerticesCount = 7;
	const Gdiplus::PointF HouseVertices[HouseVerticesCount] =
	{
		{50, 0}, {100, 50}, {80, 50}, {80, 100}, {20, 100}, {20, 50}, {0, 50}
	};

	Gdiplus::Pen* GreenPen = nullptr;
};

