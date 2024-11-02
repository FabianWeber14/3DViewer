#pragma once
#include <windows.h>

class Window
{
public:
	Window(HINSTANCE hInstance);

	bool needResize() const;
	void resetNeedResize();

	HWND hwnd;
};

