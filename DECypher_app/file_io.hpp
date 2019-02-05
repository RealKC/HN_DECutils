#ifndef DECYPHER_FILE_IO_INCLUDED
#define DECYPHER_FILE_IO_INCLUDED

#include <fstream>
#include <string>
#include <string_view>

namespace DECypher
{

/**
 * @brief Reads the contents of an entire file, and then places them into a string
 *
 * @param pathToFile
 * @return std::string
 */
std::string readWholeFile(std::string_view pathToFile);

} // DECypher

#endif //DECYPHER_FILE_IO_INCLUDED
