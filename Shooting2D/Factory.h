#pragma once
#include <type_traits>
#include "Singleton.h"
#include "enums.h"

// Actor 생성 전담 클래스
class Factory : public Singleton<Factory>
{
	friend class Singleton<Factory>;

public:
	// std::enable_if = std::is_base_of<Actor,T>::value가 true면 T*로 만들어라
	// std::is_base_of<Actor,T> = Actor가 T타입의 부모냐? 그 결과가 ::value에 들어간다.
	template <typename T>
	typename std::enable_if<std::is_base_of<Actor,T>::value, T*>::type
	SpawnActor(ResourceID InID, RenderLayer InLayer = RenderLayer::Misc)
	{
		T* NewActor = new T(InID);
		NewActor->SetRenderLayer(InLayer);

		return NewActor;
	}

private:
	Factory() = default;
	virtual ~Factory() = default;
};