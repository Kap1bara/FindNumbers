#ifndef _CLIENT_
#define _CLIENT_ 

#include "../wrappers/wrappers.hpp"
#include <iostream>
#include <string>
#include <cstring>

#define MAXLINE_SIZE 1024

class Cli
{
public:
	Cli()=default;
	Cli(const Cli&)=delete;
	Cli(int fd, sockaddr_in addr):sockfd(fd),servaddr(addr){}
	Cli & operator=(const Cli&)=delete;
	Cli(Cli &&)=delete;
	Cli & operator=(Cli&&)=delete;
	~Cli()=default;
	void runTCP();
	void runUDP();
private:
	int sockfd;
	sockaddr_in servaddr;
};


#endif