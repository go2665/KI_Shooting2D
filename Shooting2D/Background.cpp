#include "Background.h"

Background::Background(const wchar_t* InImagePath)
{
    Pivot.X = 0;    // 왼쪽 위가 피봇
    Pivot.Y = 0;
    Image = new Gdiplus::Bitmap(InImagePath); // 이미지 로딩
    if (Image->GetLastStatus() != Gdiplus::Ok)
    {
        // 정상적으로 파일 로딩이 안됬다.
        delete Image;       // 실패했으면 즉시 해제
        Image = nullptr;
        OutputDebugString(L"플레이어 이미지 로드 실패");
        MessageBox(g_hMainWindow, L"플레이어 이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
    }
}

Background::~Background()
{
    if (Image)
    {
        delete Image;
        Image = nullptr;
    }
}

void Background::Tick(float InDeltaTime)
{
    Offset += Speed * InDeltaTime;
}

void Background::Render(Gdiplus::Graphics* InGraphics)
{
    if (Image)
    {
        // Image가 로딩되어 있다.
        int NewY = static_cast<int>(Position.Y - PixelSize * Pivot.Y + Offset);
        if (Offset > g_ScreenSize.Y)
        {
            Offset = -PixelSize;
        }

        int WidthCount = g_ScreenSize.X / PixelSize + 1;
        int HeightCount = g_ScreenSize.Y / PixelSize + 2;
        int TotalHeight = (PixelSize - 3) * HeightCount;

        for (int y = -1; y < HeightCount; y++)
        {            
            for (int x = 0; x < WidthCount; x++)
            {
                int NewX = static_cast<int>(Position.X - PixelSize * Pivot.X + (PixelSize - 3) * x);
                InGraphics->DrawImage(
                    Image,          // 그려질 이미지
                    NewX,           // 그려질 위치
                    NewY,
                    PixelSize, PixelSize);  // 그려질 사이즈
            }
            NewY += (PixelSize - 3);
            if (NewY > TotalHeight)
            {
                NewY -= (TotalHeight + (PixelSize - 3));
            }
        }        
    }
}