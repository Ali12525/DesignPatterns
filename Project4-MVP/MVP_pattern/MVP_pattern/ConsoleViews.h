#pragma once
#include "IMainView.h"
#include <iostream>
#include <functional>
#include <cstdlib>

using namespace std;

class ConsoleMainView : public IMainView {
public:
    ConsoleMainView();
    
    void SetOnProject1Selected(function<void()> handler) override;
    void SetOnProject2Selected(function<void()> handler) override;
    void SetOnProject3Selected(function<void()> handler) override;
    void SetOnExitSelected(function<void()> handler) override;
    
    void ShowMenu() override;
    void ShowMessage(const string& msg) override;
    void ClearScreen() override;
    int GetUserChoice() override;

private:
    function<void()> onProject1Selected_;
    function<void()> onProject2Selected_;
    function<void()> onProject3Selected_;
    function<void()> onExitSelected_;
};
