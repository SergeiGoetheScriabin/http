# Test GET request
curl -v http://localhost:8080/

# Test HEAD request (headers only)
curl -I http://localhost:8080/

# Test 404 Not Found
curl -v http://localhost:8080/doesntexist

# Test static file
echo "Hello World" > ../www/test.txt
curl -v http://localhost:8080/test.txt

# Test image (create or download one)
curl -v http://localhost:8080/image.png
