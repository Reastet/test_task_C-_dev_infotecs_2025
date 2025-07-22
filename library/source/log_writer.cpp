#include "log_writer.hpp"

LogWriter::LogWriter(std::string filename, message_importance level)
{
    this->socket_id = -1;
    if(filename != "")
    {
        this->filename = filename;
    }
    else
    {
        this->filename = "out.txt";
    }
    if(((unsigned int) level) > 5)
    {
        this->base_level = message_importance::VERY_LOW;
    }
    else
    {
        this->base_level = level;
    }
    this->output_stream.open(this->filename);
}

LogWriter::~LogWriter()
{
    this->output_stream.close();
    if(this->socket_id != -1)
    {
        close(this->socket_id);
    }
    
}

int LogWriter::SetNewLevel(message_importance new_level)
{
    if(new_level == message_importance::ERROR_VAL)
    {return 0;}
    this->base_level = new_level;
    return 1;
}

std::string ImportanceMessage(message_importance level)
{
    switch (level)
    {
    case message_importance::VERY_LOW:
        return "VERY_LOW";
    case message_importance::LOW:
        return "LOW";
    case message_importance::MEDIUM:
        return "MEDIUM";
    case message_importance::HIGH:
        return "HIGH";
    case message_importance::VERY_HIGH:
        return "VERY_HIGH";
    case message_importance::ERROR_VAL:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

message_importance string_to_message_importance(std::string level)
{
    if (level == "VERY_LOW")
    {    return message_importance::VERY_LOW;}
    else if (level == "LOW") 
    {    return message_importance::LOW;}
    else if (level == "MEDIUM") 
    {    return message_importance::MEDIUM;}
    else if (level == "HIGH") 
    {    return message_importance::HIGH;}
    else if (level == "VERY_HIGH") 
    {    return message_importance::VERY_HIGH;}
    else
    {
        return message_importance::ERROR_VAL;
    }
}

int LogWriter::WriteMessageToFile(std::string message, message_importance level)
{
    if(level < this->base_level)
    {
        return -1;
    }
    auto now = std::chrono::system_clock::now();
    auto time_c = std::chrono::system_clock::to_time_t(now);
    tm* timeinfo = localtime(&time_c);
    char buff[40];
    strftime(buff, 40, "%H:%M:%S", timeinfo);
    this->output_stream << message << " " << ImportanceMessage(level) << " " << buff << std::endl;
    return 0;
}

int LogWriter::WriteMessageToFile(std::string message, std::string time, message_importance level)
{
    if(level < this->base_level)
    {
        return -1;
    }
    this->output_stream << message << " " << ImportanceMessage(level) << " " << time << std::endl;
    return 0;
}


LogWriter* log_writer_fabric(std::string filename, message_importance level)
{
    return new LogWriter(filename, level);
}
void log_writer_destroyer(LogWriter* writer)
{
    delete writer;
}


int LogWriter::InitNetwork(std::string ip_addr, int port)
{
    this->socket_id = socket(AF_INET, SOCK_STREAM, 0);
    if(this->socket_id < 0)
    {
        return -2;
    }
    memset(&(this->address), 0, sizeof(this->address));
    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(port);
    this->address.sin_addr.s_addr = inet_addr(ip_addr.c_str());
    if(connect(this->socket_id, (struct sockaddr*)&(this->address), sizeof(this->address))!=0)
    {
        return -1;
    }
    
    return 0;
}


int LogWriter::SendMessage(std::string message, message_importance level)
{
    std::string out = message+" " + ImportanceMessage(level)+" ";
    auto now = std::chrono::system_clock::now();
    auto time_c = std::chrono::system_clock::to_time_t(now);
    tm* timeinfo = localtime(&time_c);
    char buff[40];
    strftime(buff, 40, "%H:%M:%S", timeinfo);
    out+=std::string(buff);
    out+="\n";
    int send_size = 0;
    while(send_size < out.length())
    {
        int res = send(this->socket_id, out.c_str(), out.length(), 0);
        if(res < 0)
        {
            return -1;
        }
        send_size+=res;
    }
}
int LogWriter::SendMessage(std::string message, std::string time, message_importance level)
{

    std::string out = message+" " + ImportanceMessage(level)+" "+time+"\n";
    int send_size = 0;
    while(send_size < out.length())
    {
        int res = send(this->socket_id, out.c_str(), out.length(), 0);
        if(res < 0)
        {
            return -1;
        }
        send_size+=res;
    }
}


int LogWriter::DeinitNetwork()
{
    if(this->socket_id == -1)
    {
        return -1;
    }
    std::string out = "\0";
    int send_size = 0;
    while(send_size < out.length())
    {
        int res = send(this->socket_id, out.c_str(), out.length(), 0);
        if(res < 0)
        {
            return -2;
        }
        send_size+=res;
    }
    close(this->socket_id);
    this->socket_id = -1;
}