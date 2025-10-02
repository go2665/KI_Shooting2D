#include "Bomb.h"
#include "GameManager.h"
//#include <string>

void Bomb::OnInitialize()
{
	dropSpeed = 0.0f; // 초기 드랍 속도 설정

	SetSize(GameManager::ActorDefaultSize / 2); // 크기 설정

	float HalfSize = Size * 0.5f;
	Position.X = static_cast<float>(HalfSize + rand() % (GameManager::ScreenWidth - Size)); // 랜덤 X 위치 설정
	Position.Y = static_cast<float>(-Size); // 화면 위쪽에서 시작

	//std::string debugMessage = "Bomb::position.X : " + std::to_string(position.X) + "\n";
	//OutputDebugStringA(debugMessage.c_str());

	Angle = 180.0f;	// 회전 설정

	PhysicsComponent* physicsComponent = new PhysicsComponent(this, CollisionType::Rectangle, PhysicsLayer::Bomb);
	physicsComponent->SetWidth(static_cast<float>(HalfSize));
	physicsComponent->SetHeight(HalfSize * 0.75f);
	AddComponent(physicsComponent); // 물리 컴포넌트 추가
}

void Bomb::OnTick(float deltaTime)
{
	Actor::OnTick(deltaTime); // 부모 클래스의 OnTick 호출

	dropSpeed += dropAcceleration * deltaTime; // 드랍 속도 업데이트
	//std::string debugMessage = "Bomb::OnTick called with deltaTime: " + std::to_string(dropSpeed) + "\n";
	//OutputDebugStringA(debugMessage.c_str());

	Position.Y += dropSpeed * deltaTime; // Y 위치 업데이트

	lifetime -= deltaTime; // 수명 감소

	// 화면 밖으로 나가거나 수명이 다 된 경우 액터 삭제
	if (Position.Y > GameManager::ScreenHeight + Size || lifetime < 0.0f)
	{
		DestroyActor();
	}
}

void Bomb::OnOverlap(Actor* other)
{
	if (other && other != this)
	{
		// 폭탄과 다른 액터가 겹칠 때 처리
		// 예: 폭탄이 플레이어와 겹치면 플레이어에게 피해를 주거나 게임 오버 처리
		OutputDebugString(L"Bomb::OnOverlap called\n");
		
		// 폭탄 삭제
		DestroyActor();
	}
}

