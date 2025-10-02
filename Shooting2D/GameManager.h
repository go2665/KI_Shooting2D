#pragma once
#include <Windows.h>
#include <vector>
#include <map>
#include "Common.h"
#include "Actor.h"
#include "Player.h"
#include "Singleton.h"

// 게임내 모든 액터를 관리해줄 클래스
class GameManager : public Singleton<GameManager>
{
	// friend : 다른 클래스가 자신의 private/protected 항목에 접근하는 것을 허용해준다.
	// Singleton<GameManager>가 GameManager의 private에 접근 가능해진다.
	friend class Singleton<GameManager>;

public:
	void Initialize();
	void Destroy();
	void Tick(float InDeltaTime);
	void Render();
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	void AddActor(RenderLayer InRenderLayer, Actor* InActor) { Actors[InRenderLayer].push_back(InActor); }

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
	GameManager() = default;
	virtual ~GameManager() = default;
			
	std::map<RenderLayer, std::vector<Actor*>> Actors;

	HWND hMainWindow = nullptr;
	Point AppPosition = Point(2000, 100);
	Gdiplus::Bitmap* BackBuffer = nullptr;    // 백버퍼용 종이
	Gdiplus::Graphics* BackBufferGraphics = nullptr;  // 백버퍼용 종이에 그리기 위한 도구
	
	Player* MainPlayer = nullptr;
};

