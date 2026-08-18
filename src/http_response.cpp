#include "../include/http_response.hpp"
#include <sstream>
#include <chrono>
#include <ctime>

HttpResponse::HttpResponse() : status_code_(200), status_reason_("OK") {}

void HttpResponse::set_status(int code, const std::string& reason) {
    status_code_ = code;
    status_reason_ = reason;
}

void HttpResponse::set_header(const std::string& name, const std::string& value) {
    headers_[name] = value;
}

void HttpResponse::set_body(const std::string& body) {
    body_ = body;
    set_header("Content-Length", std::to_string(body.size()));
}

std::string HttpResponse::build() const {
    std::ostringstream response;

    // RFC 9110 Section 3.4 - Status-Line
    // Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
    response << "HTTP/1.1 " << status_code_ << " " << status_reason_ << "\r\n";

    // RFC 9110 Section 6.6.1 - Date header
    response << "Date: " << get_date() << "\r\n";

    for (const auto& [name, value] : headers_) {
        response << name << ": " << value << "\r\n";
    }

    response << "\r\n";
    response << body_;

    return response.str();
}

std::string HttpResponse::get_date() const {
    // RFC 9110 Section 5.6.7 - Date/Time Formats
    // IMF-fixdate = day-name "," SP date1 SP time-of-day SP GMT
    auto now = std::chrono::system_clock::now();
    auto time = std::chrono::system_clock::to_time_t(now);
    std::tm tm = *std::gmtime(&time);
    
    char buf[64];
    strftime(buf, sizeof(buf), "%a, %d %b %Y %H:%M:%S GMT", &tm);
    return buf;
}

// RFC 9110 Section 15.3.1 - 200 OK
HttpResponse HttpResponse::ok(const std::string& body, const std::string& content_type) {
    HttpResponse resp;
    resp.set_status(200, "OK");
    resp.set_header("Content-Type", content_type);
    resp.set_body(body);
    resp.set_header("Connection", "close");
    return resp;
}

// RFC 9110 Section 15.5.5 - 404 Not Found
HttpResponse HttpResponse::not_found() {
    HttpResponse resp;
    resp.set_status(404, "Not Found");
    resp.set_header("Content-Type", "text/html");
    std::string body = "<html><body><h1>404 Not Found</h1><p>The requested resource was not found.</p></body></html>";
    resp.set_body(body);
    resp.set_header("Connection", "close");
    return resp;
}

// RFC 9110 Section 15.5.6 - 405 Method Not Allowed
HttpResponse HttpResponse::method_not_allowed() {
    HttpResponse resp;
    resp.set_status(405, "Method Not Allowed");
    resp.set_header("Content-Type", "text/html");
    resp.set_header("Allow", "GET, HEAD");  // RFC 9110 Section 10.2.1
    std::string body = "<html><body><h1>405 Method Not Allowed</h1></body></html>";
    resp.set_body(body);
    resp.set_header("Connection", "close");
    return resp;
}

// RFC 9110 Section 15.5.4 - 403 Forbidden
HttpResponse HttpResponse::forbidden() {
    HttpResponse resp;
    resp.set_status(403, "Forbidden");
    resp.set_header("Content-Type", "text/html");
    std::string body = "<html><body><h1>403 Forbidden</h1></body></html>";
    resp.set_body(body);
    resp.set_header("Connection", "close");
    return resp;
}
