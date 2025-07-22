#include <string>
#include <log_writer.hpp>
#include "buffer_controller.hpp"
#include <iostream>
//Логгирующий класс, управляющий библиотекой
class Logger
{
    private:
    //Переменные под буффер связку и логгирующий класс
    BufferController* buff;
    LogWriter* log_writer;
    public:
    Logger(BufferController* buff, std::string filename, std::string level);
    ~Logger();
    //Инициализация библиотеки
    int init_logger_lib(std::string file_name, std::string level);
    //Бесконечный цикл, проверка буффера и логгирование
    void loop(int &is_end);
    bool is_buff_ready();
    void log_buff_data();
};