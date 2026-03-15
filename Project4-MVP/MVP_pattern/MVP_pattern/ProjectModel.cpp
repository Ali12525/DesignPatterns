#include "ProjectModel.h"
#include "Project1App.h"
#include "Project2App.h"
#include "Project3App.h"
#include <iostream>

ProjectModel::ProjectModel() {
    InitializeProjects();
}

ProjectModel::~ProjectModel() = default;

void ProjectModel::InitializeProjects() {
    projects_ = {
        {1, "Проект 1", "Паттерн Команда", 
         "Графический редактор с фигурами, Отмена / Повтор, макросами", false},
        {2, "Проект 2", "Паттерн Одиночка", 
         "Потокобезопасный логгер", false},
        {3, "Проект 3", "Паттерн Декоратор", 
         "Универсальная электронная карта (паспорт, страховка, банк)", false}
    };
}

vector<ProjectInfo> ProjectModel::GetProjectsList() const {
    return projects_;
}

ProjectInfo ProjectModel::GetProjectInfo(int projectId) const {
    for (const auto& project : projects_) {
        if (project.id == projectId) {
            return project;
        }
    }
    return {-1, "", "", "", false};
}

void ProjectModel::StartProject(int projectId) {
    for (auto& project : projects_) {
        if (project.id == projectId) {
            project.isRunning = true;

            switch (projectId) {
                case 1:
                    if (!project1App_) {
                        project1App_ = make_unique<Project1App>();
                    }
                    break;
                case 2:
                    if (!project2App_) {
                        project2App_ = make_unique<Project2App>();
                    }
                    break;
                case 3:
                    if (!project3App_) {
                        project3App_ = make_unique<Project3App>();
                    }
                    break;
            }

            NotifyObservers();
            break;
        }
    }
}

void ProjectModel::StopProject(int projectId) {
    for (auto& project : projects_) {
        if (project.id == projectId) {
            project.isRunning = false;
            NotifyObservers();
            break;
        }
    }
}

bool ProjectModel::IsProjectRunning(int projectId) const {
    for (const auto& project : projects_) {
        if (project.id == projectId) {
            return project.isRunning;
        }
    }
    return false;
}

Project1App* ProjectModel::GetProject1App() const {
    return project1App_.get();
}

Project2App* ProjectModel::GetProject2App() const {
    return project2App_.get();
}

Project3App* ProjectModel::GetProject3App() const {
    return project3App_.get();
}

void ProjectModel::AddObserver(ChangeCallback callback) {
    observers_.push_back(callback);
}

void ProjectModel::NotifyObservers() {
    for (auto& observer : observers_) {
        observer();
    }
}
