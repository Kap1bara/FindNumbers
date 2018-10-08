#include "cli.hpp"

struct globalArgs_t {
	int port=10000;				/* -p option */
	int udp=0;				/* -u option */
	int tcp=1;				/* -t option*/
	const char* addr=NULL;				/*server's ip-addres*/
} globalArgs;
static  char const *optString = "p:ut?";
void display_usage( void );
int main(int argc, char  *argv[])
{
	if(argc<2){
		display_usage();
		exit(0);
	}
	int opt=getopt(argc,argv,optString);
	while(opt!=-1){
		switch(opt){
			case 'p':
				globalArgs.port=atoi(optarg);
				break;
			case 'u':
				if(globalArgs.udp==-1){
					std::cerr<<"Unable to use TCP and UDP simultaneously\n";
					return -1;
				}
				globalArgs.udp=1;
				globalArgs.tcp=-1;
				break;
			case 't':
				if(globalArgs.tcp==-1){
					std::cerr<<"Unable to use TCP and UDP simultaneously\n";
					return -1;
				}
				globalArgs.tcp=1;
				globalArgs.udp=-1;
				break;
			case '?':
				display_usage();
				break;
			default:
				break;
		}
		opt = getopt( argc, argv, optString );
	}

	globalArgs.addr = *(argv + optind);
	sockaddr_in servaddr;

	
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(globalArgs.port);
	

	try{
		InetPton(AF_INET, globalArgs.addr, &servaddr.sin_addr);	

		Cli client(wSocket(AF_INET,(globalArgs.tcp>0)?SOCK_STREAM:SOCK_DGRAM,0),servaddr);
	 	globalArgs.tcp>0?client.runTCP():client.runUDP();
	}
	catch(int e){
		exceptionHandle(e);
	}

	return 0;
}
void display_usage( void ){
	std::cout<<"NAME\n\tcli -run client in two different modes UDP and TCP.\n"<<
				"SYNOPSIS\n\tfind [-p value] [-u] [-t] addres\n"<<
				"OPTIONS\n\t[-p value] changes port. It is 10000 by default.\n\t"<<
				"-t/-u enable TCP/UDP mode. Only one option to choose\n";
	exit(0);
}