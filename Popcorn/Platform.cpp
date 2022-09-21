#include "Platform.h"

AsPlatform::AsPlatform()
    : InnerWidth(21), XPos(AsConfig::LeftBorderXOffset), XStep(6), Width(28), HighlightPen(0), PlatformCirclePen(0), PlatformInnerPen(0), PlatformCircleBrush(0), PlatformInnerBrush(0), PlatformRect{}, PreviousPlatformRect{}
{
}

void AsPlatform::Init()
{
    HighlightPen = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));

    AsConfig::CreatePenBrush(151, 0, 0, PlatformCirclePen, PlatformCircleBrush);
    AsConfig::CreatePenBrush(0, 128, 192, PlatformInnerPen, PlatformInnerBrush);
}

void AsPlatform::Redraw(HWND Hwnd)
{
    PreviousPlatformRect = PlatformRect;

    PlatformRect.left = XPos * AsConfig::GlobalScale;
    PlatformRect.top = AsConfig::PlatformYPos * AsConfig::GlobalScale;
    PlatformRect.right = PlatformRect.left + Width * AsConfig::GlobalScale;
    PlatformRect.bottom = PlatformRect.top + Height * AsConfig::GlobalScale;

    InvalidateRect(Hwnd, &PreviousPlatformRect, FALSE);
    InvalidateRect(Hwnd, &PlatformRect, FALSE);
}

void AsPlatform::Draw(HDC hdc, HPEN BackgroundPen, HBRUSH BackgroundBrush, RECT& PaintArea)
{
    RECT IntersectionRect;
    int x = XPos;
    int y = AsConfig::PlatformYPos;

    if (!IntersectRect(&IntersectionRect, &PaintArea, &PlatformRect))
        return;

    //Redraw background when moving our platform
    SelectObject(hdc, BackgroundPen);
    SelectObject(hdc, BackgroundBrush);

    Rectangle(hdc, PreviousPlatformRect.left, PreviousPlatformRect.top, PreviousPlatformRect.right, PreviousPlatformRect.bottom);

    // Draw Side Circles
    SelectObject(hdc, PlatformCirclePen);
    SelectObject(hdc, PlatformCircleBrush);

    Ellipse(hdc, x * AsConfig::GlobalScale, y * AsConfig::GlobalScale, (x + CircleSize) * AsConfig::GlobalScale, (y + CircleSize) * AsConfig::GlobalScale);
    Ellipse(hdc, (x + InnerWidth) * AsConfig::GlobalScale, y * AsConfig::GlobalScale, (x + CircleSize + InnerWidth) * AsConfig::GlobalScale, (y + CircleSize) * AsConfig::GlobalScale);

    // Draw Highlight
    SelectObject(hdc, HighlightPen);

    Arc(hdc, (x + 1) * AsConfig::GlobalScale, (y + 1) * AsConfig::GlobalScale, (x + CircleSize - 1) * AsConfig::GlobalScale, (y + CircleSize - 1) * AsConfig::GlobalScale,
        (x + 1 + 1) * AsConfig::GlobalScale, (y + 1) * AsConfig::GlobalScale, (x + 1) * AsConfig::GlobalScale, (y + 1 + 1) * AsConfig::GlobalScale);

    // Draw Inner Part of the Platform
    SelectObject(hdc, PlatformInnerPen);
    SelectObject(hdc, PlatformInnerBrush);

    RoundRect(hdc, (x + 3) * AsConfig::GlobalScale, (y + 1) * AsConfig::GlobalScale, (x + 3 + InnerWidth + 1) * AsConfig::GlobalScale, (y + 1 + 5) * AsConfig::GlobalScale, 3 * AsConfig::GlobalScale, 3 * AsConfig::GlobalScale);
}