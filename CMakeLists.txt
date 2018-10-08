cmake_minimum_required(VERSION 3.1)	 
										

project(Client)			
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/../)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
add_executable(cli cli/client.cpp cli/cli.cpp wrappers/wrappers.cpp)
find_library(PTHREAD_LIB pthread)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pthread")
add_executable(serv serv/serv.cpp serv/server.cpp wrappers/wrappers.cpp)
target_link_libraries(serv gmpxx gmp)