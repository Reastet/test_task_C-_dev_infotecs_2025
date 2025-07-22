#include "tcp_serv.hpp"

int main()
{
    TCPServer* serv = new TCPServer(9000);
    serv->connection_controller();
    delete serv;
}