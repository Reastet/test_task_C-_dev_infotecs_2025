#include <string>
#include <iostream>

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netdb.h> 
#include <errno.h> 
#include <unistd.h>
#include <string.h>

class TCPServer
{
    private:
    struct sockaddr_in address;
    int socket_id;
    public:
    TCPServer(int port);
    ~TCPServer();
    std::string recv_data(int connection_id);
    int connection_controller();
};