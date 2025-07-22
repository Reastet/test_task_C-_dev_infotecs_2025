#include "thread_controller.hpp"

ThreadController::ThreadController(IOSystem* iosys, Logger* log)
{
    this->iosystem = iosys;
    this->logger = log;
    this->is_end = 0;
}

void ThreadController::start_loops()
{
    std::cout << "Starting"<<std::endl;
    //Запуск потоков реализован через лямбда функции
    std::thread log([this](){this->logger->loop(std::ref(this->is_end));});
    std::thread ios([this](){this->iosystem->loop(std::ref(this->is_end)); });
    ios.join();
    log.join();
}