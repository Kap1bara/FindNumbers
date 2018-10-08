#include "cli.hpp"

void Cli::runTCP(){
	std::cout<<"Client is running in TCP mode\n";
	wConnect(sockfd, reinterpret_cast<SA *> (&servaddr), sizeof(servaddr));
	std::string sendline;
	getline(std::cin,sendline);
	if(sendline.size()>MAXLINE_SIZE){
		sendline.resize(MAXLINE_SIZE);
	}
	char recvline[MAXLINE_SIZE*2+1];
	write(sockfd,sendline.c_str(),sendline.size()+1);
	if ( (read(sockfd, recvline, MAXLINE_SIZE*2+1)) > 0) {
		std::cout<<recvline<<'\n';
	}
}
void Cli::runUDP(){
	std::cout<<"Client is running in UDP mode\n";
	char recvline[MAXLINE_SIZE*2+1];
	std::string sendline;
	getline(std::cin,sendline);
	sendto(sockfd,sendline.c_str(),sendline.size()+1,0,
		reinterpret_cast<SA *> (&servaddr),sizeof(servaddr));
	recvfrom(sockfd,recvline,MAXLINE_SIZE*2+1,0,NULL,NULL);
	std::cout<<recvline<<'\n';
}