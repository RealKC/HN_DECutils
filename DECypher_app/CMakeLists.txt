project(DECypher_app)

set(DECypher_SOURCES DECypher.cpp file_io.hpp file_io.cpp)

add_executable(DECypher ${DECypher_SOURCES})

target_link_libraries(DECypher PRIVATE declib)
target_link_libraries(DECypher PRIVATE CLI11::CLI11)
