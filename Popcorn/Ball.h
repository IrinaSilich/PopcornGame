#pragma once

#include "Config.h"
#include "Level.h"

class ABall
{
public:
	ABall();

	void Init();

	void Draw(HDC hdc, RECT &paintArea);
	void Move(HWND Hwnd, ALevel* Level, int PlatformXPos, int PlatformWidth);

private:
	HPEN BallPen;
	HBRUSH BallBrush;
	double BallDirection;
	int BallXPos, BallYPos;
	double BallSpeed;

	RECT BallRect, PreviousBallRect;
};

