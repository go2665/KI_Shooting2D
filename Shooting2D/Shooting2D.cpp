// Shooting2D.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "Shooting2D.h"

//#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC
//#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);  // 사용 안하는 파라메터 명시적으로 표시
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    
    // GDI+ 초기화
    ULONG_PTR Token;
    Gdiplus::GdiplusStartupInput StartupInput;
    Gdiplus::GdiplusStartup(&Token, &StartupInput, nullptr); 

    ResourceManager::Get().Initialize();    // GameManager보다 먼저 초기화 되어야 함
    GameManager::Get().Initialize();

    //TestCollisionActor* Test1 = Factory::Get().SpawnActor<TestCollisionActor>(ResourceID::Test);
    //Test1->SetPosition(100, 100);
    //TestCollisionActor* Test2 = Factory::Get().SpawnActor<TestCollisionActor>(ResourceID::Test);
    //Test2->SetPosition(140, 140);

    //Test1->PrintTestResult(Test2);

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SHOOTING2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);                 // 1. 윈도우 클래스 등록

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))    // 2. 윈도우 실제 생성 및 초기화
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SHOOTING2D));

    MSG msg;
    ULONGLONG LastTime = GetTickCount64();

    // 3. 메시지 루프
    // 기본 메시지 루프입니다:(메세지 큐에 들어온 메세지들을 하나씩 처리하는 부분)
    while (true)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) // 종료 메시지가 나오면 그냥 종료
                break;

            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) // 단축키 처리
            {
                TranslateMessage(&msg); // 메시지를 메시지 프로시저로 보내 메시지를 처리한다.
                DispatchMessage(&msg);
            }
        }

        ULONGLONG CurrentTime = GetTickCount64();
        float DeltaTime = (CurrentTime - LastTime) / 1000.0f;   // 결과를 초 단위로 변경
        LastTime = CurrentTime;

        GameManager::Get().Tick(DeltaTime);

        InvalidateRect(GameManager::Get().GetMainWindowHandle(), 
            nullptr, FALSE); // 매 프레임마다 WM_PAINT요청
    }

    GameManager::Get().Destroy();
    ResourceManager::Get().Destroy();

    // GDI+ 정리하기
    Gdiplus::GdiplusShutdown(Token);    
    return (int) msg.wParam;
}

//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    // 윈도우의 모양과 기본동작 등을 결정
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;  // 윈도우 프로시저 함수 등록
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SHOOTING2D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = nullptr; // 메뉴 제거
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   // 클라이언트 영역의 크기를 원하는 크기로 조절하기
   RECT rc = { 0,0, GameManager::ScreenWidth, GameManager::ScreenHeight };

   AdjustWindowRectEx(&rc, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME, FALSE, 0);

   const Point StartPosition = GameManager::Get().GetAppPosition();

   // 실제 윈도우 생성
   HWND hWnd = CreateWindowW(szWindowClass,
       L"2D Shooting for GDI+", 
       // WS_OVERLAPPEDWINDOW에서 
       // WS_MAXIMIZEBOX(최대화 버튼 비활성화)와 WS_THICKFRAME(테두리잡고 크기 변경 금지)만 제외
       WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX & ~WS_THICKFRAME,   
       StartPosition.X, StartPosition.Y,   // 시작 좌표(스크린 좌표계)
       rc.right - rc.left, rc.bottom - rc.top,    // 크기(윈도우 스타일에 맞춰 재조정된 크기)
       nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   GameManager::Get().SetMainWindowHandle(hWnd);    // 게임메니저에 핸들 설정
   ShowWindow(hWnd, nCmdShow);  // 윈도우 보여주기
   UpdateWindow(hWnd);          // 윈도우 업데이트하기(윈도우 화면 갱신)


   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    //case WM_CREATE:
    //    // 윈도우가 생성되었을때 날아오는 메시지        
    //    break;
    case WM_DESTROY:
        // 윈도우가 삭제되었을 때 날아오는 메세지        
        PostQuitMessage(0);
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            GameManager::Get().Render();
            Gdiplus::Graphics GraphicsInstance(hdc);    // Graphics객체 만들기(hdc에 그리기 위한 도구 만들기)
            GraphicsInstance.DrawImage(GameManager::Get().GetBackBuffer(), 0, 0);

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_ERASEBKGND:
        // 화면을 지워야 할 때 날라온 메시지
        return 1;   // 배경지우기 방지(백버퍼 사용하고 있기 때문에)
    case WM_KEYDOWN:
        GameManager::Get().HandleKeyState(wParam, true);
        switch (wParam)
        {        
        case VK_ESCAPE:
            DestroyWindow(hWnd);    // hWnd 창을 닫아라 -> 프로그램을 꺼라(WM_DESTROY메시지가 들어간다.)
        }
        break;
    case WM_KEYUP:
        GameManager::Get().HandleKeyState(wParam, false);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 실습
// 1. TestGridActor만들기 -> 50픽셀 단위로 점찍어서 위치 확인 쉽게 할 수 있게 해주는 클래스
// 2. TestHouseActor만들기 -> 집모양 그려주는 클래스



// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
