#pragma once
#include <string>
#include <functional>

using namespace std;

class IMainView {
public:
    virtual ~IMainView() = default;

    // Установка обработчиков событий
    virtual void SetOnProject1Selected(function<void()> handler) = 0;
    virtual void SetOnProject2Selected(function<void()> handler) = 0;
    virtual void SetOnProject3Selected(function<void()> handler) = 0;
    virtual void SetOnExitSelected(function<void()> handler) = 0;
    // Отображение
    virtual void ShowMenu() = 0;
    virtual void ShowMessage(const string& msg) = 0;
    virtual void ClearScreen() = 0;
    virtual int GetUserChoice() = 0;
};
