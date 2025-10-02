#include "Actor.h"
#include "GameManager.h"
#include "ResourceManager.h"

Actor::Actor(ResourceID InID)
{
    Image = ResourceManager::Get().GetImage(InID);
}

void Actor::OnTick(float InDeltaTime)
{
}

void Actor::OnRender(Gdiplus::Graphics* InGraphics)
{
    if (!InGraphics) return;
    if (!Image) return;
 
    // Image가 로딩되어 있다.
    InGraphics->DrawImage(
        Image,          // 그려질 이미지
        static_cast<int>(Position.X - Size * Pivot.X),    // 그려질 위치
        static_cast<int>(Position.Y - Size * Pivot.Y),
        Size, Size);  // 그려질 사이즈
}
