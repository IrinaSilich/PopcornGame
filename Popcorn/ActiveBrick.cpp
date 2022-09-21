#include "ActiveBrick.h"

HPEN AActiveBrick::FadingRedBrickPens[MaxFadeStep];
HBRUSH AActiveBrick::FadingRedBrickBrushes[MaxFadeStep];
HPEN AActiveBrick::FadingBlueBrickPens[MaxFadeStep];
HBRUSH AActiveBrick::FadingBlueBrickBrushes[MaxFadeStep];

AActiveBrick::AActiveBrick()
    : FadeStep(0), BrickRect{}
{
}

void AActiveBrick::Draw(HWND Hwnd, HDC hdc, RECT &PaintArea)
{
    HPEN Pen = 0;
    HBRUSH Brush = 0;
    //unsigned char r, g, b;

    BrickRect.left = (AsConfig::OffsetX + AsConfig::CellWidth) * AsConfig::GlobalScale;
    BrickRect.top = (AsConfig::OffsetY + AsConfig::CellHeight) * AsConfig::GlobalScale;
    BrickRect.right = BrickRect.left + BrickWidth * AsConfig::GlobalScale;
    BrickRect.bottom = BrickRect.top + BrickHeight * AsConfig::GlobalScale;

    /*r = AsConfig::BlueBrickColor.R - FadeStep * (AsConfig::BlueBrickColor.R / MaxFadeStep);
    g = AsConfig::BlueBrickColor.G - FadeStep * (AsConfig::BlueBrickColor.G / MaxFadeStep);
    b = AsConfig::BlueBrickColor.B - FadeStep * (AsConfig::BlueBrickColor.B / MaxFadeStep);*/

    //AsConfig::CreatePenBrush(r, g, b, Pen, Brush);

    switch(BrickType)
    {
    case EBT_Red:
        Pen = FadingRedBrickPens[FadeStep];
        Brush = FadingRedBrickBrushes[FadeStep];
        break;
    case EBT_Blue:
        Pen = FadingBlueBrickPens[FadeStep];
        Brush = FadingBlueBrickBrushes[FadeStep];
        break;
    }
        
    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);

    RoundRect(hdc, BrickRect.left, BrickRect.top, BrickRect.right, BrickRect.bottom, 2 * AsConfig::GlobalScale, 2 * AsConfig::GlobalScale);
}

void AActiveBrick::Act(HWND Hwnd)
{
    if (FadeStep < MaxFadeStep)
    {
        ++FadeStep;
        InvalidateRect(Hwnd, &BrickRect, FALSE);
    } 
}