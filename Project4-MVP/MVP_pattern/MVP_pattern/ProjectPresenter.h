#pragma once
#include <memory>
#include "ProjectModel.h"
#include "IMainView.h"

using namespace std;

class Project1App;
class Project2App;
class Project3App;

class ProjectPresenter {
public:
    ProjectPresenter(shared_ptr<ProjectModel> model, 
                 shared_ptr<IMainView> mainView);
    
    ~ProjectPresenter() = default;

    void Run();

private:
    // Model и View
    shared_ptr<ProjectModel> model_;
    shared_ptr<IMainView> mainView_;

    bool running_;

    // Обработчики событий от View
    void OnProject1Selected();
    void OnProject2Selected();
    void OnProject3Selected();
    void OnExitSelected();

    // Вспомогательные методы
    void ShowProjectMenu();
    void RunProject1();
    void RunProject2();
    void RunProject3();
};
