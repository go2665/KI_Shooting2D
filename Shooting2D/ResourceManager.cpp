#include "ResourceManager.h"
#include "GameManager.h"

void ResourceManager::Initialize()
{
    Resources[ResourceID::None] = nullptr;
    LoadResourceFromFile(ResourceID::Player, L"./Images/Airplane.png");
    LoadResourceFromFile(ResourceID::Bomb, L"./Images/Bomb.png");
    LoadResourceFromFile(ResourceID::Background, L"./Images/Background.png");
    LoadResourceFromFile(ResourceID::Number0, L"./Images/Number0.png");
    LoadResourceFromFile(ResourceID::Number1, L"./Images/Number1.png");
    LoadResourceFromFile(ResourceID::Number2, L"./Images/Number2.png");
    LoadResourceFromFile(ResourceID::Number3, L"./Images/Number3.png");
    LoadResourceFromFile(ResourceID::Number4, L"./Images/Number4.png");
    LoadResourceFromFile(ResourceID::Number5, L"./Images/Number5.png");
    LoadResourceFromFile(ResourceID::Number6, L"./Images/Number6.png");
    LoadResourceFromFile(ResourceID::Number7, L"./Images/Number7.png");
    LoadResourceFromFile(ResourceID::Number8, L"./Images/Number8.png");
    LoadResourceFromFile(ResourceID::Number9, L"./Images/Number9.png");
    LoadResourceFromFile(ResourceID::Dot, L"./Images/Dot.png");
}

void ResourceManager::Destroy()
{
    for (auto& pair : Resources)
    {
        delete pair.second; // 로드한 비트맵 모두 지우기
    }
    Resources.clear();
}

Gdiplus::Bitmap* ResourceManager::GetImage(ResourceID InID)
{
    auto iter = Resources.find(InID);   // 안전하게 가기
    if (iter != Resources.end())
    {
        return iter->second;
    }
    return nullptr;

    //return Resources[InID]; // 이렇게 해도 큰 문제는 없다.
}

bool ResourceManager::LoadResourceFromFile(ResourceID InID, const wchar_t* path)
{
    bool Result = false;
    if (path)
    {
        Gdiplus::Bitmap* Image = new Gdiplus::Bitmap(path); // 이미지 로딩
        if (Image->GetLastStatus() != Gdiplus::Ok)
        {
            // 정상적으로 파일 로딩이 안됬다.
            delete Image;       // 실패했으면 즉시 해제
            Image = nullptr;
            OutputDebugString(L"이미지 로드 실패");
            MessageBox(GameManager::Get().GetMainWindowHandle(),
                L"이미지 로드 실패", L"오류", MB_OK | MB_ICONERROR);
        }
        else
        {
            Resources[InID] = Image;
            Result = true;
        }
    }

    return Result;;
}
