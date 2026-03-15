#include <iostream>
#include <memory>
#include <windows.h>

#include "ProjectModel.h"
#include "ProjectPresenter.h"
#include "ConsoleViews.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    auto model = make_shared<ProjectModel>();
    auto mainView = make_shared<ConsoleMainView>();
    auto presenter = make_shared<ProjectPresenter>(model, mainView);

    presenter->Run();
    
    return 0;
}