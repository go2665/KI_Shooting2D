#include "GameManager.h"
#include "Background.h"
#include "Player.h"
#include "TestGridActor.h"
#include "ResourceManager.h"
#include "Factory.h"

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

    MainPlayer = Factory::Get().SpawnActor<Player>(ResourceID::Player, RenderLayer::Player);
    Factory::Get().SpawnActor<Background>(ResourceID::Background, RenderLayer::Background);
    TestGrid = Factory::Get().SpawnActor<TestGridActor>(ResourceID::None, RenderLayer::Test);
}

void GameManager::Destroy()
{
    for (auto pair : Actors)
    {
        for (Actor* actor : pair.second)
        {
            actor->OnDestroy();
            delete actor;
        }
        pair.second.clear();
    }
    Actors.clear();

    delete BackBufferGraphics;
    BackBufferGraphics = nullptr;
    delete BackBuffer;
    BackBuffer = nullptr;
}

void GameManager::Tick(float InDeltaTime)
{   
    for (const auto& pair : Actors)
    {
        for (Actor* actor : pair.second)
        {
            actor->OnTick(InDeltaTime);
        }
    }
    ProcessPendingDestroyActors();  // 삭제 예정인 액터들을 모두 삭제
}

void GameManager::Render()
{
    if (BackBufferGraphics)   // g_BackBufferGraphics 필수
    {
        BackBufferGraphics->Clear(Gdiplus::Color(255, 0, 0, 0));

        for (const auto& pair : Actors)
        {
            for (Actor* actor : pair.second)
            {
                actor->OnRender(BackBufferGraphics);
            }
        }
    }
}

void GameManager::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    MainPlayer->HandleKeyState(InKey, InIsPressed);

    if (TestGrid)
    {
        TestGrid->DestroyActor();
        TestGrid = nullptr;
    }
}

void GameManager::RegistActor(RenderLayer InLayer, Actor* InActor)
{
    if (InActor)
    {
        Actors[InLayer].insert(InActor);
    }
}

void GameManager::UnregisteActor(Actor* InActor)
{
    std::set<Actor*>& actorSet = Actors[InActor->GetRenderLayer()];
    actorSet.erase(InActor);
    
    //for (size_t i = 0; i < actorSet.size(); i++)
    //{
    //    if (actorSet[i] == InActor)
    //    {
    //        if (i < actorSet.size() - 1)//마지막이 아니면
    //        {
    //            std::swap(actorSet[i], actorSet.back());
    //        }
    //        actorSet.pop_back();
    //        break;
    //    }
    //}
}

void GameManager::ProcessPendingDestroyActors()
{
    for (Actor* actor : PendingDestroyActors)
    {
        if (actor)
        {
            UnregisteActor(actor);
            actor->OnDestroy();
            delete actor;
        }
    }
    PendingDestroyActors.clear();
}
