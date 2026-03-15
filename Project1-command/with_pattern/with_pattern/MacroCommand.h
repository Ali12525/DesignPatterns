#pragma once
#include "Command.h"
#include <vector>

using namespace std;

class MacroCommand : public ICommand {
public:
    vector<unique_ptr<ICommand>> children;

    void Execute(AppState& state, HWND hwnd) override;
    void Unexecute(AppState& state, HWND hwnd) override;
    unique_ptr<ICommand> Clone() const override;
};