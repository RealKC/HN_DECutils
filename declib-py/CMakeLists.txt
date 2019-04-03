project(declib-py)

add_subdirectory(${CMAKE_SOURCE_DIR}/thirdparty/pybind11)
add_subdirectory(${CMAKE_SOURCE_DIR}/declib)

pybind11_add_module(declib-py MODULE EXCLUDE_FROM_ALL THIN_LTO dec.cpp hash.cpp)
