#ifndef _Serv_
#define _Serv_ 

#include "../wrappers/wrappers.hpp"
#include <cstring>
#include <string>
#include <thread>
#include <iostream>

class Serv
{
public:
	explicit Serv(int port):TCPlistenfd(wSocket(AF_INET, SOCK_STREAM,0)),
			UDPlistenfd(wSocket(AF_INET, SOCK_DGRAM,0))
	{
		memset(&servaddr,0,sizeof(servaddr));
		servaddr.sin_family=AF_INET;
		servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
		servaddr.sin_port=htons(port);

		
	}
	Serv(const Serv&)=delete;
	Serv & operator=(const Serv&)=delete;
	Serv(Serv &&)=delete;
	Serv & operator=(Serv&&)=delete;
	~Serv()=default;
	void runTCP();
	void runUDP();
	int session(int);
	
private:
	std::string parse(std::string );
private:
	int TCPlistenfd;
	int UDPlistenfd;
	sockaddr_in servaddr;
};


#endif
