# Test basic GET
curl -v http://localhost:8080/
# Expected: 200 OK, HTML response

# Test POST
curl -X POST -d '{"name":"test"}' http://localhost:8080/api/data
# Expected: 201 Created, JSON response

# Test not found
curl -v http://localhost:8080/does_not_exist
# Expected: 404 Not Found

# Test malformed request
echo -e "GET / HTTP/1.0\r\nHost: localhost\r\n\r\n" | nc localhost 8080
# Expected: 200 OK
