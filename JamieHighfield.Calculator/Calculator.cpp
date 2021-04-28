#include "Calculator.h";

// Global variables
HINSTANCE m_hInstance;
const LPCWSTR title = L"Calculator";
ATOM m_whiteFrame = NULL;

HBITMAP logo = NULL;

/// <summary>
/// The main entry point of the application.
/// </summary>
BOOL APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (!InitMainWindow(hInstance, nCmdShow)) {
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(m_hInstance, MAKEINTRESOURCE(L"Calculator"));

	MSG message;
	while (GetMessage(&message, nullptr, 0, 0)) {
		if (!TranslateAccelerator(message.hwnd, hAccelTable, &message)) {
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
}

/// <summary>
/// Stats the main window of the application.
/// </summary>
BOOL InitMainWindow(HINSTANCE hInstance, int nCmdShow) {
	WNDCLASSEXW wndClass = { 0 };

	wndClass.cbSize = sizeof(wndClass);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	wndClass.lpszClassName = L"Calculator"; // window class name, not title
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wndClass.hIconSm = LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;

	if (!RegisterClassExW(&wndClass)) {
		InitFailed(hInstance);
		return FALSE;
	}

	wndClass = { 0 };
	wndClass.cbSize = sizeof(wndClass);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = m_hInstance;
	wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = L"myframe";
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.hIconSm = NULL;
	wndClass.lpfnWndProc = FrameProc;
		
	m_whiteFrame = RegisterClassEx(&wndClass);

	if (!m_whiteFrame) {
		InitFailed(hInstance);
		return FALSE;
	}

	m_hInstance = hInstance;

	POINT pt = { 0 };
	SIZE dm = { 0 };
	dm.cx = 300;
	dm.cy = 300;
	GetCenterStartPos(dm, &pt);
	INT32 styles = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_POPUP | WS_MINIMIZEBOX);
	HWND hWnd = CreateWindowW(L"Calculator", title, styles, pt.x, pt.y, 300, 300, nullptr, nullptr, m_hInstance, nullptr);

	if (hWnd == NULL || !hWnd) {
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

/// <summary>
/// The main message loop for the application.
/// </summary>
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
		case WM_COMMAND: {
			switch (LOWORD(wParam)) {
				case ID_FILE_EXIT: {
					ExitProcess(0); // 0 exit code for successful exit
					break;
				}
				case ID_HELP_ABOUTCALCULATOR: {
					logo = LoadBitmap((HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), MAKEINTRESOURCE(IDB_PNG1));
					DialogBox(m_hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DialogProc);
					break;
				}
			}
			break;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
    }
    return FALSE;
}

/// <summary>
/// The main message loop for dialogs.
/// </summary>
BOOL __stdcall CALLBACK DialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
		{
			RECT rect;
			GetWindowRect(hWnd, &rect);

			int width = rect.right - rect.left;
			int height = rect.bottom - rect.top;

			HWND frame = CreateWindowExA(0, (LPCSTR)m_whiteFrame, "", WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN, 0, 0, width, height - 87, hWnd, (HMENU)1, m_hInstance, 0);
			SetSysFont(GetDlgItem(hWnd, 2));

			HWND hwndLabel = CreateWindowEx(NULL, L"STATIC",
				L"Calculator\n\nCopyright © Jamie Highfield 2021. All rights reserved.\n\nLicensed under the MIT license.",
				WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_CLIPSIBLINGS,
				15, 15, width - 47, 85,
				frame,
				NULL,
				NULL,
				NULL);

			SetSysFont(hwndLabel);

			EnableMenuItem(GetSystemMenu(hWnd, FALSE), SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);

			return TRUE;
		}
		case WM_COMMAND:
		{
			switch (LOWORD(wParam)) {
				case 2:
				{
					EndDialog(hWnd, LOWORD(wParam));
					return (INT_PTR)TRUE;
				}
				default: {
					break;
				}
			}
		}
		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return FALSE;
}

/// <summary>
/// The main message loop for a window frame.
/// </summary>
LRESULT __stdcall FrameProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HBRUSH hbrush = NULL;
	switch (message) {
		case WM_CTLCOLORSTATIC: {
			HDC hdcStatic = (HDC)wParam;

			SetBkColor(hdcStatic, RGB(255, 255, 255));
			if (!hbrush) {
				hbrush = CreateSolidBrush(RGB(255, 255, 255));
			}

			return (LRESULT)hbrush;
		}
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		default: {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return FALSE;
}