#include "buffer_controller.hpp"

BufferController::BufferController()
{
    this->flag_to_send = 0;
}

void BufferController::write_to_buff(std::string& send_data)
{
    this->buffer_safe_writer.lock();
    this->buffer = send_data;
    auto now = std::chrono::system_clock::now();
    auto time_c = std::chrono::system_clock::to_time_t(now);
    tm* timeinfo = localtime(&time_c);
    char buff[40];
    strftime(buff, 40, "%H:%M:%S", timeinfo);
    this->cur_time = buff;
    this->buffer_safe_writer.unlock();
    this->safe_flag_changer.lock();
    this->flag_to_send = 1;
    this->safe_flag_changer.unlock();
}

void BufferController::clear_buff()
{
    this->buffer_safe_writer.lock();
    this->safe_flag_changer.lock();
    this->buffer = "";
    this->cur_time = "";
    this->flag_to_send = false;
    this->safe_flag_changer.unlock();
    this->buffer_safe_writer.unlock();
}

int BufferController::get_flag()
{
    return this->flag_to_send;
}
std::string BufferController::get_buffer()
{
    return this->buffer;
}
std::string BufferController::get_time()
{
    return this->cur_time;
}