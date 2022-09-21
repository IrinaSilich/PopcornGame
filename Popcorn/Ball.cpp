#include "Ball.h"

ABall::ABall()
    : BallPen(0), BallBrush(0), BallXPos(20), BallYPos(170), BallSpeed(3.0), BallDirection(M_PI - M_PI_4), BallRect{}, PreviousBallRect{}
{
}

void ABall::Init()
{
    AsConfig::CreatePenBrush(255, 255, 255, BallPen, BallBrush);
}

void ABall::Draw(HDC hdc, RECT& PaintArea, HPEN BackgroundPen, HBRUSH BackgroundBrush)
{
    RECT IntersectionRect;

    if (!IntersectRect(&IntersectionRect, &PaintArea, &BallRect))
        return;

    SelectObject(hdc, BackgroundPen);
    SelectObject(hdc, BackgroundBrush);

    Ellipse(hdc, PreviousBallRect.left, PreviousBallRect.top, PreviousBallRect.right - 1, PreviousBallRect.bottom - 1);

    SelectObject(hdc, BallPen);
    SelectObject(hdc, BallBrush);

    Ellipse(hdc, BallRect.left, BallRect.top, BallRect.right - 1, BallRect.bottom - 1);
}

void ABall::Move(HWND Hwnd, ALevel* Level, int PlatformXPos, int PlatformWidth)
{
    PreviousBallRect = BallRect;

    int NextXPos, NextYPos;
    int maxXPos = AsConfig::MaxXPos - AsConfig::BallSize;
    int platformYPos = AsConfig::PlatformYPos - AsConfig::BallSize;

    NextXPos = BallXPos + (int)(BallSpeed * cos(BallDirection));
    NextYPos = BallYPos - (int)(BallSpeed * sin(BallDirection));

    //Correct ball bouncing from the walls
    if (NextXPos < AsConfig::LeftBorderXOffset)
    {
        NextXPos = AsConfig::AsConfig::OffsetX - (NextXPos - AsConfig::AsConfig::OffsetX);
        BallDirection = M_PI - BallDirection;
    }

    if (NextYPos < AsConfig::UpperBorderYOffset)
    {
        NextYPos = AsConfig::UpperBorderYOffset - (NextYPos - AsConfig::UpperBorderYOffset);
        BallDirection = -BallDirection;
    }

    if (NextXPos > maxXPos)
    {
        NextXPos = maxXPos - (NextXPos - maxXPos);
        BallDirection = M_PI - BallDirection;
    }

    if (NextYPos > AsConfig::MaxYPos)
    {
        NextYPos = AsConfig::MaxYPos - (NextYPos - AsConfig::MaxYPos);
        BallDirection = M_PI + (M_PI - BallDirection);
    }

    //Correct ball bouncing from the platform
    if (NextYPos > platformYPos)
    {
        if (NextXPos >= PlatformXPos && NextXPos <= PlatformXPos + PlatformWidth)
        {
            NextYPos = platformYPos - (NextYPos - platformYPos);
            BallDirection = M_PI + (M_PI - BallDirection);
        }
    }

    //Correct ball bouncing from bricks
    Level->CheckLevelBrickHit(NextYPos, BallDirection);

    //Move the ball
    BallXPos = NextXPos;
    BallYPos = NextYPos;

    BallRect.left = BallXPos * AsConfig::GlobalScale;
    BallRect.top = BallYPos * AsConfig::GlobalScale;
    BallRect.right = BallRect.left + AsConfig::BallSize * AsConfig::GlobalScale;
    BallRect.bottom = BallRect.top + AsConfig::BallSize * AsConfig::GlobalScale;

    InvalidateRect(Hwnd, &PreviousBallRect, FALSE);
    InvalidateRect(Hwnd, &BallRect, FALSE);
}
