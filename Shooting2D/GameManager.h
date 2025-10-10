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

// ���ӳ� ��� ���͸� �������� Ŭ����
class GameManager : public Singleton<GameManager>
{
	// friend : �ٸ� Ŭ������ �ڽ��� private/protected �׸� �����ϴ� ���� ������ش�.
	// Singleton<GameManager>�� GameManager�� private�� ���� ����������.
	friend class Singleton<GameManager>;

public:
	// �ʱ�ȭ
	void Initialize();
	// ����
	void Destroy();
	// ƽ �й�
	void Tick(float InDeltaTime);
	// ����� ���� �׸���
	void Render();
	// �Է� ó��
	void HandleKeyState(WPARAM InKey, bool InIsPressed);

	// ���͸� ���� �޴����� ���(ƽ�� ���� ó���� �����ϰ� ����)
	void RegistActor(RenderLayer InLayer, Actor* InActor);
	// ���͸� ���� ��û
	inline void RequestDestroy(Actor* DestroyTarget) { PendingDestroyActors.push_back(DestroyTarget); };

	// ȭ�� ũ��
	static constexpr unsigned int ScreenWidth = 600;
	static constexpr unsigned int ScreenHeight = 800;
	// ���� �⺻ ũ��(�ȼ�������)
	static constexpr unsigned int ActorDefaultSize = 64;

	// Getter
	inline const HWND GetMainWindowHandle() const { return hMainWindow; }
	inline const Point& GetAppPosition() const { return AppPosition; }
	inline Gdiplus::Bitmap* GetBackBuffer() const { return BackBuffer; }
	
	// Setter
	inline void SetMainWindowHandle(HWND InWindowHandle) { 
		if (hMainWindow == nullptr)
		{
			hMainWindow = InWindowHandle;	// �� �ѹ��� ������ �� �ִ� ����
		}
	}
	inline void SetGameState(GameState InState){ State = InState; }
protected:
private:
	GameManager() = default;
	virtual ~GameManager() = default;

	void UnregisteActor(Actor* InActor);		// ���͸� ���� �޴������� ��� ����
	void ProcessCollisions();					// �浹 ó�� �Լ�
	void ProcessPendingDestroyActors();			// ���� ������ ���͵��� ������ �����ϴ� �Լ�
			
	std::map<RenderLayer, std::set<Actor*>> Actors;	// ��� ���Ͱ� ����� ��(���̾� ���� ������ set�� ����)
	std::vector<Actor*> PendingDestroyActors;		// ���� ������ ���͵��� ���(�̹� �����ӿ� ���� ��û�� ���� ���͵�)
	std::map<PhysicsLayer, std::vector<PhysicsComponent*>> PhysicsComponents; // ���� ������Ʈ ����Ʈ

	HWND hMainWindow = nullptr;					// ������ �ڵ�
	Point AppPosition = Point(200, 100);		// ���α׷��� ���۵� ��ġ
	Gdiplus::Bitmap* BackBuffer = nullptr;		// ����ۿ� ����
	Gdiplus::Graphics* BackBufferGraphics = nullptr;  // ����ۿ� ���̿� �׸��� ���� ����
	
	Player* MainPlayer = nullptr;				// �÷��̾�(���� ���� ������ ����)
	BombSpawner* Spawner = nullptr;				// ��ź ������(�ֱ������� ��ź�� �����ϴ� ��ü)
	TimerUI* Timer = nullptr;					// �ð� ǥ�ÿ� UI

	TestGridActor* TestGrid = nullptr;			// ��ġ Ȯ���� ���� �׽�Ʈ�� �׸���

	GameState State = GameState::Playing;		// ������ ����
};

