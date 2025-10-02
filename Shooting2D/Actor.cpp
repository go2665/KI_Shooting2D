#include "Actor.h"
#include "GameManager.h"
#include "ResourceManager.h"

Actor::Actor(ResourceID InID)
{
    Image = ResourceManager::Get().GetImage(InID);
}

void Actor::DestroyActor()
{
    if (!IsPendingDestroy)
    {
        IsPendingDestroy = true;
        GameManager::Get().RequestDestroy(this);    // 자신을 제거 요청하기
    }
}

void Actor::OnDestroy()
{
    while (!Components.empty())
    {
        RemoveComponent(Components[0]); // 컴포넌트 제거
    }
    Components.clear(); // 컴포넌트 리스트 초기화
}

void Actor::OnTick(float InDeltaTime)
{
    // 컴포넌트 업데이트
    for (auto& component : Components)
    {
        component->OnTick(InDeltaTime);
    }
}

void Actor::OnRender(Gdiplus::Graphics* InGraphics)
{
    if (!InGraphics) return;
    if (!Image) return;

    // 현재 변환 상태 저장
    Gdiplus::Matrix oldTransform;
    InGraphics->GetTransform(&oldTransform);

    // 회전 중심점을 객체의 중심으로 설정
    InGraphics->TranslateTransform(Position.X, Position.Y);

    // 지정된 각도만큼 회전
    InGraphics->RotateTransform(Angle);

    InGraphics->TranslateTransform(-Position.X, -Position.Y);

    // Image가 로딩되어 있다.
    InGraphics->DrawImage(
        Image,          // 그려질 이미지
        static_cast<int>(Position.X - Size * Pivot.X),    // 그려질 위치
        static_cast<int>(Position.Y - Size * Pivot.Y),
        Size, Size);  // 그려질 사이즈

    // 이전 변환 상태로 복원
    InGraphics->SetTransform(&oldTransform);
}

void Actor::AddComponent(Component* InComponent)
{
    if (InComponent)
    {
        Components.push_back(InComponent);
        InComponent->OnInitialize(); // 컴포넌트 초기화 호출
    }
}

void Actor::RemoveComponent(Component* InComponent)
{
    if (InComponent)
    {
        auto it = std::find(Components.begin(), Components.end(), InComponent);
        if (it != Components.end())
        {
            (*it)->OnDestroy(); // 컴포넌트 파괴 호출

            std::swap(*it, Components.back());
            Components.pop_back();   // 스왑 앤 팝 방식으로 컴포넌트 제거
            delete InComponent;
            InComponent = nullptr;
        }
    }
}
