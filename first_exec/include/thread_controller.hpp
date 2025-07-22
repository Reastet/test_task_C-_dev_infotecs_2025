#include <thread>
#include "i_o_system.hpp"
#include "logger.hpp"

//Система управления потоками
class ThreadController
{
    private:
    //Переменные под системы ввода-вывода и логгер
    IOSystem* iosystem;
    Logger* logger;
    //Переменная, связывающая потоки
    int is_end;
    public:
    ThreadController(IOSystem* iosys, Logger* log);
    void start_loops();
};
