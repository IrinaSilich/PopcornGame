#pragma once

#include "Config.h"

class AsPlatform
{
public:
	AsPlatform();

	void Init();
	void Redraw(HWND Hwnd);
	void Draw(HDC hdc, HPEN BackgroundPen, HBRUSH BackgroundBrush, RECT& PaintArea);

	int XPos;
	int Width;
	int XStep;

private:
	HPEN HighlightPen, PlatformCirclePen, PlatformInnerPen;
	HBRUSH PlatformCircleBrush, PlatformInnerBrush;
	RECT PlatformRect, PreviousPlatformRect;

	int InnerWidth;

	static const int CircleSize = 7;
	static const int Height = 7;
};