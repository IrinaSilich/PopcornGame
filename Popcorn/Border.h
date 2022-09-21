#pragma once

#include "Config.h"

class AsBorder
{
public:
	AsBorder();

	void Init();
	void Draw(HDC hdc, RECT &PaintArea, HPEN BackgroundPen, HBRUSH BackgroundBrush);

private:
	void DrawElement(HDC hdc, int x, int y, bool topBorder, HPEN BackgroundPen, HBRUSH BackgroundBrush);

	HPEN BlueBorderPen, WhiteBorderPen;
	HBRUSH BlueBorderBrush, WhiteBorderBrush;
};