#include "TestHouseActor.h"

TestHouseActor::TestHouseActor(ResourceID _)
	: Actor(ResourceID::None)
{
    GreenPen = new Gdiplus::Pen(Gdiplus::Color(255, 0, 255, 0), 2.0f);

    int Max = -1;
    for (PointF Pos : HouseVertices)
    {
        if (Max < Pos.X)
        {
            Max = static_cast<int>(Pos.X);
        }
    }
    Size = Max;
}

TestHouseActor::~TestHouseActor()
{
    delete GreenPen;
    GreenPen = nullptr;
}

void TestHouseActor::OnRender(Gdiplus::Graphics* InGraphics)
{
    PointF Positions[HouseVerticesCount];
    for (int i = 0; i < HouseVerticesCount; i++)
    {
        Positions[i] = Position + HouseVertices[i];
        Positions[i].X -= Size * Pivot.X;
        Positions[i].Y -= Size * Pivot.Y;
    }
    InGraphics->DrawPolygon(GreenPen, Positions, HouseVerticesCount);
    //g_BackBufferGraphics->FillPolygon(GreenBrush, Positions, g_HouseVerticesCount);
}