#include <iostream>
#include <string>
#include <chrono>
#include "buffer_controller.hpp"
//Система ввода вывода
class IOSystem
{
    private:
    //Буффер для ввода
    std::string buffer;
    //Контроллер буффера
    BufferController* buff;
    public:
    IOSystem(BufferController* buffer);
    //Бесконечный цикл. is_end-внешняя переменная, связывающая
    //поток ввода-вывода и логгирующий поток
    void loop(int &is_end);
    //Функция ввода данных
    void enter_data();
};