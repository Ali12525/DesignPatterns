#include "History.h"

// Выполняет команду и помещает её в стек отмены.
// Если recordForMacro == true и macroRecorder не nullptr, добавляет клон команды в recorder.
void History::ExecuteAndPush(unique_ptr<ICommand> cmd, AppState& state, HWND hwnd,
    bool recordForMacro, vector<unique_ptr<ICommand>>* macroRecorder) {
    if (recordForMacro && macroRecorder)
        macroRecorder->push_back(cmd->Clone());

    cmd->Execute(state, hwnd);

    if (undoStack.size() == limit) undoStack.pop_front();
    undoStack.push_back(move(cmd));
    redoStack.clear();
}

// Отменяет последнюю выполненную команду (извлекает из стека отмены, выполняет Unexecute, помещает в стек повтора)
void History::Undo(AppState& state, HWND hwnd) {
    if (!CanUndo()) return;
    auto cmd = move(undoStack.back());
    undoStack.pop_back();
    cmd->Unexecute(state, hwnd);
    if (redoStack.size() == limit) redoStack.pop_front();
    redoStack.push_back(move(cmd));
}

// Повторяет последнюю отменённую команду (извлекает из стека повтора, выполняет Execute, помещает в стек отмены).
void History::Redo(AppState& state, HWND hwnd) {
    if (!CanRedo()) return;
    auto cmd = move(redoStack.back());
    redoStack.pop_back();
    cmd->Execute(state, hwnd);
    if (undoStack.size() == limit) undoStack.pop_front();
    undoStack.push_back(move(cmd));
}