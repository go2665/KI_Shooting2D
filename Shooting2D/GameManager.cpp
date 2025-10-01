#include "GameManager.h"
#include "Background.h"
#include "Player.h"
#include "TestGridActor.h"

void GameManager::Initialize()
{
    BackBuffer = new Gdiplus::Bitmap(
        GameManager::ScreenWidth, GameManager::ScreenHeight, PixelFormat32bppARGB);
    BackBufferGraphics = Gdiplus::Graphics::FromImage(BackBuffer);
    if (!BackBufferGraphics)
    {
        // 혹시 안만들어졌을 때를 대비한 에러 출력
        MessageBox(hMainWindow, L"백 버퍼 그래픽스 생성 실패", L"오류", MB_OK | MB_ICONERROR);
    }

    AddActor(new Background(L"./Images/Background.png"));
    MainPlayer = new Player(L"./Images/Airplane.png");
    AddActor(MainPlayer);
    AddActor(new TestGridActor());
}

void GameManager::Destroy()
{
    for (Actor* Actor : Actors)
    {
        delete Actor;
    }
    Actors.clear();

    delete BackBufferGraphics;
    BackBufferGraphics = nullptr;
    delete BackBuffer;
    BackBuffer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{
    for (Actor* Actor : Actors)
    {
        Actor->OnTick(InDeltaTime);
    }
}

void GameManager::Render()
{
    if (BackBufferGraphics)   // g_BackBufferGraphics 필수
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        for (Actor* Actor : Actors)
        {
            Actor->OnRender(BackBufferGraphics);
        }
    }
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);
}