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
//Копия .hpp файла библиотеки
enum class message_importance {
    ERROR_VAL,
    VERY_LOW,
    LOW,
    MEDIUM,
    HIGH,
    VERY_HIGH
};
std::string ImportanceMessage(message_importance level);
message_importance string_to_message_importance(std::string level);
class LogWriter
{
    private:
        std::string filename;
        message_importance base_level;
        std::ofstream output_stream;
        int socket_id;
        struct sockaddr_in address;
    public:
        LogWriter(std::string filename, message_importance level);
        ~LogWriter();
        int SetNewLevel(message_importance new_level);
        int WriteMessageToFile(std::string message, message_importance level);
        int WriteMessageToFile(std::string message, std::string time, message_importance level);
        int InitNetwork(std::string ip_addr, int port);
        int SendMessage(std::string message, message_importance level);
        int SendMessage(std::string message, std::string time, message_importance level);
        int DeinitNetwork();
};

LogWriter* log_writer_fabric(std::string filename, message_importance level);
void log_writer_destroyer(LogWriter* writer);