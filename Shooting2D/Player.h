#pragma once
#include <unordered_map>
#include <Windows.h>
#include <gdiplus.h>
#include "enums.h"

// extern : 뒤에 있는 변수가 다른 파일에 선언이 되어 있다.
extern HWND g_hMainWindow; // g_hMainWindow가 다른 파일에 있다는 것을 알려줌

class Player
{
	/*
		피봇 위치는 한가운데
		이미지로 표시
		키보드 입력으로 좌우 이동
		플레이어가 화면을 벗어나지 않게 하기
	*/
public:
	Player() = delete;
	Player(const wchar_t* InImagePath);	// 무조건 파일 경로를 받아야 생성할 수 있다.
	~Player();

	void Render(Gdiplus::Graphics* InGraphics);

	void HandleKeyState(WPARAM InKey, bool InIsPressed);

private:
	// 플레이어 키 입력 상태
	std::unordered_map<InputDirection, bool> KeyWasPressedMap;

	// 플레이어 이미지가 들어있을 비트맵
	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이

	// 플레이어가 그려질 크기
	static constexpr int PixelSize = 64;
};

