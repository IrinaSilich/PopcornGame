#include "Engine.h"

AsEngine::AsEngine()
: Hwnd(0)
{
}

void AsEngine::InitEngine(HWND hwnd)
{
    Hwnd = hwnd;

    AActiveBrick::SetupColors();

    Level.Init();
    Ball.Init();
    Platform.Init();
    Platform.Redraw(Hwnd);
    Border.Init();

    SetTimer(Hwnd, TimerID, 1000 / AsConfig::FPS, NULL);
}

void AsEngine::DrawFrame(HDC hdc, RECT &paintArea)
{
    Level.Draw(Hwnd, hdc, paintArea);

    Platform.Draw(hdc, paintArea);

    /*for (int i = 0; i < 16; i++)
    {
        DrawBrickLetter(hdc, 20 + i * AsConfig::CellWidth * GlobalScale, 100, EBT_Red, ELT_O, i);
        DrawBrickLetter(hdc, 20 + i * AsConfig::CellWidth * GlobalScale, 200, EBT_Blue, ELT_None, i);
    }*/

    Ball.Draw(hdc, paintArea);

    Border.Draw(hdc, paintArea);
}

int AsEngine::OnKeyDown(EKey_Type Key_type)
{
    switch (Key_type)
    {
    case EKT_Left:
        Platform.XPos -= Platform.XStep;
        if (Platform.XPos <= AsConfig::LeftBorderXOffset)
            Platform.XPos = AsConfig::LeftBorderXOffset;
        Platform.Redraw(Hwnd);
        break;

    case EKT_Right:
        Platform.XPos += Platform.XStep;
        if (Platform.XPos >= AsConfig::MaxXPos - Platform.Width + 1)
            Platform.XPos = AsConfig::MaxXPos - Platform.Width + 1;
        Platform.Redraw(Hwnd);
        break;
    }
    return 0;
}

int AsEngine::OnTimer()
{
    Ball.Move(Hwnd, &Level, Platform.XPos, Platform.Width);
    Level.ActiveBrick.Act(Hwnd);
    return 0;
}
