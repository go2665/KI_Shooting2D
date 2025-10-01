#pragma once
#include <Windows.h>
#include <vector>
#include "Common.h"
#include "Actor.h"
#include "Player.h"

// 게임내 모든 액터를 관리해줄 클래스
class GameManager
{
public:
	void Initialize();
	void Destroy();
	void Tick(float InDeltaTime);
	void Render(Gdiplus::Graphics* InGraphics);
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	static constexpr unsigned int ScrrenWidth = 600;
	static constexpr unsigned int ScrrenHeight = 800;
	static constexpr unsigned int ActorDefaultSize = 64;
protected:
private:
	GameManager() = default;
	virtual ~GameManager() = default;
	GameManager(const GameManager&) = delete;	// 복사 생성자 삭제
	GameManager& operator=(const GameManager&) = delete; // 대입 연산자 삭제
	GameManager(const GameManager&&) = delete;	// 이동 생성자 삭제
	GameManager& operator=(const GameManager&&) = delete; // 이동 대입 연산자 삭제

	std::vector<Actor*> Actors;

	HWND hMainWindow = nullptr;
	Point AppPosition = Point(2000, 100);
	Gdiplus::Bitmap* BackBuffer = nullptr;    // 백버퍼용 종이
	Gdiplus::Graphics* BackBufferGraphics = nullptr;  // 백버퍼용 종이에 그리기 위한 도구
	
	Player* MainPlayer = nullptr;
};

