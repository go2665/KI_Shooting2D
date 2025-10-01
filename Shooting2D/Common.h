#pragma once

#include <Windows.h>
#include <gdiplus.h>

using Point = Gdiplus::Point;
using PointF = Gdiplus::PointF;

extern HWND g_hMainWindow; // g_hMainWindow가 다른 파일에 있다는 것을 알려줌
extern Gdiplus::Point g_ScreenSize;
