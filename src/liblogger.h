#ifndef LOGLIB_H
#define LOGLIB_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <mutex>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(const std::string& filename, LogLevel defaultLevel);
    ~Logger();

    void log(const std::string& message, LogLevel level) noexcept;
    void setDefaultLevel(LogLevel level) noexcept;

private:

    std::string getCurrentTime() noexcept;
    void WriteToLogFile(const std::string& message, LogLevel level);

    std::ofstream logFile;
    LogLevel defaultLevel;
    std::string filename;
    std::mutex m;
};

#endif