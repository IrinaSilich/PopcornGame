#include "ActiveBrick.h"

HPEN AActiveBrick::FadingRedBrickPens[MaxFadeStep];
HBRUSH AActiveBrick::FadingRedBrickBrushes[MaxFadeStep];
HPEN AActiveBrick::FadingBlueBrickPens[MaxFadeStep];
HBRUSH AActiveBrick::FadingBlueBrickBrushes[MaxFadeStep];

AActiveBrick::AActiveBrick(EBrickType brickType)
: BrickType(brickType), FadeStep(0), BrickRect{}
{
}

void AActiveBrick::Draw(HWND Hwnd, HDC hdc, RECT &paintArea)
{
    HPEN Pen = 0;
    HBRUSH Brush = 0;

    BrickRect.left = (AsConfig::OffsetX + AsConfig::CellWidth) * AsConfig::GlobalScale;
    BrickRect.top = (AsConfig::OffsetY + AsConfig::CellHeight) * AsConfig::GlobalScale;
    BrickRect.right = BrickRect.left + BrickWidth * AsConfig::GlobalScale;
    BrickRect.bottom = BrickRect.top + BrickHeight * AsConfig::GlobalScale;

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
    if (FadeStep < MaxFadeStep - 1)
    {
        ++FadeStep;
        InvalidateRect(Hwnd, &BrickRect, FALSE);
    } 
}

void AActiveBrick::SetupColors()
{
    for (int i = 0; i < MaxFadeStep; i++)
    {
        GetFadingColor(AsConfig::BlueBrickColor, i, FadingBlueBrickPens[i], FadingBlueBrickBrushes[i]);
        GetFadingColor(AsConfig::RedBrickColor, i, FadingRedBrickPens[i], FadingRedBrickBrushes[i]);
    }
}

unsigned char AActiveBrick::GetFadingChannel(unsigned char color, unsigned char backgroundColor, int step)
{
    return color - step * (color - backgroundColor) / MaxFadeStep - 1;
}

void AActiveBrick::GetFadingColor(const AColor &color, int step, HPEN &pen, HBRUSH &brush)
{
    unsigned char r, g, b;

    r = GetFadingChannel(color.R, AsConfig::BackgroundColor.R, step);
    g = GetFadingChannel(color.G, AsConfig::BackgroundColor.G, step);
    b = GetFadingChannel(color.B, AsConfig::BackgroundColor.B, step);

    AsConfig::CreatePenBrush(r, g, b, pen, brush);
}