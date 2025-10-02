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

enum class RenderLayer : uint8_t
{
	Background = 0,
	Player,
	Bomb,
	UI,
	Test,
	Misc
};

enum class ResourceID : uint8_t
{
	None = 0,
	Player,
	Bomb,
	Background,
	Number0,
	Number1,
	Number2,
	Number3,
	Number4,
	Number5,
	Number6,
	Number7,
	Number8,
	Number9,
	Dot,
	Test,
	// 이미지가 추가되면 enum 추가
};

enum class CollisionType
{
	Circle,
	Rectangle
};

enum class PhysicsLayer
{
	None = 0,
	Player,
	Bomb
};

enum class GameState
{
	Playing,
	GameOver
};