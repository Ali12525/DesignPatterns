#include "ConsoleViews.h"
#include <cstdlib>
#include <iostream>

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#endif

ConsoleMainView::ConsoleMainView()
    : onProject1Selected_(nullptr)
    , onProject2Selected_(nullptr)
    , onProject3Selected_(nullptr)
    , onExitSelected_(nullptr) {
}

void ConsoleMainView::SetOnProject1Selected(function<void()> handler) {
    onProject1Selected_ = handler;
}

void ConsoleMainView::SetOnProject2Selected(function<void()> handler) {
    onProject2Selected_ = handler;
}

void ConsoleMainView::SetOnProject3Selected(function<void()> handler) {
    onProject3Selected_ = handler;
}

void ConsoleMainView::SetOnExitSelected(function<void()> handler) {
    onExitSelected_ = handler;
}

void ConsoleMainView::ShowMenu() {
    cout << "======================================" << endl;
    cout << "  ГЛАВНОЕ МЕНЮ" << endl;
    cout << "======================================" << endl;
    cout << endl;
    cout << "  1. Проект 1 (Команда)" << endl;
    cout << "  2. Проект 2 (Одиночка)" << endl;
    cout << "  3. Проект 3 (Декоратор)" << endl;
    cout << "  0. Выход" << endl;
    cout << endl;
    cout << "======================================" << endl;
}

void ConsoleMainView::ShowMessage(const string& msg) {
    cout << msg << endl;
}

void ConsoleMainView::ClearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int ConsoleMainView::GetUserChoice() {
    int choice;
    cin >> choice;
    cin.ignore(10000, '\n');
    return choice;
}