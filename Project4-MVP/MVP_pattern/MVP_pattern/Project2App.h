#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <vector>

using namespace std;

enum class LogLevel { DEBUGG = 0, INFO = 1, WARNING = 2, EERROR = 3 };

inline string to_string(LogLevel lvl) {
    switch (lvl) {
        case LogLevel::DEBUGG: return "DEBUG";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::EERROR: return "ERROR";
    }
    return "UNKNOWN";
}

class LogManager {
public:
    static LogManager& instance();

    void set_file(const string& filename);
    void set_level(LogLevel lvl);
    LogLevel get_level() const;

    void add_ref();
    void release_ref();

    void write(LogLevel msg_level,
               const string& prefix,
               const string& data,
               bool& at_line_start,
               bool flush_on_end);

private:
    LogManager();
    ~LogManager();

    LogManager(const LogManager&) = delete;
    LogManager& operator=(const LogManager&) = delete;

    void open_stream_nolock();

    mutable mutex mtx_;
    ofstream ofs_;
    string filename_;
    int refcount_;
    LogLevel level_;
};

class logstream {
public:
    explicit logstream(const string& prefix = "");
    ~logstream();

    logstream(const logstream&) = delete;
    logstream& operator=(const logstream&) = delete;

    logstream(logstream&&) noexcept = default;
    logstream& operator=(logstream&&) noexcept = default;

    static void set_log_file(const string& filename);
    static void set_level(LogLevel lvl);

    template<typename T>
    logstream& operator<<(const T& value) {
        buffer_ << value;
        if (buffer_.str().find('\n') != string::npos) {
            flush_buffer();
        }
        return *this;
    }

    logstream& operator<<(ostream& (*manip)(ostream&));

    logstream& at(LogLevel lvl);
    logstream& debug();
    logstream& info();
    logstream& warning();
    logstream& error();

private:
    void flush_buffer();

    string prefix_;
    ostringstream buffer_;
    LogLevel current_level_;
    bool at_line_start_;
};

class Project2App {
public:
    Project2App();
    ~Project2App();

    void Run();
    void SetLogFile(const string& filename);
    vector<string> GetLogs() const;

private:
    string logFile_;
    vector<string> capturedLogs_;

    void RunDemo();
    void CaptureLog(const string& message);
};
