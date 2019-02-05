project(declib)

set(declib_SOURCES dec.cpp hash.cpp)
set(declib_HEADERS dec.hpp hash.hpp)

add_library(declib STATIC ${declib_SOURCES} ${declib_HEADERS})

target_include_directories(declib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
