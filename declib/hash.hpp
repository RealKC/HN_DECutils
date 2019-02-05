#ifndef DECLIB_KC_HEADER_HASHING
#define DECLIB_KC_HEADER_HASHING

#include <string>

namespace DecEncryptDecryptKCImpl
{

enum class CsHashType {
    Mono, Net, Auto
};

int platformAgnosticHash(const std::string&, CsHashType);

int netHash(const std::string&);
int monoHash(const std::string&);

} // DecEncryptDecryptKCImpl

#if defined(_WIN32)
#    define DEC_KC_PLATFORM DecEncryptDecryptKCImpl::CsHashType::Net
#else
#    define DEC_KC_PLATFORM DecEncryptDecryptKCImpl::CsHashType::Mono
#endif // defined(_WIN32)

namespace DecEncryptDecryptKCImpl
{
static constexpr CsHashType currentPlatform = DEC_KC_PLATFORM;
} // DecEncryptDecryptKCImpl

#undef DEC_KC_PLATFORM

#endif // DECLIB_KC_HEADER_HASHING
