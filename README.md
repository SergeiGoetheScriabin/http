HTTP/1.1 Server

A lightweight HTTP/1.1 server written in C++20 using POSIX sockets. The server handles TCP connections, parses HTTP requests, builds responses, and serves static files from a local web root.
Features

    HTTP/1.1 request parsing
    GET and HEAD methods
    Static file serving
    Content-Type detection
    Content-Length handling
    404 Not Found and 403 Forbidden responses
    Path traversal protection
    Clean socket management using RAII
    No third-party networking libraries

Build

git clone <repository-url>
cd http

mkdir -p build
cd build
cmake ..
make

Run

Start the server from the build directory:

./server

The server listens on:

http://localhost:8080

The default web root is:

www/

Usage
GET

Request the default page:

curl http://localhost:8080/

Request a specific file:

curl http://localhost:8080/test.txt

HEAD

Request headers without the response body:

curl -I http://localhost:8080/

404 Response

Request a file that does not exist:

curl -v http://localhost:8080/not-found

Static Files

Create a file in the web root:

echo "Hello, world." > ../www/test.txt

Then request it:

curl http://localhost:8080/test.txt

Browser

With the server running, open:

http://localhost:8080

Benchmarks

Benchmarks are run locally with ApacheBench.

Run:

ab -n 1000 -c 10 http://localhost:8080/

Example output:

Concurrency Level:      10
Complete requests:      1000
Failed requests:        0
Requests per second:    <RPS> [#/sec]
Time per request:       <TIME> [ms]
Transfer rate:          <RATE> [Kbytes/sec]

Results will vary depending on the machine and environment.
Project Structure

http/
├── include/
│   ├── tcp_server.hpp
│   ├── http_request.hpp
│   ├── http_response.hpp
│   └── mime_types.hpp
├── src/
│   ├── main.cpp
│   ├── tcp_server.cpp
│   ├── http_request.cpp
│   ├── http_response.cpp
│   └── mime_types.cpp
├── www/
│   └── index.html
├── CMakeLists.txt
└── README.md

Implementation

The server is intentionally small and uses POSIX sockets directly rather than a networking framework. The code is organized around TCP connection handling, HTTP request parsing, response construction, and static file serving.

