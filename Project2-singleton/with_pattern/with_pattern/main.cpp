#include "logger.h"

int main() {
    logstream::set_log_file("test.log");
    logstream::set_level(LogLevel::DEBUG);

    logstream lg("main");

    lg.debug() << "debug message: x=" << 42 << endl;
    lg.info() << "app started" << endl;
    lg.at(LogLevel::WARNING) << "low memory: " << 123 << endl;
    lg.error() << "fatal error code " << -1 << endl;

    return 0;
}