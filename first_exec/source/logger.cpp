#include <logger.hpp>

Logger::Logger(BufferController* buff, std::string filename, std::string level)
{
    this->buff = buff;
    this->init_logger_lib(filename, level);

    /////
    //Данный участок кода является демонстрационным
    //И показывает работу по сети
    //int res = this->log_writer->InitNetwork(std::string("127.0.0.1"), 9000);
    /////
}
Logger::~Logger()
{
    /////
    //Данный участок кода является демонстрационным
    //И показывает работу по сети
    //this->log_writer->DeinitNetwork();
    /////
    log_writer_destroyer(this->log_writer);
}

int Logger::init_logger_lib(std::string file_name, std::string level)
{
    this->log_writer = log_writer_fabric(file_name, string_to_message_importance(level));
}

bool Logger::is_buff_ready()
{
    return this->buff->get_flag();
}

void Logger::log_buff_data()
{
    auto data = this->buff->get_buffer();
    auto time = this->buff->get_time();
    this->buff->clear_buff();
    this->log_writer->WriteMessageToFile(data, time, string_to_message_importance("MEDIUM"));
    /////
    //Данный участок кода является демонстрационным
    //И показывает работу по сети
    //this->log_writer->SendMessage(data, time, string_to_message_importance("MEDIUM"));
    /////
}

void Logger::loop(int &is_end)
{
    while(true)
    {if(this->is_buff_ready())
    {
        this->log_buff_data();
    }
    //Если поток ввода-вывода поменяет переменную
    //Данный цикл прекратит работу
    if(is_end)
    {
        return;
    }}
}