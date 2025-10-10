#pragma once
#include <type_traits>
#include <vector>
#include "Common.h"
#include "Component.h"

class Actor
{
public:
	Actor() = delete;
	Actor(ResourceID InID);	// 무조건 파일 경로를 받아야 생성할 수 있다. -> ID를 통해 리소스 매니저에서 비트맵을 받아 오도록 처리
	virtual ~Actor() = default;

	// 자기 자신을 제거하도록 요청하는 함수
	void DestroyActor();

	// 생성되었을 때의 할일
	virtual void OnInitialize() {};
	// 제거 될 때에 할일
	virtual void OnDestroy();
	// 틱마다 할일
	virtual void OnTick(float InDeltaTime);
	// 그릴 때마다 할일
	virtual void OnRender(Gdiplus::Graphics* InGraphics);

	// 물리 컴포넌트가 있을 때만 처리
	virtual void OnOverlap(Actor* InOther) {};	// 다른 액터와 겹쳤을 때 자동호출 되는 함수

	// 컴포넌트 추가하는 함수
	void AddComponent(Component* InComponent);
	// 컴포넌트 제거하는 함수
	void RemoveComponent(Component* InComponent);

	// 컴포넌트 리턴용 탬플릿 함수
	template<typename T>
	T* GetComponent() const
	{
		static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
		for (auto comp : Components)
		{
			T* castComp = dynamic_cast<T*>(comp);
			if (castComp)
			{
				return castComp;
			}
		}
		return nullptr;
	}
	// 컴포넌트 확인용 탬플릿 함수
	template<typename T>
	bool HasComponent() const
	{
		return GetComponent<T>() != nullptr;
	}
	

	// Getter
	inline const PointF& GetPosition() const { return Position; }
	inline int GetSize() const { return Size; }
	inline const PointF& GetPivot() const { return Pivot; }
	inline const RenderLayer GetRenderLayer() const { return TargetRenderLayer; }

	// Setter
	inline void SetPosition(float InX, float InY) { Position.X = InX; Position.Y = InY; }
	inline void SetSize(int InSize) { Size = InSize; }
	inline void SetPivot(float InX, float InY) { Pivot.X = InX; Pivot.Y = InY; }
	inline void SetRenderLayer(RenderLayer InLayer) { TargetRenderLayer = InLayer; }

protected:
	// 위치
	PointF Position = { 0.0f, 0.0f };

	// 각도
	float Angle = 0.0f;

	// 크기
	int Size = 64;

	// 중심점
	PointF Pivot = { 0.5f, 0.5f }; // Pivot 기본 값은 한가운데

	// 이미지가 들어있을 비트맵
	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이		

	// 이미지가 그려질 레이어
	RenderLayer TargetRenderLayer = RenderLayer::Misc;

	// 이 액터에 속한 컴포넌트들
	std::vector<Component*> Components;

private:
	bool IsPendingDestroy = false;		// 삭제 예정인 액터인지 표시
};

