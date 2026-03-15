#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <mutex>
#include <memory>
#include <iostream>
#include <iomanip>

using namespace std;

enum class LogLevel : int {
    TRACE = 0,
    DEBUG = 1,
    INFO = 2,
    WARNING = 3,
    ERROR = 4,
    FATAL = 5
};

// Преобразовать уровень в строку
inline const char* to_string(LogLevel lvl) {
    switch (lvl) {
    case LogLevel::TRACE:   return "TRACE";
    case LogLevel::DEBUG:   return "DEBUG";
    case LogLevel::INFO:    return "INFO";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::ERROR:   return "ERROR";
    case LogLevel::FATAL:   return "FATAL";
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
    void open_stream_nolock();

    mutable mutex mtx_;
    ofstream ofs_;             // выходной файловый поток
    string filename_;
    size_t refcount_;
    LogLevel level_;
};

class logstream {
public:
    class Message {
    public:
        Message(logstream& parent, LogLevel level);    
        Message(Message&& other) noexcept;              // Конструктор перемещения. Нужен, чтобы временный объект Message можно было вернуть из функции at() и передать дальше.
        Message& operator=(Message&&) = delete;         // Запрет копирования
        Message(const Message&) = delete;
        Message& operator=(const Message&) = delete;
        ~Message();

        // Оператор вывода для любого типа
        template <typename T>
        inline Message& operator << (const T& rhs) {
            ss_ << rhs;
            return *this;
        }

        // Обработка манипуляторов потока (endl и т.п.)
        Message& operator << (ostream& (*manip)(ostream&));

        // Принудительный сброс сообщения в лог
        void flush(bool force_newline = false);

    private:
        void flush_on_destroy();

        logstream& parent_;
        LogLevel level_;
        ostringstream ss_;             // накопительный буфер
        bool closed_;                       // флаг: сообщение уже отправлено
    };

    // Конструктор с префиксомы
    explicit logstream(const string& prefix = string());
    ~logstream();

    inline Message at(LogLevel lvl) { return Message(*this, lvl); }
    inline Message trace() { return at(LogLevel::TRACE); }
    inline Message debug() { return at(LogLevel::DEBUG); }
    inline Message info() { return at(LogLevel::INFO); }
    inline Message warning() { return at(LogLevel::WARNING); }
    inline Message error() { return at(LogLevel::ERROR); }
    inline Message fatal() { return at(LogLevel::FATAL); }

    static void set_log_file(const string& name);
    static void set_level(LogLevel lvl);
    static LogLevel get_level();

    void set_prefix(const string& p);
    const string& get_prefix() const;

private:
    string prefix_;
    bool at_line_start_;
};