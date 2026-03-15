#pragma once
#include <windows.h>
#include <vector>

using namespace std;

enum class ShapeType {
    Triangle,
    Rectangle,
    Ellipse
};

struct Shape {
    int id;
    ShapeType type;
    RECT rc;
    COLORREF color;
    int penWidth;
};

struct AppState {
    COLORREF currentColor = RGB(0, 0, 0);
    int currentPenWidth = 1;
    std::vector<Shape> shapes;
    int nextShapeId = 1;
};