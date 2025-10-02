#include "UserInterface.h"
#include "GameManager.h"

void UserInterface::UpdatePosition()
{
	// 앵커와 피봇을 고려	해 위치를 업데이트
	GameManager& gameManager = GameManager::Get();
	Position.X = anchoredPosition.x + (anchor.X * gameManager.ScreenWidth) - (Pivot.X * width);
	Position.Y = anchoredPosition.y + (anchor.Y * gameManager.ScreenHeight) - (Pivot.Y * height);
}
