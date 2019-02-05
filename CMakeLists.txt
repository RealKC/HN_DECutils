cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(DECdecypher)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(declib)
add_subdirectory(thirdparty/CLI11)
add_subdirectory(DECypher_app)

install(TARGETS DECypher DESTINATION bin)
