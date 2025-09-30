#pragma once
#include <unordered_map>
#include <Windows.h>
#include <gdiplus.h>
#include "enums.h"

// extern : 뒤에 있는 변수가 다른 파일에 선언이 되어 있다.
extern HWND g_hMainWindow; // g_hMainWindow가 다른 파일에 있다는 것을 알려줌
extern Gdiplus::Point g_ScreenSize;

using PointF = Gdiplus::PointF;
class Player
{
public:
	Player() = delete;
	Player(const wchar_t* InImagePath);	// 무조건 파일 경로를 받아야 생성할 수 있다.
	~Player();

	void Render(Gdiplus::Graphics* InGraphics);
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

private:
	// 플레이어가 그려질 크기
	static constexpr int PixelSize = 64;

	// 플레이어의 중심점
	PointF Pivot = { 0.5f, 0.5f }; // Pivot 기본 값은 한가운데

	// 플레이어의 위치
	PointF Position = { 0.0f, 0.0f };

	// 플레이어의 이동 속도
	float Speed = 10.0f;

	// 플레이어 키 입력 상태
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// 플레이어 이미지가 들어있을 비트맵
	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이		
};

