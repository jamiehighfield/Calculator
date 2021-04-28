#pragma once
#pragma comment(lib, "comctl32.lib")
#pragma comment(linker,"\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <SDKDDKVer.h>;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>;
#include <stdlib.h>;
#include <malloc.h>;
#include <memory.h>;
#include <tchar.h>;
#include "resource.h";
#include <CommCtrl.h>;
#include <string>

BOOL InitMainWindow(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall FrameProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/// <summary>
/// Gets the center point of the primary screen for a given set of dimensions of a window.
/// </summary>
void GetCenterStartPos(SIZE dm, POINT* pt) {
	int w = GetSystemMetrics(SM_CXSCREEN);
	int h = GetSystemMetrics(SM_CYSCREEN);
	pt->x = (w - dm.cx) / 2;
	pt->y = (h - dm.cy) / 2;
}

/// <summary>
/// Sets the font to be the system font for a given handle.
/// </summary>
void SetSysFont(HWND hWnd) {
	NONCLIENTMETRICS metrics;
	metrics.cbSize = sizeof(metrics);
	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0);
	HFONT font = CreateFontIndirect(&metrics.lfMessageFont);
	SendMessage(hWnd, WM_SETFONT, (WPARAM)font, 0);
}

/// <summary>
/// Shows an error message indicating that the initialisation has failed. A string represenation of GetLastError() will also be included in the message.
/// </summary>
void InitFailed(HINSTANCE hInstance) {
	LPSTR messageBuffer = nullptr;
	DWORD error = GetLastError();

	size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
	std::string message(messageBuffer, size);
	LocalFree(messageBuffer);

	if (error == 0) {
		message = "The operation was successful.";
	}

	TASKDIALOGCONFIG tdc = { 0 };

	tdc.cbSize = sizeof(tdc);
	tdc.hwndParent = NULL;
	tdc.dwCommonButtons = TDCBF_OK_BUTTON;
	tdc.pszWindowTitle = L"Calculator";
	tdc.pszMainInstruction = L"Calculator was unable to start";
	tdc.pszContent = L"An error occured when attempting to start calculator. Please restart the application and try again.\n\nThe error provided by Windows was:\n\n" + *message.c_str();
	tdc.pszMainIcon = TD_WARNING_ICON;

	TaskDialogIndirect(&tdc, nullptr, nullptr, nullptr);
}