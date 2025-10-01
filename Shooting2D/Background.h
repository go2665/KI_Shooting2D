#pragma once
#include "Common.h"

class Background
{
public:
	Background() = delete;
	Background(const wchar_t* InImagePath);	// 무조건 파일 경로를 받아야 생성할 수 있다.
	~Background();

	void Tick(float InDeltaTime);
	void Render(Gdiplus::Graphics* InGraphics);

private:
	static constexpr int PixelSize = 64;

	// 중심점
	PointF Pivot = { 0.5f, 0.5f }; // Pivot 기본 값은 한가운데

	// 위치
	PointF Position = { 0.0f, 0.0f };

	// 이동 속도
	float Speed = 50.0f;

	// 이미지가 들어있을 비트맵
	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이		

	float Offset = 0.0f;
};

