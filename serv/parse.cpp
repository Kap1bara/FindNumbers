#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>

std::string parse(std::string  str){
	std::vector<int> numbers;
	//std::remove(str.begin(), str.end(), ' ');
	std::cout<<"STRING: "<<str<<'\n';
	numbers.reserve(1024);
	auto fb=str.find_first_of("1234567890");
	auto fe=fb;

	while (fb!=std::string::npos && fe!=std::string::npos)
	{
	   	auto fe=str.find_first_not_of("1234567890",fb);
	   	numbers.push_back(stoi(str.substr(fb,fe-fb)));
	   	fb=str.find_first_of("1234567890",fe);  
	   
	}
	std::ostringstream buff;
	numbers.shrink_to_fit();
	std::copy(numbers.begin(),
			 numbers.end(),
			 std::ostream_iterator<int>(buff," "));
	return buff.str();
}
int main(int argc, char const *argv[])
{
	std::string str;
	getline(std::cin,str);
	std::cout<<parse(str);
	return 0;
}