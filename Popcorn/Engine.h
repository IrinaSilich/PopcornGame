#pragma once
#include <Windows.h>

#include "Border.h"
#include "Ball.h"
#include "Platform.h"

enum EKey_Type
{
	EKT_Left,
	EKT_Right,
	EKT_Space
};

const int TimerID = WM_USER + 1;

class AsEngine
{
public:
	AsEngine();

	void InitEngine(HWND hwnd);
	void DrawFrame(HDC hdc, RECT &PaintArea);
	
	int OnKeyDown(EKey_Type Key_type);
	int OnTimer();

private:
	HWND Hwnd;
	HPEN BackgroundPen;
	HBRUSH BackgroundBrush;
	ABall Ball;
	ALevel Level;
	AsPlatform Platform;
	AsBorder Border;
};
