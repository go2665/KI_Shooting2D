#include "Background.h"

Background::Background(const wchar_t* InImagePath)
    :Actor(InImagePath)
{
    Pivot.X = 0;    // 왼쪽 위가 피봇
    Pivot.Y = 0;    
}

void Background::OnTick(float InDeltaTime)
{
    Offset += ScrollSpeed * InDeltaTime;
}

void Background::OnRender(Gdiplus::Graphics* InGraphics)
{
    constexpr int PixelGap = 3;
    if (Image)
    {
        // Image가 로딩되어 있다.
        int NewY = static_cast<int>(Position.Y - Size * Pivot.Y + Offset);
        if (Offset > g_ScreenSize.Y)
        {
            Offset = -static_cast<float>(Size);
        }

        int WidthCount = g_ScreenSize.X / Size + 1;     // +1은 화면 밖까지 타일을 그리기 위해 추가
        int HeightCount = g_ScreenSize.Y / Size + 2;    // +2는 화면 밖까지 타일을 그리기 위해 추가
        int TotalHeight = (Size - PixelGap) * HeightCount;

        for (int y = -1; y < HeightCount; y++)
        {            
            for (int x = 0; x < WidthCount; x++)
            {
                int NewX = static_cast<int>(Position.X - Size * Pivot.X + (Size - PixelGap) * x);
                InGraphics->DrawImage(
                    Image,          // 그려질 이미지
                    NewX,           // 그려질 위치
                    NewY,
                    Size, Size);  // 그려질 사이즈
            }
            NewY += (Size - PixelGap);
            if (NewY > TotalHeight)
            {
                NewY -= (TotalHeight + (Size - PixelGap));
            }
        }        
    }
}