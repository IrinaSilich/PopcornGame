#include "Border.h"

AsBorder::AsBorder()
: BlueBorderPen(0), WhiteBorderPen(0), BlueBorderBrush(0), WhiteBorderBrush(0)
{
}

void AsBorder::Init()
{
    AsConfig::CreatePenBrush(85, 255, 255, BlueBorderPen, BlueBorderBrush);
    AsConfig::CreatePenBrush(255, 255, 255, WhiteBorderPen, WhiteBorderBrush);
}

void AsBorder::Draw(HDC hdc, RECT &PaintArea, HPEN BackgroundPen, HBRUSH BackgroundBrush)
{
    //left line
    for (int i = 0; i < 50; i++)
        DrawElement(hdc, 2, 1 + 4 * i, false, BackgroundPen, BackgroundBrush);

    //right line
    for (int i = 0; i < 50; i++)
        DrawElement(hdc, 201, 1 + 4 * i, false, BackgroundPen, BackgroundBrush);

    //upper line
    for (int i = 0; i < 50; i++)
        DrawElement(hdc, 3 + 4 * i, 0, true, BackgroundPen, BackgroundBrush);
}

void AsBorder::DrawElement(HDC hdc, int x, int y, bool topBorder, HPEN BackgroundPen, HBRUSH BackgroundBrush)
{
    //Blue border
    SelectObject(hdc, BlueBorderPen);
    SelectObject(hdc, BlueBorderBrush);

    if (topBorder)
        Rectangle(hdc, x * AsConfig::GlobalScale, (y + 1) * AsConfig::GlobalScale, (x + 4) * AsConfig::GlobalScale, (y + 4) * AsConfig::GlobalScale);
    else
        Rectangle(hdc, (x + 1) * AsConfig::GlobalScale, y * AsConfig::GlobalScale, (x + 4) * AsConfig::GlobalScale, (y + 4) * AsConfig::GlobalScale);

    //White edge
    SelectObject(hdc, WhiteBorderPen);
    SelectObject(hdc, WhiteBorderBrush);

    if (topBorder)
        Rectangle(hdc, x * AsConfig::GlobalScale, y * AsConfig::GlobalScale, (x + 4) * AsConfig::GlobalScale, (y + 1) * AsConfig::GlobalScale);
    else
        Rectangle(hdc, x * AsConfig::GlobalScale, y * AsConfig::GlobalScale, (x + 1) * AsConfig::GlobalScale, (y + 4) * AsConfig::GlobalScale);

    //Hole
    SelectObject(hdc, BackgroundPen);
    SelectObject(hdc, BackgroundBrush);

    if (topBorder)
        Rectangle(hdc, (x + 2) * AsConfig::GlobalScale, (y + 2) * AsConfig::GlobalScale, (x + 3) * AsConfig::GlobalScale, (y + 3) * AsConfig::GlobalScale);
    else
        Rectangle(hdc, (x + 2) * AsConfig::GlobalScale, (y + 1) * AsConfig::GlobalScale, (x + 3) * AsConfig::GlobalScale, (y + 2) * AsConfig::GlobalScale);
}