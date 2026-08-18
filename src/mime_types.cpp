// mime_types.cpp
// RFC 9110 Section 8.3 - Implementation

#include "../include/mime_types.hpp"
#include <unordered_map>

static const std::unordered_map<std::string, std::string> mime_map = {
    // Text types
    {".html", "text/html"},
    {".htm", "text/html"},
    {".css", "text/css"},
    {".js", "application/javascript"},
    {".json", "application/json"},
    {".xml", "application/xml"},
    {".txt", "text/plain"},
    {".csv", "text/csv"},
    
    // Image types
    {".png", "image/png"},
    {".jpg", "image/jpeg"},
    {".jpeg", "image/jpeg"},
    {".gif", "image/gif"},
    {".svg", "image/svg+xml"},
    {".ico", "image/x-icon"},
    
    // Application types
    {".pdf", "application/pdf"},
    {".zip", "application/zip"},
    {".gz", "application/gzip"},
};

std::string MimeTypes::get_content_type(const std::string& path) {
    // RFC 9110 Section 8.3 - Determine media type
    size_t dot = path.find_last_of('.');
    if (dot != std::string::npos) {
        auto it = mime_map.find(path.substr(dot));
        if (it != mime_map.end()) {
            return it->second;
        }
    }
    // RFC 2046 Section 4.5.1 - Default to binary if unknown
    return "application/octet-stream";
}
