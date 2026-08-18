#pragma once

#include <string>

class MimeTypes {

public:
    static std::string get_content_type(const std::string& path); 
};
