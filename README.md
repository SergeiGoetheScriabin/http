# HTTP/1.1 Server from Scratch

A lightweight HTTP/1.1 server built from scratch using only POSIX sockets and C++20, following **RFC 9110** (HTTP Semantics). No third-party libraries - just the C++ standard library and system calls.

## 📋 Project Overview

This server demonstrates deep understanding of:
- TCP/IP networking (socket programming)
- HTTP/1.1 protocol semantics
- RFC 9110 compliance
- Modern C++ (RAII, OOP, std::filesystem)
- System programming

## 🚀 Features Implemented

### Phase 1: TCP Server (RFC 9110 Section 3.3)
- Socket creation, binding, listening, and accepting
- RAII for automatic socket cleanup
- Non-copyable server design

### Phase 2: HTTP Request Parser (RFC 9110 Sections 3.4, 5, 7.1)
- Request-Line parsing (Method, URI, HTTP-Version)
- Header field parsing (case-insensitive)
- Content-Length handling for request body
- Whitespace trimming (RFC 9110 Section 5.5)

### Phase 3: HTTP Response Builder (RFC 9110 Sections 15, 6.6.1)
- Status codes: 200 OK, 404 Not Found, 405 Method Not Allowed, 403 Forbidden
- Date header (RFC 9110 Section 5.6.7 - IMF-fixdate format)
- Content-Type based on file extension
- Content-Length for proper message framing
- Connection: close header

### Phase 4: Static File Serving (RFC 9110 Sections 6.4, 7.1)
- File path resolution from URI
- Default index.html handling
- Binary file support (images, PDFs, etc.)

### Phase 5: Security (RFC 9110 Section 17.3)
- Path traversal prevention (`..` filtering)
- 403 Forbidden for unsafe paths

### Phase 6: HTTP Methods (RFC 9110 Section 9)
- GET method (Section 9.3.1) - retrieve resources
- HEAD method (Section 9.3.2) - retrieve headers only

## 🛠️ Building

```bash
# Clone or navigate to project
cd ~/http

# Create build directory
mkdir -p build && cd build

# Configure with CMake
cmake ..

# Build
make

# Run server
./server
