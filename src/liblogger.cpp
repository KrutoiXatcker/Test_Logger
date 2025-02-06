#include "liblogger.h"


Logger::Logger(const std::string& filename, LogLevel defaultLevel)
    : filename(filename), defaultLevel(defaultLevel)
{
    logFile.open(filename, std::ios::app);  // Открытие файла в режиме добавления
    if (!logFile) {
        std::cerr << "Error opening log file." << std::endl;
    }
}


Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}


void Logger::log(const std::string& message, LogLevel level) noexcept
{
    if (static_cast<int>(level) >= static_cast<int>(defaultLevel)) {
        std::string levelStr;
        switch (level) {
            case LogLevel::INFO: levelStr = "INFO"; break;
            case LogLevel::WARNING: levelStr = "WARNING"; break;
            case LogLevel::ERROR: levelStr = "ERROR"; break;
        }
        std::string logMessage = getCurrentTime() + " [" + levelStr + "] \t" + message;
        WriteToLogFile(logMessage, level);
    }
}


void Logger::setDefaultLevel(LogLevel level) noexcept
{
    defaultLevel = level;
}


std::string Logger::getCurrentTime() noexcept
{
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::string timeStr = std::ctime(&time);
    timeStr.pop_back();  // Удаляем символ новой строки
    return timeStr;
}

void Logger::WriteToLogFile(const std::string& message, LogLevel level)
{
    std::lock_guard<std::mutex> g(m);   // Блокировка мьютексом 

    if (logFile.is_open())
    {   
        //  Запись в лог файл 
        logFile << message << std::endl;
    }
    else
    {   
        // Вывод сообщения об ошибке в стандартный поток ошибок, если файл лога не удалось открыть  
        std::cerr << "Log file not open." << std::endl;
    }
}