Copy everything below directly into README.md:

## RFC 9110 References

| Feature | RFC 9110 Section |
|---|---|
| TCP Connections | 3.3 |
| Request-Line | 3.4 |
| URI References | 4.1 |
| Field Names | 5.1 |
| Field Values | 5.5 |
| Date/Time Formats | 5.6.7 |
| Date Header | 6.6.1 |
| Content | 6.4 |
| Host Header | 7.2 |
| Content-Type | 8.3 |
| Content-Length | 8.6 |
| GET Method | 9.3.1 |
| HEAD Method | 9.3.2 |
| 200 OK | 15.3.1 |
| 403 Forbidden | 15.5.4 |
| 404 Not Found | 15.5.5 |
| 405 Method Not Allowed | 15.5.6 |
| Path Traversal | 17.3 |

## Future Enhancements

- [ ] Last-Modified / If-Modified-Since
- [ ] 304 Not Modified responses
- [ ] POST method with form data
- [ ] Thread pool for concurrent connections
- [ ] Range requests
- [ ] Persistent connections / Keep-Alive
- [ ] Request and response logging

## Supported Methods

| Method | Status |
|---|---|
| GET | Supported |
| HEAD | Supported |

## Supported Status Codes

| Status | Description |
|---|---|
| 200 | OK |
| 403 | Forbidden |
| 404 | Not Found |
| 405 | Method Not Allowed |

## Example Response

```http
HTTP/1.1 200 OK
Date: Mon, 17 Mar 2025 12:00:00 GMT
Content-Type: text/html
Content-Length: 89
Connection: close

<html><body><h1>HTTP Server Works!</h1>...

Quick Tests

Start the server:

cd ~/http/build
./server


Then, from another terminal:

# Basic GET
curl http://localhost:8080/

# HEAD request
curl -I http://localhost:8080/

# 404 response
curl -v http://localhost:8080/notfound

# Create and serve a static file
echo "Test content" > ../www/test.txt
curl http://localhost:8080/test.txt

# Benchmark
ab -n 1000 -c 10 http://localhost:8080/
