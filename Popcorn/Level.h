#pragma once

#include "Config.h"
#include "ActiveBrick.h"

enum ELetterType
{
	ELT_None,
	ELT_O
};

class ALevel
{
public:
	ALevel();

	void Init();

	void CheckLevelBrickHit(int& NextYPos, double& ballDirection);
	void Draw(HWND Hwnd, HDC hdc, RECT& PaintArea);

	AActiveBrick ActiveBrick;

private:
	void DrawBrick(HDC hdc, int x, int y, EBrickType BrickType);

	void SetLetterColor(bool IsSwitch, HPEN& FrontPen, HBRUSH& FrontBrush, HPEN& BackPen, HBRUSH& BackBrush);
	void DrawBrickLetter(HDC hdc, int x, int y, EBrickType BrickType, ELetterType LetterType, int RotationStep);

	HPEN LetterPen, RedBrickPen, BlueBrickPen;
	HBRUSH RedBrickBrush, BlueBrickBrush;
	RECT LevelRect;

	static char FirstLevel[AsConfig::LevelHeight][AsConfig::LevelWidth];
};