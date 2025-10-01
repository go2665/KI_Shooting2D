#include "TestGridActor.h"
#include "GameManager.h"

TestGridActor::TestGridActor()
    :Actor(nullptr)
{
    WindowWidth = GameManager::ScreenWidth;
    WindowHeight = GameManager::ScreenHeight;

    Size = 5;
    HalfSize = Size / 2;

    BlueBrush = new Gdiplus::SolidBrush(Gdiplus::Color(255, 0, 0, 255));
}

TestGridActor::~TestGridActor()
{
    delete BlueBrush;
    BlueBrush = nullptr;
}

void TestGridActor::OnRender(Gdiplus::Graphics* InGraphics)
{
    if (!InGraphics || !BlueBrush) return;

    for (int y = 0; y <= WindowHeight; y += Interval)
    {
        for (int x = 0; x <= WindowWidth; x += Interval)
        {
            InGraphics->FillRectangle(BlueBrush, x - HalfSize, y - HalfSize, Size, Size);
        }
    }
}

