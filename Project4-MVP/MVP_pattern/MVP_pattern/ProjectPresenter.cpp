#include "ProjectPresenter.h"
#include "Project1App.h"
#include "Project2App.h"
#include "Project3App.h"
#include <iostream>
#include <windows.h>

ProjectPresenter::ProjectPresenter(shared_ptr<ProjectModel> model, shared_ptr<IMainView> mainView)
    : model_(model)
    , mainView_(mainView)
    , running_(true) {
    
    // Регистрация обработчиков событий
    mainView_->SetOnProject1Selected([this]() { OnProject1Selected(); });
    mainView_->SetOnProject2Selected([this]() { OnProject2Selected(); });
    mainView_->SetOnProject3Selected([this]() { OnProject3Selected(); });
    mainView_->SetOnExitSelected([this]() { OnExitSelected(); });

    // Подписка на изменения модели
    model_->AddObserver([this]() {});
}

void ProjectPresenter::Run() {
    mainView_->ShowMessage("Меню:");
    mainView_->ShowMessage("  1. Паттерн Команда - Графический редактор");
    mainView_->ShowMessage("  2. Паттерн Одиночка - Потокобезопасный логгер");
    mainView_->ShowMessage("  3. Паттерн Декоратор - Универсальная электронная карта");
    mainView_->ShowMessage("");

    while (running_) {
        ShowProjectMenu();
        
        int choice = mainView_->GetUserChoice();
        
        switch (choice) {
            case 1:
                OnProject1Selected();
                break;
            case 2:
                OnProject2Selected();
                break;
            case 3:
                OnProject3Selected();
                break;
            case 0:
                OnExitSelected();
                break;
            default:
                mainView_->ShowMessage("Неверный выбор. Попробуйте снова.");
                break;
        }
    }
}

void ProjectPresenter::ShowProjectMenu() {
    mainView_->ClearScreen();
    mainView_->ShowMessage("");
    mainView_->ShowMessage("======================================");
    mainView_->ShowMessage("  ГЛАВНОЕ МЕНЮ");
    mainView_->ShowMessage("======================================");
    mainView_->ShowMessage("");
    
    auto projects = model_->GetProjectsList();
    for (const auto& project : projects) {
        string status = project.isRunning ? " [ЗАПУЩЕНА]" : "";
        cout << "  " << project.id << ". " << project.name 
                  << " (" << project.pattern << ")" << status << endl;
        cout << "     " << project.description << endl;
        cout << endl;
    }
    
    mainView_->ShowMessage("  0. Выход");
    mainView_->ShowMessage("");
    mainView_->ShowMessage("======================================");
    cout << "Выберите проект: ";
}

void ProjectPresenter::OnProject1Selected() {
    model_->StartProject(1);
    RunProject1();
    model_->StopProject(1);
}

void ProjectPresenter::OnProject2Selected() {
    model_->StartProject(2);
    RunProject2();
    model_->StopProject(2);
}

void ProjectPresenter::OnProject3Selected() {
    model_->StartProject(3);
    RunProject3();
    model_->StopProject(3);
}

void ProjectPresenter::OnExitSelected() {
    mainView_->ShowMessage("");
    mainView_->ShowMessage("Завершение работы...");
    running_ = false;
}

void ProjectPresenter::RunProject1() {
    mainView_->ShowMessage("");
    mainView_->ShowMessage("ЗАПУСК ПРОЕКТА 1: Графический редактор");
    mainView_->ShowMessage("");

    Project1App* app = model_->GetProject1App();
    if (!app) {
        mainView_->ShowMessage("Ошибка: не удалось создать приложение");
        return;
    }

    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    if (!app->Initialize(hInstance)) {
        mainView_->ShowMessage("Ошибка инициализации приложения");
        return;
    }

    mainView_->ShowMessage("Графический редактор запущен!");
    mainView_->ShowMessage("Функционал:");
    mainView_->ShowMessage("  - Рисование: треугольник, прямоугольник, эллипс");
    mainView_->ShowMessage("  - Выбор цвета и толщины пера");
    mainView_->ShowMessage("  - Повтор / Отмена");
    mainView_->ShowMessage("  - Запись и воспроизведение макросов");
    mainView_->ShowMessage("");
    mainView_->ShowMessage("Закройте окно редактора для возврата в меню...");
    mainView_->ShowMessage("");

    app->Run();

    // После закрытия окна возвращаемся в меню
    app->Shutdown();
}

void ProjectPresenter::RunProject2() {
    mainView_->ShowMessage("");
    mainView_->ShowMessage("ЗАПУСК ПРОЕКТА 2: Логгер (Singleton)");
    mainView_->ShowMessage("");

    Project2App* app = model_->GetProject2App();
    if (!app) {
        mainView_->ShowMessage("Ошибка: не удалось создать приложение");
        return;
    }

    app->SetLogFile("project2_output.log");
    app->Run();

    mainView_->ShowMessage("");
    mainView_->ShowMessage("Нажмите Enter для возврата в меню...");
    cin.get();
}

void ProjectPresenter::RunProject3() {
    mainView_->ShowMessage("");
    mainView_->ShowMessage("ЗАПУСК ПРОЕКТА 3: Декоратор (Электронная карта)");
    mainView_->ShowMessage("");

    Project3App* app = model_->GetProject3App();
    if (!app) {
        mainView_->ShowMessage("Ошибка: не удалось создать приложение");
        return;
    }

    app->Run();

    mainView_->ShowMessage("");
    mainView_->ShowMessage("Нажмите Enter для возврата в меню...");
    cin.get();
}