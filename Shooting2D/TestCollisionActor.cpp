#include <Windows.h>
#include <string>
#include "TestCollisionActor.h"

void TestCollisionActor::PrintTestResult(const TestCollisionActor* InTarget)
{
	char temp[256];
	if (CheckCircltToCircleCollision(this, InTarget))
	{
		sprintf_s(temp, 256, "원과 원이 충돌함.\n");
	}
	else
	{
		sprintf_s(temp, 256, "원과 원이 충돌하지 않음.\n");
	}
	OutputDebugStringA(temp);
	if (CheckRectToRectCollision(this, InTarget))
	{
		sprintf_s(temp, 256, "사각형과 사각형이 충돌함.\n");
	}
	else
	{
		sprintf_s(temp, 256, "사각형과 사각형이 충돌하지 않음.\n");
	}
	OutputDebugStringA(temp);
	if (CheckCircleToRectCollision(this, InTarget))
	{
		sprintf_s(temp, 256, "원과 사각형이 충돌함.\n");
	}
	else
	{
		sprintf_s(temp, 256, "원과 사각형이 충돌하지 않음.\n");
	}
	OutputDebugStringA(temp);	
}

bool TestCollisionActor::CheckCircltToCircleCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo)
{
	if(!InFrom || !InTo)
		return false;

	const PointF& From = InFrom->GetPosition();
	const PointF& To = InTo->GetPosition();

	float dx = To.X - From.X;
	float dy = To.Y - From.Y;
	float squaredDistance = dx * dx + dy * dy;

	float radiusSum = InFrom->Radius + InTo->Radius;
	float squaredRadiusSum = radiusSum * radiusSum;

	return squaredDistance <= squaredRadiusSum;
}

bool TestCollisionActor::CheckRectToRectCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo)
{
	if (!InFrom || !InTo)
		return false;

	const PointF& From = InFrom->GetPosition();
	const PointF& To = InTo->GetPosition();

	float HalfWidthFrom = InFrom->Width * 0.5f;
	float HalfHeightFrom = InFrom->Height * 0.5f;
	float HalfWidthTo = InTo->Width * 0.5f;
	float HalfHeightTo = InTo->Height * 0.5f;

	float FromLeft		= From.X - HalfWidthFrom;
	float FromRight		= From.X + HalfWidthFrom;
	float FromTop		= From.Y - HalfHeightFrom;
	float FromBottom	= From.Y + HalfHeightFrom;

	float ToLeft		= To.X - HalfWidthTo;
	float ToRight		= To.X + HalfWidthTo;
	float ToTop			= To.Y - HalfHeightTo;
	float ToBottom		= To.Y + HalfHeightTo;

	return !(FromRight < ToLeft || FromLeft>ToRight || FromBottom < ToTop || FromTop > ToBottom);
	//return (FromRight >= ToLeft && FromLeft <= ToRight && FromBottom >= ToTop && FromTop <= ToBottom);
}

bool TestCollisionActor::CheckCircleToRectCollision(const TestCollisionActor* InFrom, const TestCollisionActor* InTo)
{
	if (!InFrom || !InTo)
		return false;

	const PointF& From = InFrom->GetPosition();		// 사각형
	const PointF& To = InTo->GetPosition();			// 원

	float RectLeft = From.X - InFrom->Width * 0.5f;		// 사각형의 꼭지점
	float RectRight = From.X + InFrom->Width * 0.5f;
	float RectTop = From.Y - InFrom->Height * 0.5f;
	float RectBottom = From.Y + InFrom->Height * 0.5f;

	//원의 중심에서 가각형에 가장 가까운 점 찾기
	float ClosestX = To.X;
	float ClosestY = To.Y;

	if (To.X < RectLeft)
		ClosestX = RectLeft;
	else if (To.X > RectRight)
		ClosestX = RectRight;

	if (To.Y < RectTop)
		ClosestY = RectTop;
	else if (To.Y > RectBottom)
		ClosestY = RectBottom;

	float dx = To.X - ClosestX;
	float dy = To.Y - ClosestY;
	float squaredDistance = dx * dx + dy * dy;

	return squaredDistance <= (InTo->Radius * InTo->Radius);
}
