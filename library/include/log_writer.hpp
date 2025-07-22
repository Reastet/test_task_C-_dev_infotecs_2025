#include <string>
#include <fstream>
#include <chrono>
#include <ctime>


#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#pragma once

//enum класс для задания важности сообщения
enum class message_importance {
    ERROR_VAL,
    VERY_LOW,
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH
};

//Функции для превращения сообщения в строку и из строки в соответствующее значение
std::string ImportanceMessage(message_importance level);
message_importance string_to_message_importance(std::string level);

//Класс для записи логов
class LogWriter
{
    private:
        std::string filename; //Имя файла
        message_importance base_level;//Минимальный уровень сообщения
        std::ofstream output_stream;//Выходной поток записи (дескриптор файла)
        //ID сокета и параметры адреса
        int socket_id; 
        struct sockaddr_in address;
    public:
        //Конструктор с заданием имени файла и минимального уровня, при неправильных значениях ставит по умолчанию output.txt и VERY_LOW
        LogWriter(std::string filename, message_importance level);
        ~LogWriter();
        int SetNewLevel(message_importance new_level);//Меняет уровень сообщения
        //Функции записи в файл. Одна используется, когда нужно указать текущее время, а вторая-если время подается извне
        //(например, по каким-то причинам запись была отложена, но время сохранено)
        int WriteMessageToFile(std::string message, message_importance level);
        int WriteMessageToFile(std::string message, std::string time, message_importance level);
        //Инициализация подключения, принимает ip адресс и порт
        int InitNetwork(std::string ip_addr, int port);
        //Отправка сообщений. Аналогична WriteMessageToFile
        int SendMessage(std::string message, message_importance level);
        int SendMessage(std::string message, std::string time, message_importance level);
        //Деинициализация сетевых настроек
        int DeinitNetwork();
};
//Фабрика и деструктор вышеописанного класса. Предназначены для динамической подгрузки библиотек
LogWriter* log_writer_fabric(std::string filename, message_importance level);
void log_writer_destroyer(LogWriter* writer);