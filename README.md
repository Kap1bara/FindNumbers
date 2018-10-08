# FindNumbers
Client-Server application. Client enters string and server finds all the numbers, sort them, sum them and resend to client

Serv/ contains server's source code. 
Executable file runs UDP and TCP servers in two threads. This servers recieve data from clients (not more then 1024 ASCII-symbols), server searchs numbers, sort it and sum it. As it may be that there is numbers which contains over 100 digits, so server uses gmp library to handle it. </br> Cli/ contains client application source. Client may be started in two modes TCP and UDP. It sends string and recieve result from server.
