#include <iostream>
#include "liblogger.h"
#include <string>
#include "app.h"
#include <getopt.h>


// Функция проверки уровня логирования
LogLevel checkLevel(const std::string& levelStr) {
    if (levelStr == "1") return LogLevel::WARNING;
    if (levelStr == "2") return LogLevel::ERROR;
    return LogLevel::INFO; // По умолчанию INFO
}

int main(int argc, char **argv) {

    // Эти два переменых будут переданы во время создания обекта класса logger 
    std::string infoLogPath = "./log_info.txt";
    LogLevel level = LogLevel::INFO;


    // Объявление массива структур option, для описания длинных параметров командной строки
    static struct option long_options[] = {
        {"log-path", required_argument, 0, 'p'},
        {"log-level", required_argument, 0, 'l'},
        {0, 0, 0, 0}
    };

    //Создание цикла для разбора аргументов командной строки
    int option;
    int option_index = 0;
    while ((option = getopt_long(argc, argv, "p:l:", long_options, &option_index)) != -1) {
        switch (option) {
            case 'p':
              infoLogPath = optarg;
              break;
          case 'l':
              level = checkLevel(optarg);
                break;
           case '?':
            std::cout << "Error: Unknown option" << std::endl;
               return 1;
             default:
            break;
        }
    }

    // Вывод на экран настроек перед запуском приложения 
    std::cout << "Log path: " << infoLogPath << std::endl;
    std::cout << "Log level: " << static_cast<int>(level) << std::endl;


    // Создание и запуск самого приложения 
    App app(infoLogPath,level);
    app.run();

    return 0;
}
