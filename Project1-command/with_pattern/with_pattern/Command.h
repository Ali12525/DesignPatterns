#pragma once
#define NOMINMAX
#include <windows.h>
#include <memory>

using namespace std;

struct AppState;

struct ICommand {
    virtual ~ICommand() = default;
    virtual void Execute(AppState& state, HWND hwnd) = 0;
    virtual void Unexecute(AppState& state, HWND hwnd) = 0;
    virtual unique_ptr<ICommand> Clone() const = 0;
};