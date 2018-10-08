#ifndef  _WRAPPERS_
#define _WRAPPERS_ 

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
using SA=sockaddr;
void 	wBind(int, const SA *, socklen_t);
void 	wListen(int, int);
int		wAccept(int, SA *, socklen_t *);
void	wClose(int);
int 	wSocket(int,int,int);
void 	wConnect(int , const SA*, socklen_t);
void 	InetPton(int, const char*,void*);
void    exceptionHandle(int);

#endif
