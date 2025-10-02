#include "TimerUI.h"
#include "ResourceManager.h"
#include "GameManager.h"

void TimerUI::OnInitialize()
{
	Actor::OnInitialize();	// 부모 클래스의 OnInitialize 호출
	
	SetSize(GameManager::ActorDefaultSize * 0.5f);	// 크기 설정
	anchoredPosition = { -10, 10 };			// 앵커를 기준으로한 위치 설정
	anchor = { 1.0f, 0.0f };				// 앵커 포인트를 오른쪽 상단으로 설정
	Pivot = { 1.0f, 0.0f };					// 피봇 포인트를 오른쪽 상단으로 설정
	width = Size * 4;
	height = Size;							// 전체 너비는 4자리(0.00) * size, 높이는 size로 설정
	UpdatePosition();
	
	digits.reserve(3);			// 최소 3개 자리 숫자를 저장할 수 있도록 벡터 예약(0.00)
	digitImages.reserve(10);	// 0부터 9까지의 숫자 이미지 예약
	// 0부터 9까지의 숫자 이미지 로드
	for (int i = 0; i < 10; ++i)
	{
		digitImages.push_back(ResourceManager::Get().GetImage(static_cast<ResourceID>(static_cast<int>(ResourceID::Number0) + i)));
	}
	dotImage = ResourceManager::Get().GetImage(ResourceID::Dot); // 소수점 이미지 로드
}

void TimerUI::OnTick(float deltaTime)
{
	Actor::OnTick(deltaTime);
	elapsedTime += deltaTime; // 경과 시간 업데이트
	SetNumber(elapsedTime); // 목표 숫자를 설정. 
}

void TimerUI::OnRender(Gdiplus::Graphics* graphics)
{
	if (!graphics) return;

	int digitCount = static_cast<int>(digits.size());
	int indexOffset = digitCount;
	for(int i = 0; i < digitCount; ++i)
	{
		if (i == 2)
		{
			// 소수점 그리기
			graphics->DrawImage(dotImage, static_cast<int>(Position.X) + indexOffset * Size, static_cast<int>(Position.Y), Size, Size);
			indexOffset--;
		}

		RenderDigit(graphics, digits[i], indexOffset); // 각 자리 숫자 렌더링. digits에는 자리수가 역으로 저장되어 있으므로, 가장 높은 자리부터 렌더링
		indexOffset--;
	}
}

void TimerUI::SetNumber(float number)
{
	if (targetNumber != number)
	{
		targetNumber = number; // 목표 숫자 업데이트

		digits.clear(); // 이전에 저장된 숫자 제거
		int number = static_cast<int>(targetNumber * 100.0f); // 소수점 둘째 자리까지 고려. 그 아래는 버림 처리
		do
		{
			digits.push_back(number % 10);	// 현재 자리 숫자를 추가
			number /= 10;					// 다음 자리로 이동
		} while (number > 0);	// 모든 자리 숫자를 처리할 때까지 반복(targetNumber가 시작부터 0인 경우를 대비해 do-while사용)

		// 최소 0.00출력이 되어야 한다.
		const int minimumDigits = 3; // 최소 3자리 숫자(0.00) 보장
		int paddingCount = minimumDigits - (int)digits.size();
		for(int i = 0; i < paddingCount; ++i)
		{
			digits.push_back(0);	// 부족한 자리수는 0으로 채움
		}

		SetWidth(Size * (static_cast<int>(digits.size()) + 1)); // 너비는 size * (자리수 + 소수점 자리)
	}
}

void TimerUI::RenderDigit(Gdiplus::Graphics* graphics, int digit, unsigned int index)
{
	if( digit < 0 || digit > 9 )
	{
		return; // 유효하지 않은 인덱스나 숫자 처리
	}

	// 피봇은 왼쪽 상단으로 설정
	graphics->DrawImage(digitImages[digit], static_cast<int>(Position.X) + index * Size, static_cast<int>(Position.Y), Size, Size);
}