#pragma once
#include "Common.h"

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

	// 크기
	int Size = 64;

	// 중심점
	PointF Pivot = { 0.5f, 0.5f }; // Pivot 기본 값은 한가운데

	// 이미지가 들어있을 비트맵
	Gdiplus::Bitmap* Image = nullptr;   // 플레이어가 그려질 종이		

	// 이미지가 그려질 레이어
	RenderLayer TargetRenderLayer = RenderLayer::Misc;

private:
	bool IsPendingDestroy = false;		// 삭제 예정인 액터인지 표시
};

