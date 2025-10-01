#pragma once
#include <Windows.h>
#include <vector>
#include "Common.h"
#include "Actor.h"
#include "Player.h"

// ���ӳ� ��� ���͸� �������� Ŭ����
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
	GameManager(const GameManager&) = delete;	// ���� ������ ����
	GameManager& operator=(const GameManager&) = delete; // ���� ������ ����
	GameManager(const GameManager&&) = delete;	// �̵� ������ ����
	GameManager& operator=(const GameManager&&) = delete; // �̵� ���� ������ ����

	std::vector<Actor*> Actors;

	HWND hMainWindow = nullptr;
	Point AppPosition = Point(2000, 100);
	Gdiplus::Bitmap* BackBuffer = nullptr;    // ����ۿ� ����
	Gdiplus::Graphics* BackBufferGraphics = nullptr;  // ����ۿ� ���̿� �׸��� ���� ����
	
	Player* MainPlayer = nullptr;
};

