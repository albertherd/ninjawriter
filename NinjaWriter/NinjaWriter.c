// NinjaWriter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

BOOL CALLBACK EnumWindowCallbackFunc(HWND hwnd, LPARAM lParam);
void DrawOnScreen();

DWORD processId = 4504;
HWND processHwnd = NULL;

int main(int argc, char* argv[])
{
	/*if (argc < 2)
		return 1;

	processId = atoi(argv[1]);
	if (processId < 1)
		return 1;*/

	EnumWindows(EnumWindowCallbackFunc, NULL);
	if (!processHwnd)
		return 1;

	DrawOnScreen();
	
	return 0;
}

void DrawOnScreen()
{
	RECT rect;

	HDC hdc = GetDC(processHwnd);
	if (!hdc)
		return;

	GetClientRect(processHwnd, &rect);
	SetTextColor(hdc, 0x00000000);
	SetBkMode(hdc, TRANSPARENT);
	rect.left = 50;
	rect.top = 50;
	DrawText(hdc, L"Hello world", -1, &rect, DT_SINGLELINE | DT_NOCLIP);

	ReleaseDC(processHwnd, hdc);
}


BOOL CALLBACK EnumWindowCallbackFunc(HWND hwnd, LPARAM lParam)
{
	DWORD currentWindowProcessId;
	GetWindowThreadProcessId(hwnd, &currentWindowProcessId);

	if (currentWindowProcessId == processId)
	{
		processHwnd = hwnd;
		return FALSE;
	}
	return TRUE;
}
