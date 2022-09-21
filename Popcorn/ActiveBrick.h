#pragma once

#include "Config.h"

enum EBrickType
{
	EBT_None,
	EBT_Red,
	EBT_Blue
};

class AActiveBrick
{
public:
	AActiveBrick();
	void Draw(HWND Hwnd, HDC hdc, RECT& PaintArea);
	void Act(HWND Hwnd);

	EBrickType BrickType;

	RECT BrickRect;

	int FadeStep;

	static const int MaxFadeStep = 80;
	static const int BrickWidth = 15;
	static const int BrickHeight = 7;

	static HPEN FadingRedBrickPens[MaxFadeStep];
	static HBRUSH FadingRedBrickBrushes[MaxFadeStep];
	static HPEN FadingBlueBrickPens[MaxFadeStep];
	static HBRUSH FadingBlueBrickBrushes[MaxFadeStep];
};