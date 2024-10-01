#include "WinMainCMake.h"
#include "framework.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Control Handles
HWND hStatusCtrl, hListCtrl, hStatic1, hStatic2;
RECT rECT;
HDWP hDWP;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: 在此处放置代码。

	// 初始化全局字符串
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_WIN32GUI, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32GUI));

	MSG msg;

	// 主消息循环:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32GUI));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_WIN32GUI);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 将实例句柄存储在全局变量中

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	// Static Image
	hStatic1 = CreateWindowEx(WS_OVERLAPPED, TEXT("Static"), nullptr,
		WS_VISIBLE | WS_CHILD | SS_GRAYRECT, 10, 10, 400, 300, hWnd, HMENU(1000), hInstance, 0);
	hStatic2 = CreateWindowEx(WS_OVERLAPPED, TEXT("Static"), nullptr,
		WS_VISIBLE | WS_CHILD | SS_GRAYRECT, 10, 10, 400, 300, hWnd, HMENU(1001), hInstance, 0);
	// List view
	hListCtrl = CreateWindowEx(WS_EX_CLIENTEDGE, TEXT("SysListView32"), nullptr,
		WS_VISIBLE | WS_CHILD | LVS_REPORT, 10, 10, 400, 300, hWnd, HMENU(1002), hInstance, 0);
	LVCOLUMN lvCol{ 0 };
	lvCol.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
	lvCol.iSubItem = 0;
	lvCol.cx = 100;
	lvCol.pszText = (LPTSTR)TEXT("Name");
	ListView_InsertColumn(hListCtrl, 0, &lvCol);

	lvCol.iSubItem = 1;
	lvCol.cx = 100;
	lvCol.pszText = (LPTSTR)TEXT("Param");
	ListView_InsertColumn(hListCtrl, 1, &lvCol);

	lvCol.iSubItem = 2;
	lvCol.cx = 100;
	lvCol.pszText = (LPTSTR)TEXT("Value");
	ListView_InsertColumn(hListCtrl, 2, &lvCol);

	LVITEM lvItem{ 0 };
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE;
	lvItem.iItem = 0;
	lvItem.iSubItem = 0;
	lvItem.pszText = (LPTSTR)TEXT("Name1");
	lvItem.iImage = 0;
	ListView_InsertItem(hListCtrl, &lvItem);

	lvItem.iSubItem = 1;
	lvItem.pszText = (LPTSTR)TEXT("Param1");
	SendMessage(hListCtrl, LVM_SETITEMTEXT, 0, (LPARAM)&lvItem);

	lvItem.iSubItem = 2;
	lvItem.pszText = (LPTSTR)TEXT("Value1");
	SendMessage(hListCtrl, LVM_SETITEMTEXT, 0, (LPARAM)&lvItem);

	lvItem.iItem = 1;
	lvItem.iSubItem = 0;
	lvItem.pszText = (LPTSTR)TEXT("Name2");
	lvItem.iImage = 0;
	ListView_InsertItem(hListCtrl, &lvItem);

	lvItem.iSubItem = 1;
	lvItem.pszText = (LPTSTR)TEXT("Param2");
	SendMessage(hListCtrl, LVM_SETITEMTEXT, 1, (LPARAM)&lvItem);

	lvItem.iSubItem = 2;
	lvItem.pszText = (LPTSTR)TEXT("Value2");
	SendMessage(hListCtrl, LVM_SETITEMTEXT, 1, (LPARAM)&lvItem);

	// Status bar
	hStatusCtrl = CreateWindowEx(WS_OVERLAPPED, TEXT("msctls_statusbar32"), nullptr,
		WS_VISIBLE | WS_CHILD, 0, 0, 0, 0, hWnd, HMENU(1003), hInstance, 0);
	int array[3]{ 100,200,-1 };
	SendMessage(hStatusCtrl, SB_SETPARTS, 3, (LPARAM)array);
	SendMessage(hStatusCtrl, SB_SETTEXT, 0, (LPARAM)TEXT("Status1"));
	SendMessage(hStatusCtrl, SB_SETTEXT, 1, (LPARAM)TEXT("Status2"));
	SendMessage(hStatusCtrl, SB_SETTEXT, 2, (LPARAM)TEXT("Status3"));

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: 在此处添加使用 hdc 的任何绘图代码...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_SIZE:
		// Change pos of status bar
		SendMessage(hStatusCtrl, WM_SIZE, 0, 0);
		GetClientRect(hWnd, &rECT);
		// Change pos of list view
		hDWP = BeginDeferWindowPos(1);
		DeferWindowPos(hDWP, hListCtrl, NULL, (rECT.right - rECT.left) * 3 / 4 + 10, 10, (rECT.right - rECT.left) * 1 / 4 - 20, (rECT.bottom - rECT.top) - 40, SWP_NOZORDER);
		EndDeferWindowPos(hDWP);
		// 
		// Change pos of static image field
		hDWP = BeginDeferWindowPos(1);
		DeferWindowPos(hDWP, hStatic1, NULL, 10, 10, (rECT.right - rECT.left) * 3 / 4 - 20, (rECT.bottom - rECT.top) / 2 - 40, SWP_NOZORDER);
		EndDeferWindowPos(hDWP);

		hDWP = BeginDeferWindowPos(1);
		DeferWindowPos(hDWP, hStatic2, NULL, 10, 10 + (rECT.bottom - rECT.top) / 2, (rECT.right - rECT.left) * 3 / 4 - 20, (rECT.bottom - rECT.top) / 2 - 40, SWP_NOZORDER);
		EndDeferWindowPos(hDWP);
		// 
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}