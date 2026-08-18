basically we have to do this...

ABNF Syntax for RFC 9110.

## 2.1

>ABNF is the new language rules for HTTP.

```method = token  

```   request-target = origin-form
```   HTTP-version = HTTP-name "/" DIGIT "." DIGIT
 
We must parse bytes such that they follow thes erules.

An example of this would be like

method = GET
request-target = /index.html
HTTP-version = HTTP/1.1

the parser has to be like.

GET -> you gotta match the token
/index -> you gotta match origin-form
HTTP1.1 -> you gotta match index version





while(server_running) {
    accept connections

    client = accept();


    recv bytes

    bytes = recv(client);

    request = parse_http(bytes);

    response = handle_request(request);

    respones_bytes =  serialize(response);


    send(client, response bytes);

    close(client);
}
