#pragma once
#include <string>
#include <vector>
#include <memory>
#include <functional>

using namespace std;

class Project1App;
class Project2App;
class Project3App;

struct ProjectInfo {
    int id;
    string name;
    string pattern;
    string description;
    bool isRunning;
};

class ProjectModel {
public:
    ProjectModel();
    ~ProjectModel();

    vector<ProjectInfo> GetProjectsList() const;

    ProjectInfo GetProjectInfo(int projectId) const;
    void StartProject(int projectId);
    void StopProject(int projectId);
    bool IsProjectRunning(int projectId) const;

    Project1App* GetProject1App() const;
    Project2App* GetProject2App() const;
    Project3App* GetProject3App() const;

    // Подписка на изменения
    using ChangeCallback = function<void()>;
    void AddObserver(ChangeCallback callback);
    void NotifyObservers();

private:
    vector<ProjectInfo> projects_;
    vector<ChangeCallback> observers_;

    unique_ptr<Project1App> project1App_;
    unique_ptr<Project2App> project2App_;
    unique_ptr<Project3App> project3App_;

    void InitializeProjects();
};
