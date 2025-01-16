#ifndef APP_H
#define APP_H

#include <string>
#include <memory>
#include <thread>
#include <chrono>
#include <vector>
#include "liblogger.h" 
#include <mutex>

class App {
public:
App(const std::string& logFile,LogLevel leval);
void run();
private:

    std::shared_ptr<Logger> logger_; 

    void logThread(LogLevel level, int delay_ms); 

    std::mutex logger_mutex;
};


#endif