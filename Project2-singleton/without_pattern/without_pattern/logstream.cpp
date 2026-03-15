#include "logger.h"

LogManager mgr;

logstream::Message::Message(logstream& parent, LogLevel level)
    : parent_(parent), level_(level), closed_(false) {
}

// Конструктор перемещения: забирает строковый поток и помечает исходный как закрытый
logstream::Message::Message(Message&& other) noexcept
    : parent_(other.parent_), level_(other.level_),
    ss_(move(other.ss_)), closed_(other.closed_) {
    other.closed_ = true;
}

logstream::Message::~Message() {
    if (!closed_) flush_on_destroy();
}

// Оператор для манипуляторов: если endl – немедленно отправляем строку
logstream::Message& logstream::Message::operator<<(ostream& (*manip)(ostream&)) {
    typedef ostream& (*manip_t)(ostream&);
    if (manip == static_cast<manip_t>(endl)) {
        ss_ << manip;                          // добавляет '\n'
        string s = ss_.str();
        ss_.str("");
        mgr.write(level_, parent_.prefix_, s, parent_.at_line_start_, true);
        closed_ = true;
    }
    else {
        ss_ << manip;
    }
    return *this;
}

void logstream::Message::flush(bool force_newline) {
    if (closed_) return;
    string s = ss_.str();
    ss_.str("");
    if (!s.empty() || force_newline) {
        if (force_newline) s += "\n";
        mgr.write(level_, parent_.prefix_, s, parent_.at_line_start_, true);
    }
    closed_ = true;
}

// Сброс остатка сообщения при разрушении (без принудительного flush)
void logstream::Message::flush_on_destroy() {
    if (closed_) return;
    string leftover = ss_.str();
    ss_.str("");
    if (!leftover.empty()) {
        mgr.write(level_, parent_.prefix_, leftover, parent_.at_line_start_, false);
    }
    closed_ = true;
}

// Конструктор: запоминает префикс и увеличивает счётчик ссылок
logstream::logstream(const string& prefix)
    : prefix_(prefix), at_line_start_(true) {
    mgr.add_ref();
}

// Деструктор: уменьшает счётчик ссылок
logstream::~logstream() {
    mgr.release_ref();
}

void logstream::set_prefix(const string& p) {
    prefix_ = p;
}

const string& logstream::get_prefix() const {
    return prefix_;
}

void logstream::set_log_file(const string& name) {
    mgr.set_file(name);
}

void logstream::set_level(LogLevel lvl) {
    mgr.set_level(lvl);
}

LogLevel logstream::get_level() {
    return mgr.get_level();
}