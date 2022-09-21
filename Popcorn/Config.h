#pragma once

#include <Windows.h>

#define _USE_MATH_DEFINES
#include <math.h>

class AColor
{
public:
	AColor(unsigned char r, unsigned char g, unsigned char b);
	unsigned char R, G, B;
};

class AsConfig
{
public:
	static void CreatePenBrush(const AColor &Color, HPEN& Pen, HBRUSH& Brush);
	static void CreatePenBrush(unsigned char r, unsigned char g, unsigned char b, HPEN& Pen, HBRUSH& Brush);
	
	static const int BallSize = 4;
	static const int LevelWidth = 12; // in cells, not in pixels
	static const int LevelHeight = 14; // in cells, not in pixels
	static const int OffsetX = 8;
	static const int OffsetY = 6;
	static const int CellWidth = 16;
	static const int CellHeight = 8;
	static const int GlobalScale = 3;
	static const int MaxXPos = OffsetX + CellWidth * LevelWidth;
	static const int MaxYPos = 199 - BallSize;
	static const int PlatformYPos = 185;
	static const int LeftBorderXOffset = 6;
	static const int UpperBorderYOffset = 4;
	static const int FPS = 20;
	static const AColor RedBrickColor, BlueBrickColor;
	
};