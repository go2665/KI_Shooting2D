#include "Player.h"

Player::Player(const wchar_t* InImagePath)
{
    Position.X = 300;
    Position.Y = 700;

    KeyWasPressedMap[InputDirection::Up] = false;
    KeyWasPressedMap[InputDirection::Down] = false;
    KeyWasPressedMap[InputDirection::Left] = false;
    KeyWasPressedMap[InputDirection::Right] = false;

    Image = new Gdiplus::Bitmap(InImagePath); // 플레이어 이미지 로딩
    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        // 정상적으로 파일 로딩이 안됬다.
        delete Image;       // 실패했으면 즉시 해제
        Image = nullptr;
        OutputDebugString(L"플레이어 이미지 로드 실패");
        MessageBox(g_hMainWindow, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
    }
}

Player::~Player()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void Player::Render(Gdiplus::Graphics* InGraphics)
{
    if (Image)
    {
        // g_PlayerImage가 로딩되어 있다.
        InGraphics->DrawImage(
            Image,          // 그려질 이미지
            static_cast<int>(Position.X - PixelSize * Pivot.X),    // 그려질 위치
            static_cast<int>(Position.Y - PixelSize * Pivot.Y),
            PixelSize, PixelSize);  // 그려질 사이즈
    }
    else
    {
        Gdiplus::SolidBrush RedBrush(Gdiplus::Color(255, 255, 0, 0));
        InGraphics->FillEllipse(
            &RedBrush,
            100, 100,
            PixelSize, PixelSize);
    }
}

void Player::HandleKeyState(WPARAM InKey, bool InIsPressed)
{
    if (InKey == VK_LEFT || InKey == VK_RIGHT)
    {
        KeyWasPressedMap[static_cast<InputDirection>(InKey)] = InIsPressed;

        if (InKey == VK_LEFT)
        {
            Position.X -= Speed;
            if (Position.X < (0 + PixelSize))
            {
                Position.X = 0 + PixelSize;
            }
            InvalidateRect(g_hMainWindow, nullptr, FALSE);
        }
        else if (InKey == VK_RIGHT)
        {
            Position.X += Speed;
            if ((g_ScreenSize.X - PixelSize) < Position.X)
            {
                Position.X = static_cast<float>(g_ScreenSize.X - PixelSize);
            }
            InvalidateRect(g_hMainWindow, nullptr, FALSE);
        }
    }
}
