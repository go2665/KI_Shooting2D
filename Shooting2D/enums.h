#pragma once
#include <Windows.h>
#include <cstdint>

enum class InputDirection : uint8_t
{
	None = 0,
	Up = VK_UP,
	Down = VK_DOWN,
	Left = VK_LEFT,
	Right = VK_RIGHT
};

enum class RenderLayer
{
	Background = 0,
	Player,
	Bomb,
	UI,
	Test,
	Misc
};