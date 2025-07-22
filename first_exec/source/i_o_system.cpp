#include "i_o_system.hpp"

IOSystem::IOSystem(BufferController* buffer)
{
    this->buff = buffer;
}

void IOSystem::enter_data()
{
  
   std::cout << "You can enter data:"<<std::endl;
   std::cin >> this->buffer;
   if(this->buffer != "Exit")
   {this->buff->write_to_buff(this->buffer);
   this->buffer = "";}
}

void IOSystem::loop(int &is_end)
{
    while(this->buffer != "Exit")
    {
        if(this->buff->get_flag() == false)
        {
        std::cout << "Please, whait, while old data will be logged" << std::endl;
        this->enter_data();
        }

    }
    
    is_end = 1;
}