#include "wrappers.hpp"
#include <iostream>
void wBind(int fd, const SA *sa, socklen_t salen){
	if (bind(fd, sa, salen) < 0)
		throw 101;
}
void wListen(int fd, int backlog){
	if (listen(fd, backlog) < 0)
		throw 102;
}
int wAccept(int fd, SA *sa, socklen_t *salenptr){
	int n=0;
	if( (n=accept(fd,sa,salenptr) )<0 ){
		throw 103;
	}
	return n;
}
int wSocket(int family, int type, int protocol)
{
	int	n=0;

	if ( (n = socket(family, type, protocol)) < 0)
		throw 100;
	return n;
}
void wClose(int fd){
	if (close(fd) == -1)
		throw 104;
}
void wConnect(int fd, const SA *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0)
		throw 105;
}
void 	InetPton(int af, const char *src, void *dst){
	int k;
	if( (k=inet_pton(af, src, dst))<=0 ){
		throw 106;
	}
}
void    exceptionHandle(int e){
	switch(e){
		case 100:
			std::cerr<<"Error "<<e<<". Socket creation error.\n ";
			break;
		case 101:
			std::cerr<<"Error "<<e<<". Binding error.\n ";
			break;
		case 102:
			std::cerr<<"Error "<<e<<". Listen error.\n ";
			break;
		case 103:
			std::cerr<<"Error "<<e<<". Accept error\n ";
			break;
		case 104:
			std::cerr<<"Error "<<e<<". Close error\n ";
			break;
		case 105:
			std::cerr<<"Error "<<e<<". Connection error\n ";
			break;
		case 106:
			std::cerr<<"Error "<<e<<". InetPton Error. Check addres\n ";
			break;
	}
}