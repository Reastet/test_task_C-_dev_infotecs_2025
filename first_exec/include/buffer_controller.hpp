#include <string>
#include <mutex>
#include <ctime>

#pragma once
//Класс-связка для системы ввода-вывода и системы логгирования
class BufferController
{
    private:
    //Буффер с данными
    std::string buffer;
    //Буффер для записи времени
    std::string cur_time;
    //Переменная, сообщающая логгирующему потоку, что можно читать данные
    bool flag_to_send;
    //Мьютексы для ограничения доступа к буфферам
    std::mutex buffer_safe_writer;
    std::mutex safe_flag_changer;
    public:
    BufferController();
    //Все функции редактирования данных являются потокобезопасными
    //Запись данных в буффер
    void write_to_buff(std::string& send_data);
    //чистка буффера
    void clear_buff();
    //Получение флага, буффера и времени
    int get_flag();
    std::string get_buffer();
    std::string get_time();
};