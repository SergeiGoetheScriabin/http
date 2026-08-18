#pragma once

#include <string>
#include <unordered_map>

struct HttpRequest {
    std::string method; // GET, POST, etc. (RFC 9110 Section 9)
    std::string uri; // /index.html (RFC 9110 Section 4.1)
    std::string version; // HTTP1.1 (RFC 9110 Section 2.5)
    std::unordered_map<std::string, std::string> headers; // RFC 9110 Section 5.1
    std::string body; // RFC Section 6.4
};

class HttpRequestParser {
public:
    HttpRequest parse(const std::string& raw);
};
