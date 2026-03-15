#pragma once
#include <windows.h>
#include <vector>

using namespace std;

// Типы фигур
enum class ShapeType {
    Triangle,
    Rectangle,
    Ellipse
};

// Простая структура фигуры
struct Shape {
    int id;
    ShapeType type;
    RECT rc;
    COLORREF color;
    int penWidth;
};

// Состояние приложения
struct AppState {
    COLORREF currentColor = RGB(0, 0, 0);
    int currentPenWidth = 1;
    vector<Shape> shapes;
    int nextShapeId = 1;
};