    #include "app.h"
    

    App::App(const std::string& logFile , LogLevel level)
      : logger_(std::make_shared<Logger>(logFile, level)) {}


    void App::run() {
        std::vector<std::thread> threads;

        // Запуск потоков с разными уровнями логирования и задержками
         threads.emplace_back([this] { logThread(LogLevel::INFO, 500); });
         threads.emplace_back([this] { logThread(LogLevel::WARNING, 1000); });
         threads.emplace_back([this] { logThread(LogLevel::ERROR, 2000); });
      
        for(auto& t : threads){
            t.join();
        }
        
        std::cout << "All threads have finished." << std::endl;
    }

    void App::logThread(LogLevel level, int delay_ms) {
        for (int i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
            logger_->log("Log message from thread with level: " + std::to_string(static_cast<int>(level)) + ", iteration: " + std::to_string(i), level);
        }
     }
