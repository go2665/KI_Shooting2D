#pragma once
#include "Actor.h"
#include "Enums.h"

// 모든 사용자 인터페이스 요소의 기본 클래스입니다. 
class UserInterface : public Actor
{
public:
	UserInterface() = delete;
	UserInterface(ResourceID resourceId) : Actor(resourceId) {};

	inline void SetWidth(int newWidth) { width = newWidth; UpdatePosition(); }
	inline void SetHeight(int newHeight) { height = newHeight; UpdatePosition(); }
	inline void SetPivot(float x, float y) { Pivot.X = x; Pivot.Y = y; UpdatePosition(); }
	inline void SetAnchor(float x, float y) { anchor.X = x; anchor.Y = y; UpdatePosition(); }

protected:
	int width = 0;		// 이미지 전체 너비
	int height = 0;		// 이미지 전체 높이
	PointF anchor = { 0.0f, 0.0f }; // 이미지 앵커 포인트
	POINT anchoredPosition = { 0, 0 }; // 앵커를 기준으로한 위치

	void UpdatePosition();
};