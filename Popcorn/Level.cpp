#include "Level.h"

char ALevel::FirstLevel[AsConfig::LevelHeight][AsConfig::LevelWidth] =
{
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

ALevel::ALevel()
: ActiveBrick(EBT_Red), LetterPen(0), RedBrickPen(0), BlueBrickPen(0), RedBrickBrush(0), BlueBrickBrush(0), LevelRect{}
{
}

void ALevel::Init()
{
    LetterPen = CreatePen(PS_SOLID, AsConfig::GlobalScale, RGB(255, 255, 255));

    AsConfig::CreatePenBrush(AsConfig::RedBrickColor, RedBrickPen, RedBrickBrush);
    AsConfig::CreatePenBrush(AsConfig::BlueBrickColor, BlueBrickPen, BlueBrickBrush);

    LevelRect.left = AsConfig::OffsetX * AsConfig::GlobalScale;
    LevelRect.top = AsConfig::OffsetY * AsConfig::GlobalScale;
    LevelRect.right = LevelRect.left + AsConfig::CellWidth * AsConfig::LevelWidth;
    LevelRect.bottom = LevelRect.top + AsConfig::CellHeight * AsConfig::LevelHeight;
}

void ALevel::CheckLevelBrickHit(int& NextYPos, double& ballDirection)
{
    //Adjust ball bouncing off bricks

    int BrickYPos = AsConfig::OffsetY + AsConfig::LevelHeight * AsConfig::CellHeight;

    for (int i = AsConfig::LevelHeight - 1; i >= 0; i--)
    {
        for (int j = 0; j < AsConfig::LevelWidth; j++)
        {
            if (FirstLevel[i][j] == 0)
                continue;

            if (NextYPos < BrickYPos)
            {
                NextYPos = BrickYPos - (NextYPos - BrickYPos);
                ballDirection = -ballDirection;
            }
        }

        BrickYPos -= AsConfig::CellHeight;
    }
}

void ALevel::Draw(HWND Hwnd, HDC hdc, RECT &paintArea)
{
    RECT IntersectionRect;

    if (!IntersectRect(&IntersectionRect, &paintArea, &LevelRect))
        return;

    for (int j = 0; j < AsConfig::LevelHeight; j++)
        for (int i = 0; i < AsConfig::LevelWidth; i++)
            DrawBrick(hdc, AsConfig::OffsetX + i * AsConfig::CellWidth, AsConfig::OffsetY + j * AsConfig::CellHeight, (EBrickType)FirstLevel[j][i]);

    ActiveBrick.Draw(Hwnd, hdc, paintArea);
}

void ALevel::DrawBrick(HDC hdc, int x, int y, EBrickType BrickType)
{
    HPEN Pen;
    HBRUSH Brush;

    switch (BrickType)
    {
    case EBT_Blue:
        Pen = BlueBrickPen;
        Brush = BlueBrickBrush;
        break;
    case EBT_Red:
        Pen = RedBrickPen;
        Brush = RedBrickBrush;
        break;
    default:
        return;
    }

    SelectObject(hdc, Pen);
    SelectObject(hdc, Brush);

    RoundRect(hdc, x * AsConfig::GlobalScale, y * AsConfig::GlobalScale, (x + AActiveBrick::BrickWidth) * AsConfig::GlobalScale, (y + AActiveBrick::BrickHeight) * AsConfig::GlobalScale, 2 * AsConfig::GlobalScale, 2 * AsConfig::GlobalScale);
}

void ALevel::SetLetterColor(bool IsSwitch, HPEN& FrontPen, HBRUSH& FrontBrush, HPEN& BackPen, HBRUSH& BackBrush)
{
    if (IsSwitch)
    {
        FrontPen = RedBrickPen;
        FrontBrush = RedBrickBrush;

        BackPen = BlueBrickPen;
        BackBrush = BlueBrickBrush;
    }
    else
    {
        FrontPen = BlueBrickPen;
        FrontBrush = BlueBrickBrush;

        BackPen = RedBrickPen;
        BackBrush = RedBrickBrush;
    }
}

void ALevel::DrawBrickLetter(HDC hdc, int x, int y, EBrickType BrickType, ELetterType LetterType, int RotationStep)
{
    double Offset;
    int BackPartOffset;
    XFORM XForm, OldXForm;
    HPEN FrontPen, BackPen;
    HBRUSH FrontBrush, BackBrush;
    bool IsSwitch;

    //Calculate rotation angle based on Step of the Rotation
    double RotationAngle;
    int BrickHalfHeight = AActiveBrick::BrickHeight * AsConfig::GlobalScale / 2;

    //Falling Letters can be only from Bricks of such types
    if (!(BrickType == EBT_Red || BrickType == EBT_Blue))
        return;

    //Correction of the RotationStep and RotationAngle
    RotationStep = RotationStep % 16;

    if (RotationStep < 8)
        RotationAngle = 2.0 * M_PI / 16.0 * (double)RotationStep;
    else
        RotationAngle = 2.0 * M_PI / 16.0 * (double)(8L - (long long)RotationStep);

    if (RotationStep > 4 && RotationStep <= 12)
    {
        if (BrickType == EBT_Blue)
            IsSwitch = true;
        else
            IsSwitch = false;
    }
    else
    {
        if (BrickType == EBT_Red)
            IsSwitch = true;
        else
            IsSwitch = false;
    }

    SetLetterColor(IsSwitch, FrontPen, FrontBrush, BackPen, BackBrush);

    if (RotationStep == 4 || RotationStep == 12)
    {
        //Draw Letter Background
        SelectObject(hdc, RedBrickPen);
        SelectObject(hdc, RedBrickBrush);

        Rectangle(hdc, x, y + BrickHalfHeight - AsConfig::GlobalScale, x + AActiveBrick::BrickWidth * AsConfig::GlobalScale, y + BrickHalfHeight);

        //Draw Letter Front
        SelectObject(hdc, BlueBrickPen);
        SelectObject(hdc, BlueBrickBrush);

        Rectangle(hdc, x, y + BrickHalfHeight, x + AActiveBrick::BrickWidth * AsConfig::GlobalScale, y + BrickHalfHeight + AsConfig::GlobalScale - 1);
    }
    else
    {
        SetGraphicsMode(hdc, GM_ADVANCED);

        //Transformation Matrix for Letter Rotation
        XForm.eM11 = 1;
        XForm.eM12 = 0;
        XForm.eM21 = 0;
        XForm.eM22 = (float)cos(RotationAngle);
        XForm.eDx = (float)x;
        XForm.eDy = (float)y + (float)BrickHalfHeight;

        GetWorldTransform(hdc, &OldXForm);
        SetWorldTransform(hdc, &XForm);

        //Draw Letter Background
        SelectObject(hdc, BackPen);
        SelectObject(hdc, BackBrush);

        Offset = (1.0 - fabs(XForm.eM22)) * 3.0 * double(AsConfig::GlobalScale);
        BackPartOffset = (int)round(Offset);

        Rectangle(hdc, 0, -BrickHalfHeight - BackPartOffset, AActiveBrick::BrickWidth * AsConfig::GlobalScale, BrickHalfHeight - BackPartOffset);

        //Draw Letter Front
        SelectObject(hdc, FrontPen);
        SelectObject(hdc, FrontBrush);

        Rectangle(hdc, 0, -BrickHalfHeight, AActiveBrick::BrickWidth * AsConfig::GlobalScale, BrickHalfHeight);

        if (RotationStep > 4 && RotationStep <= 12)
        {
            if (LetterType == ELT_O)
            {
                SelectObject(hdc, LetterPen);
                Ellipse(hdc, 0 + 5 * AsConfig::GlobalScale, (-5 * AsConfig::GlobalScale) / 2, 0 + 10 * AsConfig::GlobalScale, 5 * AsConfig::GlobalScale / 2);
            }
        }

        SetWorldTransform(hdc, &OldXForm);
    }
}