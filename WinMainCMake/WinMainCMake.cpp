#include "WinMainCMake.h"
#include "framework.h"
// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Desktop Application");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Control Handles
HWND hStatusCtrl, hListCtrl, hStatic1, hStatic2;
RECT rECT;
HDWP hDWP;
HDC textLabel;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    // Add custom control
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
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


    switch (message)
    {
    case WM_PAINT:
        PAINTSTRUCT ps;
        GetClientRect(hWnd, &rECT);
        textLabel = BeginPaint(hWnd, &ps);

        // Here your application is laid out.
        // For this introduction, we just print out "Hello, Windows desktop!"
        // in the top left corner.
        TextOut(textLabel,
            rECT.left + 5, rECT.top + 5,
            _T("Program started"), _tcslen(_T("Program started")));
        // End application-specific layout section.
        EndPaint(hWnd, &ps);
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
        DeferWindowPos(hDWP, hStatic1, NULL, 10, 30, (rECT.right - rECT.left) * 3 / 4 - 20, (rECT.bottom - rECT.top) / 2 - 40, SWP_NOZORDER);
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
        break;
    }

    return 0;
}