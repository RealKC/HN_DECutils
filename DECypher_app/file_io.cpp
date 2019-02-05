#include <numeric>
#include <string>

#include "file_io.hpp"

namespace DECypher
{

// This function was created using a bunch of stackoverflow posts
// Please help improve it
// Some of the SO posts I used are
// https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c
// https://stackoverflow.com/questions/10712117/how-to-count-the-characters-in-a-text-file
std::string readWholeFile(std::string_view pathToFile)
{
    std::string ret;

    std::ifstream file(std::string(pathToFile), std::ios::in | std::ios::binary | std::ios::ate);
    // opens file directly at the end

    if (file.is_open()) {
        ret.reserve(static_cast<std::size_t>(file.gcount()));
        file.seekg(0, std::ios::beg);
        file.read(ret.data(), ret.capacity()); // this will work as of C++17
        file.close();
        return ret;
    } else {
        //TODO: throw an exception when I stop being lazy
    }
}


} // DECypher
