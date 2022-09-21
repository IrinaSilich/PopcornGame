#include "Config.h"

AColor::AColor(unsigned char r, unsigned char g, unsigned char b)
: R(r), G(g), B(b)
{
}

const AColor AsConfig::RedBrickColor(255, 85, 85);
const AColor AsConfig::BlueBrickColor(85, 255, 255);

void AsConfig::CreatePenBrush(const AColor &Color, HPEN &Pen, HBRUSH &Brush)
{
    Pen = CreatePen(PS_SOLID, 0, RGB(Color.R, Color.G, Color.B));
    Brush = CreateSolidBrush(RGB(Color.R, Color.G, Color.B));
}

void AsConfig::CreatePenBrush(unsigned char r, unsigned char g, unsigned char b, HPEN &Pen, HBRUSH &Brush)
{
    Pen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
    Brush = CreateSolidBrush(RGB(r, g, b));
}
