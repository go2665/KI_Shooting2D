#pragma once
#include <Windows.h>
#include <vector>
#include <set>
#include <map>
#include "Common.h"
#include "Actor.h"
#include "Player.h"
#include "Singleton.h"
#include "TestGridActor.h"

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

	void RegistActor(RenderLayer InLayer, Actor* InActor);
	inline void RequestDestroy(Actor* DestroyTarget) { PendingDestroyActors.push_back(DestroyTarget); };

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

	void UnregisteActor(Actor* InActor);
	void ProcessPendingDestroyActors();			// 삭제 예정인 액터들을 실제로 정리하는 함수
			
	std::map<RenderLayer, std::set<Actor*>> Actors;
	std::vector<Actor*> PendingDestroyActors;	// 삭제 예정인 액터들의 목록

	HWND hMainWindow = nullptr;
	Point AppPosition = Point(2000, 100);
	Gdiplus::Bitmap* BackBuffer = nullptr;    // 백버퍼용 종이
	Gdiplus::Graphics* BackBufferGraphics = nullptr;  // 백버퍼용 종이에 그리기 위한 도구
	
	Player* MainPlayer = nullptr;
	TestGridActor* TestGrid = nullptr;
};

