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
	AActiveBrick(EBrickType brickType);
	void Draw(HWND Hwnd, HDC hdc, RECT& paintArea);
	void Act(HWND Hwnd);

	static void SetupColors();

	static const int BrickWidth = 15;
	static const int BrickHeight = 7;

private:
	EBrickType BrickType;

	RECT BrickRect;

	int FadeStep;

	static unsigned char GetFadingChannel(unsigned char color, unsigned char backgrounColor, int step);
	static void GetFadingColor(const AColor &color, int step, HPEN &pen, HBRUSH &brush);

	static const int MaxFadeStep = 80;

	static HPEN FadingRedBrickPens[MaxFadeStep];
	static HBRUSH FadingRedBrickBrushes[MaxFadeStep];
	static HPEN FadingBlueBrickPens[MaxFadeStep];
	static HBRUSH FadingBlueBrickBrushes[MaxFadeStep];
};