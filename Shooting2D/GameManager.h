#pragma once
#include <Windows.h>
#include <vector>
#include <set>
#include <map>
#include "Common.h"
#include "PhysicsComponent.h"
#include "Actor.h"
#include "Player.h"
#include "Singleton.h"
#include "TestGridActor.h"
#include "BombSpawner.h"
#include "TimerUI.h"

// 게임내 모든 액터를 관리해줄 클래스
class GameManager : public Singleton<GameManager>
{
	// friend : 다른 클래스가 자신의 private/protected 항목에 접근하는 것을 허용해준다.
	// Singleton<GameManager>가 GameManager의 private에 접근 가능해진다.
	friend class Singleton<GameManager>;

public:
	// 초기화
	void Initialize();
	// 정리
	void Destroy();
	// 틱 분배
	void Tick(float InDeltaTime);
	// 백버퍼 내용 그리기
	void Render();
	// 입력 처리
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	// 액터를 게임 메니저에 등록(틱과 랜더 처리를 가능하게 해줌)
	void RegistActor(RenderLayer InLayer, Actor* InActor);
	// 액터를 삭제 요청
	inline void RequestDestroy(Actor* DestroyTarget) { PendingDestroyActors.push_back(DestroyTarget); };

	// 화면 크기
	static constexpr unsigned int ScreenWidth = 600;
	static constexpr unsigned int ScreenHeight = 800;
	// 액터 기본 크기(픽셀사이즈)
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
	inline void SetGameState(GameState InState){ State = InState; }
protected:
private:
	GameManager() = default;
	virtual ~GameManager() = default;

	void UnregisteActor(Actor* InActor);		// 액터를 게임 메니저에서 등록 해제
	void ProcessCollisions();					// 충돌 처리 함수
	void ProcessPendingDestroyActors();			// 삭제 예정인 액터들을 실제로 정리하는 함수
			
	std::map<RenderLayer, std::set<Actor*>> Actors;	// 모든 액터가 저장된 맵(레이어 별로 별도의 set에 저장)
	std::vector<Actor*> PendingDestroyActors;		// 삭제 예정인 액터들의 목록(이번 프레임에 삭제 요청이 들어온 액터들)
	std::map<PhysicsLayer, std::vector<PhysicsComponent*>> PhysicsComponents; // 물리 컴포넌트 리스트

	HWND hMainWindow = nullptr;					// 윈도우 핸들
	Point AppPosition = Point(200, 100);		// 프로그램이 시작될 위치
	Gdiplus::Bitmap* BackBuffer = nullptr;		// 백버퍼용 종이
	Gdiplus::Graphics* BackBufferGraphics = nullptr;  // 백버퍼용 종이에 그리기 위한 도구
	
	Player* MainPlayer = nullptr;				// 플레이어(자주 쓰기 때문에 저장)
	BombSpawner* Spawner = nullptr;				// 폭탄 생성기(주기적으로 폭탄을 생성하는 객체)
	TimerUI* Timer = nullptr;					// 시간 표시용 UI

	TestGridActor* TestGrid = nullptr;			// 위치 확인을 위한 테스트용 그리드

	GameState State = GameState::Playing;		// 게임의 상태
};

