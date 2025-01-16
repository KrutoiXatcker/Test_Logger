#ifndef LOGLIB_H
#define LOGLIB_H

#include <string>
#include <fstream>
#include <chrono>
#include <iostream>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    Logger(const std::string& filename, LogLevel defaultLevel);
    ~Logger();

    void log(const std::string& message, LogLevel level);
    void setDefaultLevel(LogLevel level);

private:
    std::string getCurrentTime();
    void writeToLogFile(const std::string& message, LogLevel level);

    std::ofstream logFile;
    LogLevel defaultLevel;
    std::string filename;
};

#endif