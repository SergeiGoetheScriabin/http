// tcp_server.hpp
#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdexcept>
#include <iostream>
#include <functional>

class TCPServer {
public:
    using ConnectionHandler = std::function<void(int client_fd, const sockaddr_in& client_addr)>;
    
    TCPServer(int port);
    ~TCPServer();
    
    TCPServer(const TCPServer&) = delete;
    TCPServer& operator=(const TCPServer&) = delete;
    
    void start(ConnectionHandler handler);
    void stop();
    
    int get_fd() const { return server_fd_; }

private:
    int server_fd_;
    int port_;
    bool running_;
    
    void create_socket();
    void bind_socket();
    void listen_socket();
};
