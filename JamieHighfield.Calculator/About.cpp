//#include "About.h";
//
//// Global variables
//HINSTANCE m_aboutHInstance;
//const LPCWSTR title = L"About Calculator";
//
//BOOL OpenAboutDlg(HWND hWnd) {
//	return TRUE;
//
//	WNDCLASSEXW wndClass = { 0 };
//
//	wndClass.cbSize = sizeof(wndClass);
//	wndClass.cbClsExtra = 0;
//	wndClass.cbWndExtra = 0;
//	wndClass.hInstance = hInstance;
//	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
//	wndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
//	wndClass.lpszClassName = L"About"; // window class name, not title
//	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	wndClass.hIconSm = LoadIcon(wndClass.hInstance, MAKEINTRESOURCE(IDI_ICON1));
//	wndClass.style = CS_HREDRAW | CS_VREDRAW;
//	wndClass.lpfnWndProc = WndProc;
//
//	if (!RegisterClassExW(&wndClass)) {
//		/*TaskDialog(
//			NULL,
//			hInstance,
//			L"Calculator",
//			L"Unable to start Calculator",
//			L"Windows was unable to create the main window for Calculator and Calculator was therefore unable to start.",
//			TDCBF_OK_BUTTON,
//			TD_WARNING_ICON,
//			NULL);*/
//	}
//
//	m_aboutHInstance = hInstance;
//
//	
//	INT32 styles = (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_POPUP);
//	HWND hWnd = CreateWindowW(L"About", title, styles, CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, nullptr, nullptr, m_hInstance, nullptr);
//
//	if (hWnd == NULL || !hWnd) {
//		return FALSE;
//	}
//
//	ShowWindow(hWnd, nCmdShow);
//	UpdateWindow(hWnd);
//
//	return TRUE;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
//switch (message)
//{
//case WM_COMMAND:
//{
//
//    break;
//}
//case WM_PAINT:
//{
//    PAINTSTRUCT ps;
//    HDC hdc = BeginPaint(hWnd, &ps);
//    // TODO: Add any drawing code that uses hdc here...
//    EndPaint(hWnd, &ps);
//}
//break;
//case WM_DESTROY:
//    PostQuitMessage(0);
//    break;
//default:
//    return DefWindowProc(hWnd, message, wParam, lParam);
//}
//return 0;
//}