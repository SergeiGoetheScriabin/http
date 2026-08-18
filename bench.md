#install apache bench

sudo apt-get install apache2-utils  (for ubuntu debian)


#bench on 1000 request, 10 concurrent
ab -n 1000 -c 10 http:://localhost:8080/


