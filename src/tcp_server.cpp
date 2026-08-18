// tcp_server.cpp
#include "../include/tcp_server.hpp"

TCPServer::TCPServer(int port) : port_(port), running_(false) {
    create_socket();
    bind_socket();
    listen_socket();
}

TCPServer::~TCPServer() {
    stop();
    if (server_fd_ >= 0) {
        close(server_fd_);
    }
}

void TCPServer::create_socket() {
    server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd_ < 0) {
        throw std::runtime_error("socket() failed");
    }
    
    int opt = 1;
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
    }
}

void TCPServer::bind_socket() {
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port_);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    if (bind(server_fd_, (sockaddr*)&addr, sizeof(addr)) < 0) {
        throw std::runtime_error("bind() failed on port " + std::to_string(port_));
    }
    std::cout << "Server bound to port " << port_ << std::endl;
}

void TCPServer::listen_socket() {
    if (listen(server_fd_, 64) < 0) {
        throw std::runtime_error("listen() failed");
    }
    std::cout << "Listening for connections..." << std::endl;
}

void TCPServer::start(ConnectionHandler handler) {
    running_ = true;
    
    while (running_) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        
        int client_fd = accept(server_fd_, (sockaddr*)&client_addr, &client_len);
        
        if (client_fd < 0) {
            if (running_) {
                std::cerr << "accept() failed" << std::endl;
            }
            continue;
        }
        
        std::cout << "Client connected" << std::endl;
        handler(client_fd, client_addr);
        close(client_fd);
    }
}

void TCPServer::stop() {
    running_ = false;
}
