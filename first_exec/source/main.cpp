#include "thread_controller.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>



using namespace std;



int main(int argc, char** argv)
{
    if(argc != 3)
    {
        cout <<"Incorrect arguments num" << endl;
    }
    string filename = argv[1];
    string level = argv[2];
    BufferController* buffer = new BufferController;
    Logger* log = new Logger(buffer, filename, level);
    IOSystem* ios = new IOSystem(buffer);
    ThreadController* thread_cont = new ThreadController(ios, log);
    thread_cont->start_loops();
}
