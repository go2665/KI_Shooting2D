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
	static GameManager& Get()
	{
		static GameManager instance;
		return instance;
	}
	void Initialize();
	void Destroy();
	void Tick(float InDeltaTime);
	void Render();
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	void AddActor(Actor* InActor) { Actors.push_back(InActor); }

	static constexpr unsigned int ScreenWidth = 600;
	static constexpr unsigned int ScreenHeight = 800;
	static constexpr unsigned int ActorDefaultSize = 64;

	// Getter
	inline const HWND GetMainWindowHandle() const { return hMainWindow; }
	inline const Point& GetAppPosition() const { return AppPosition; }
	inline Gdiplus::Bitmap* GetBackBuffer() const { return BackBuffer; }

	// Setter
	inline void SetMainWindowHandle(HWND InWindowHandle) { 
		if (hMainWindow == nullptr)
		{
			hMainWindow = InWindowHandle;	// 딱 한번만 설정할 수 있는 세터
		}
	}
protected:
private:
	// Singleton : 클래스의 인스턴스가 1개만 있는 클래스. 
	// private에 생성자를 넣어서 밖에서 인스턴스화 하는 것을 원천적으로 봉쇄
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

