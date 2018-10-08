#include "Serv.hpp"
#include <gmpxx.h>
void Serv::runTCP(){
	wBind(TCPlistenfd,reinterpret_cast<SA*>(&servaddr),sizeof(servaddr));
	wListen(TCPlistenfd,10000);
	for(;;){
		int connfd=wAccept(TCPlistenfd,reinterpret_cast<SA*>(NULL),NULL);
			//std::thread Session(&Serv::session,this,connfd);	
			//Session.detach();
			session(connfd);
	}
	
}
void Serv::runUDP(){
	wBind(UDPlistenfd,reinterpret_cast<SA*>(&servaddr),sizeof(servaddr));	
	for(;;){
		char recvline[1024];
		socklen_t	len=sizeof(servaddr);
		recvfrom(UDPlistenfd, recvline, 1024, 0,
			reinterpret_cast<SA *> (&servaddr), &len);
		std::string result=this->parse(recvline);
		sendto(UDPlistenfd, result.c_str(), result.size()+1, 0, 
			reinterpret_cast<SA *> (&servaddr), len);
	}
}
int Serv::session( int connfd){
	
	
	char recvline[1024];
	std::string result="";
	if ( (read(connfd, recvline, 1024)) > 0) {
		result=this->parse(recvline);
	}
	write(connfd,result.c_str(),result.size()+1);
	try{
		wClose(connfd);
	}	
	catch(int){
		std::cerr<<"invalid closing";
	}	
	return connfd;
	
}
#include <algorithm> //std::copy, std::find_first(_not)_of, std::for_each
#include <vector>
#include <sstream>  //converting vector to string and adding to sting a sum
#include <iterator> //ostream_iterator
std::string Serv::parse(std::string str){
	std::vector<mpz_class> numbers;
	numbers.reserve(512);
	auto fb=str.find_first_of("1234567890");
	while (fb!=std::string::npos)
	{
	   	auto fe=str.find_first_not_of("1234567890",fb);
	   	numbers.push_back(mpz_class(str.substr(fb,fe-fb)));
	   	fb=str.find_first_of("1234567890",fe);    
	}
	numbers.shrink_to_fit();

	std::sort(numbers.begin(), numbers.end());

	std::ostringstream buff;
	std::copy(numbers.begin(),
			 numbers.end(),
			 std::ostream_iterator<mpz_class>(buff," "));

	mpz_class sum=0;
	std::for_each(numbers.begin(), numbers.end(),
					[&sum](mpz_class x){sum+=x;});
	buff<<'\n'<<sum<<'\n';
	return buff.str();
}