#pragma once
#include <string>
#include <functional>
#include <vector>

using namespace std;

class IProjectView {
public:
    virtual ~IProjectView() = default;
    virtual void ShowHeader(const std::string& title) = 0;
    virtual void ShowFooter() = 0;
    virtual void WaitForKey() = 0;
};

class IProject1View : public IProjectView {
public:
    virtual ~IProject1View() = default;
    virtual void ShowLaunchMessage() = 0;
    virtual void ShowEditorInfo() = 0;
};

class IProject2View : public IProjectView {
public:
    virtual ~IProject2View() = default;
    virtual void ShowLogOutput(const vector<string>& logs) = 0;
    virtual void ShowLogStatus(bool isLogging) = 0;
};

class IProject3View : public IProjectView {
public:
    virtual ~IProject3View() = default;
    virtual void ShowCardDescription(const string& description) = 0;
    virtual void ShowCardComponents(const vector<string>& components) = 0;
};
