// http_request.cpp
// RFC 9110 Sections 3.4, 5 - Implementation

#include "../include/http_request.hpp"
#include <sstream>
#include <algorithm>
#include <cctype>

HttpRequest HttpRequestParser::parse(const std::string& raw) {
    HttpRequest req;
    std::istringstream stream(raw);
    std::string line;
    
    // Step 1: Parse request-line (RFC 9110 Section 3.4)
    // Example: "GET /index.html HTTP/1.1"
    std::getline(stream, line);
    if (!line.empty() && line.back() == '\r') line.pop_back();  // Remove \r
    
    std::istringstream line_stream(line);  // FIXED: was "isstringstream"
    line_stream >> req.method >> req.uri >> req.version;
    
    // Step 2: Parse headers (RFC 9110 Section 5)
    // Example: "Host: localhost:8080"
    while (std::getline(stream, line)) {
        if (line.empty() || line == "\r") break;  // Empty line = end of headers
        
        if (!line.empty() && line.back() == '\r') line.pop_back();
        
        size_t colon = line.find(':');  // FIXED: was "coln"
        if (colon != std::string::npos) {
            std::string name = line.substr(0, colon);  // FIXED: was "coln"
            std::string value = line.substr(colon + 1);  // FIXED: was "std:string"
            
            // RFC 9110 Section 5.5 - Remove whitespace
            value.erase(0, value.find_first_not_of(" \t"));  // FIXED: added space and tab
            value.erase(value.find_last_not_of(" \t") + 1);  // FIXED: added space and tab
            
            req.headers[name] = value;
        }
    }
    
    // Step 3: Parse body if Content-Length exists (RFC 9110 Section 8.6)
    size_t header_end = raw.find("\r\n\r\n");
    if (header_end != std::string::npos) {
        auto it = req.headers.find("Content-Length");
        if (it != req.headers.end()) {
            try {
                int length = std::stoi(it->second);
                if (length > 0) {
                    req.body = raw.substr(header_end + 4, length);
                }
            } catch (...) {
                // Invalid Content-Length, ignore
            }
        }
    }
    
    return req;
}
