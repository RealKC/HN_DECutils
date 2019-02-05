#ifndef DECLIB_KC_HEADER_DEC_ENCRYPTION_IN_QUOTES
#define DECLIB_KC_HEADER_DEC_ENCRYPTION_IN_QUOTES

#include <cstdint>
#include <string>

#include "hash.hpp"

#define DECLIB_KC_VERSION_MAJOR 0
#define DECLIB_KC_VERSION_MINOR 1
#define DECLIB_KC_VERSION_PATCH 0

namespace DecEncryptDecryptKCImpl
{
static constexpr struct {
    std::uint8_t major, minor,patch;
} version {
    DECLIB_KC_VERSION_MAJOR,
    DECLIB_KC_VERSION_MINOR,
    DECLIB_KC_VERSION_PATCH
};
} // DecEncryptDecryptKCImpl
namespace dec = DecEncryptDecryptKCImpl;

namespace DecEncryptDecryptKCImpl
{

struct DecFile;
struct DecHeader;

std::string encrypt(
    std::string data,
    std::string header,
    std::string signature,
    std::string extension,
    std::string password,
    CsHashType  hashType = CsHashType::Auto
);

std::string encryptString(
    std::string data,
    int         hash
);

DecFile decrypt(
    DecFile     file,
    std::string pass,
    CsHashType  hashType = CsHashType::Auto
);
DecHeader decryptHeader(
    DecHeader   head,
    std::string pass,
    CsHashType  hashType = CsHashType::Auto
);
std::string decryptString(std::string data, int hash);
DecFile readEncryptedFile(std::string srcPath);

struct DecHeader {
    std::string header,
        signature,
        key, /* = the string `ENCODED` passed through `encrypyString`
             with the hash for your password*/
        extension;
};

struct DecFile {
    bool valid;
    DecHeader header;
    std::string body;
};

} // DecEncryptDecryptKCImpl

#endif // DECLIB_KC_HEADER_DEC_ENCRYPTION_IN_QUOTES
