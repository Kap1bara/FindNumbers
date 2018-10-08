#include "Serv.hpp"
#include <iostream>
struct globalArgs_t {
	int port=10000;				/* -p option */
} globalArgs;
static  char const *optString = "p:?";
void display_usage();
int main(int argc, char  *argv[])
{
	int opt=getopt(argc,argv,optString);
	while(opt!=-1){
		switch(opt){
			case 'p':
				globalArgs.port=atoi(optarg);
				break;
			case '?':
				display_usage();
				break;
			default:
				break;
		}
		opt = getopt( argc, argv, optString );
	}
	Serv server(globalArgs.port);
	/*std::thread TCPserver(&Serv::runTCP,&server);
	std::thread UDPserver(&Serv::runUDP,&server);
	TCPserver.join();
	UDPserver.join();*/
	server.runTCP();
	
	return 0;
}
void display_usage(){
	std::cout<<"NAME\n\tserv -run server.\n"<<
				"SYNOPSIS\n\tfind [-p value]\n"<<
				"OPTIONS\n\t[-p value] changes port. It is 10000 by default.\n";
	exit(0);
}