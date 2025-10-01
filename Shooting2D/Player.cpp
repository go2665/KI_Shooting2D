#include "Player.h"
#include "Common.h"

Player::Player(const wchar_t* InImagePath)
    : Actor(InImagePath)
{
    Position.X = 300.0f;
    Position.Y = 700.0f;
    KeyWasPressedMap[InputDirection::Up] = false;
    KeyWasPressedMap[InputDirection::Down] = false;
    KeyWasPressedMap[InputDirection::Left] = false;
    KeyWasPressedMap[InputDirection::Right] = false; 
}


void Player::OnTick(float InDeltaTime)
{
    float MoveDistance = InDeltaTime * Speed;
    if (KeyWasPressedMap[InputDirection::Left])
    {
        Position.X -= MoveDistance;
    }
    if (KeyWasPressedMap[InputDirection::Right])
    {
        Position.X += MoveDistance;
    }

    if (Position.X < (0 - Size * 0.5f))
    {
        Position.X = g_ScreenSize.X + Size * 0.5f; // 순환 이동
    }
    else if ((g_ScreenSize.X + Size * 0.5f) < Position.X)
    {
        Position.X = static_cast<float>(0 - Size * 0.5f);
    }
}

void Player::OnRender(Gdiplus::Graphics* InGraphics)
{
    Actor::OnRender(InGraphics);    // 부모의 OnRender 실행
    
    // 부모의 OnRender 실행한 후 추가로 동작 실행
    if (!Image)    
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
            static_cast<int>(Position.X - Size * Pivot.X),    // 그려질 위치
            static_cast<int>(Position.Y - Size * Pivot.Y),
            Size, Size);
    }
}

void Player::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    if (InKey == VK_LEFT || InKey == VK_RIGHT)
    {
        KeyWasPressedMap[static_cast<InputDirection>(InKey)] = InIsPressed;
    }
}
