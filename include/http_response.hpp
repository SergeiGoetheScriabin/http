#pragma once

#include <string>
#include <unordered_map>

class HttpResponse {
public:

    HttpResponse();
// RFC 9110 Section 15 Status COdes
    void set_status(int code, const std::string& reason);
    void set_header(const std::string& name, const std::string& value);
    void set_body(const std::string& body);

    // Build full response string
    std::string build() const;

    // Helpers
    static HttpResponse ok(const std::string& body, const std::string& content_type = "text/html");
    static HttpResponse not_found();
    static HttpResponse method_not_allowed();
    static HttpResponse forbidden();

private:
    int status_code_;
    std::string status_reason_;
    std::unordered_map<std::string, std::string> headers_;
    std::string body_;

    std::string get_date() const; // 6.6.1
};
