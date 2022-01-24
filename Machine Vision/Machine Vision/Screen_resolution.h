#pragma once
#include "wtypes.h"
#include <iostream>
using namespace std;
int resolution_horizontal = 0;
int resolution_vertical = 0;

static void GetDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}