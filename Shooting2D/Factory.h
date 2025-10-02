#pragma once
#include <type_traits>
#include "Singleton.h"
#include "enums.h"

// Actor ���� ���� Ŭ����
class Factory : public Singleton<Factory>
{
	friend class Singleton<Factory>;

public:
	// std::enable_if = std::is_base_of<Actor,T>::value�� true�� T*�� ������
	// std::is_base_of<Actor,T> = Actor�� TŸ���� �θ��? �� ����� ::value�� ����.
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