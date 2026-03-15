#pragma once
#include <windows.h>
#include "AppState.h"

using namespace std;

// Нормализует прямоугольник: приводит координаты к виду left <= right, top <= bottom.
RECT NormalizeRect(const RECT& r);

void DrawShapeGDI(HDC hdc, const Shape& s);
void DrawAll(HDC hdc, const AppState& state);