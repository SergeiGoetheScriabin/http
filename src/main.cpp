#include "../include/tcp_server.hpp"
#include "../include/http_request.hpp"
#include "../include/http_response.hpp"
#include "../include/mime_types.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

// RFC 9110 Section 6.4 - Read file content
std::string read_file(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return "";
    std::string content;
    file.seekg(0, std::ios::end);
    content.resize(file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&content[0], content.size());
    return content;
}

// RFC 9110 Section 7.1 - Build file path from URI
std::string get_file_path(const std::string& uri) {
    std::string path = uri;
    // Remove query string
    size_t query_pos = path.find('?');
    if (query_pos != std::string::npos) {
        path = path.substr(0, query_pos);
    }
    // Default to index.html
    if (path == "/" || path.empty()) {
        path = "/index.html";
    }
    return "www" + path;
}

// RFC 9110 Section 17.3 - Security: Prevent path traversal
bool is_path_safe(const std::string& path) {
    return path.find("..") == std::string::npos;
}

void handle_client(int client_fd, const sockaddr_in& client_addr) {
    char buffer[8192] = {0};
    ssize_t bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    
    if (bytes <= 0) {
        close(client_fd);
        return;
    }
    
    std::string raw(buffer, bytes);
    
    // Parse request
    HttpRequestParser parser;
    HttpRequest req = parser.parse(raw);
    
    // Print parsed request (debugging)
    std::cout << "Method: " << req.method << " URI: " << req.uri << std::endl;
    
    HttpResponse response;
    
    // RFC 9110 Section 9 - Methods
    if (req.method == "GET") {
        // RFC 9110 Section 9.3.1 - GET method
        std::string file_path = get_file_path(req.uri);
        
        if (!is_path_safe(file_path)) {
            response = HttpResponse::forbidden();
        } else if (!std::filesystem::exists(file_path)) {
            response = HttpResponse::not_found();
        } else {
            std::string content = read_file(file_path);
            std::string content_type = MimeTypes::get_content_type(file_path);
            response = HttpResponse::ok(content, content_type);
        }
    } else if (req.method == "HEAD") {
        // RFC 9110 Section 9.3.2 - HEAD method (same as GET but no body)
        std::string file_path = get_file_path(req.uri);
        
        if (!is_path_safe(file_path)) {
            response = HttpResponse::forbidden();
        } else if (!std::filesystem::exists(file_path)) {
            response = HttpResponse::not_found();
        } else {
            std::string content_type = MimeTypes::get_content_type(file_path);
            response = HttpResponse::ok("", content_type);  // Empty body for HEAD
        }
    } else {
        // RFC 9110 Section 15.5.6 - 405 Method Not Allowed
        response = HttpResponse::method_not_allowed();
    }
    
    std::string response_str = response.build();
    write(client_fd, response_str.c_str(), response_str.size());
    close(client_fd);
}

int main() {
    try {
        // Create www directory and default index.html
        std::filesystem::create_directory("www");
        if (!std::filesystem::exists("www/index.html")) {
            std::ofstream index("www/index.html");
            index << "<html><body><h1>HTTP Server Works!</h1>"
                  << "<p>RFC 9110 Implementation</p>"
                  << "<p>Try: <a href='/test.txt'>test.txt</a></p>"
                  << "</body></html>";
        }
        
        std::cout << "Starting RFC 9110 HTTP Server on port 8080..." << std::endl;
        TCPServer server(8080);
        server.start(handle_client);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
