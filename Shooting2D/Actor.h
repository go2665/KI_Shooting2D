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

	void DestroyActor();

	virtual void OnInitialize() {};
	virtual void OnDestroy() {};
	virtual void OnTick(float InDeltaTime);
	virtual void OnRender(Gdiplus::Graphics* InGraphics);

	virtual void OnOverlap(Actor* InOther) {};	// 다른 액터와 겹쳤을 때 자동호출 되는 함수

	void AddComponent(Component* InComponent);
	void RemoveComponent(Component* InComponent);

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

