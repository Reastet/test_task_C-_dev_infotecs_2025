#include "tcp_serv.hpp"

TCPServer::TCPServer(int port)
{
    this->socket_id = socket(AF_INET, SOCK_STREAM, 0);
    memset(&(this->address), 0, sizeof(this->address));
    this->address.sin_family = AF_INET;
    this->address.sin_port = htons(port);
    this->address.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(this->socket_id, (struct sockaddr*) &(this->address), sizeof(this->address)) < 0) 
    {    
        std::cout << "bind_error"<<std::endl;
        return; 
    }
    if (listen(this->socket_id, 1) < 0) 
    {
        std::cout <<"listen_error"<<std::endl;
        return;
    }

    
}

int TCPServer::connection_controller()
{
    socklen_t addrlen = sizeof(this->address); 
    
    int connection_id = accept(this->socket_id, (struct sockaddr*) &(this->address), &addrlen); 
    std::cout<<"SMB connected"<<std::endl;
    std::string out;
    int count = 0;
    do
    {
        count ++;
        out = this->recv_data(connection_id);
        std::cout << out << std::endl;
        if(count == 4)
        {
            break;
        }
    } while (out != "END");
    
}

std::string TCPServer::recv_data(int connection_id)
{
    char buffer[1024];
    int rcv;

    int i; 
    rcv = recv(connection_id, buffer, sizeof(buffer)-1, 0); 
    buffer[rcv] = 0;
    std::string out = buffer;
    if(out == "\0")
    {
        out = "END";
    }
    return out;
}

TCPServer::~TCPServer()
{
    close(this->socket_id);
}
