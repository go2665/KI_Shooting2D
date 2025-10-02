#pragma once
#include <unordered_map>
#include "Common.h"
#include "Singleton.h"

class ResourceManager : public Singleton<ResourceManager>
{
	friend class Singleton<ResourceManager>;

public:
	void Initialize();
	void Destroy();

	Gdiplus::Bitmap* GetImage(ResourceID InID);

private:
	// Singleton : 클래스의 인스턴스가 1개만 있는 클래스. 
	// private에 생성자를 넣어서 밖에서 인스턴스화 하는 것을 원천적으로 봉쇄
	ResourceManager() = default;
	virtual ~ResourceManager() = default;
	
	bool LoadResourceFromFile(ResourceID InID, const wchar_t* path);	// 파일에서 리소스를 로딩하는 함수

	std::unordered_map<ResourceID, Gdiplus::Bitmap*> Resources;	// 모든 리소스가 다 들어있는 맵
};

