#include <string>

#include "hash.hpp"

namespace DecEncryptDecryptKCImpl
{

int platformAgnosticHash(const std::string& data, CsHashType hashType)
{
    switch (hashType)
    {
        case CsHashType::Net :
            return netHash(data);
        case CsHashType::Mono :
            return monoHash(data);
        default :
            return monoHash(data);
    }
}

int netHash(const std::string& data)
{
    //okay, listen, I've no idea what these magic constants do, a friend of mine
    //gave me the original code in the .NET impl and I just ported it over to C++

    int num = 352654597, num2 = num;
    int somePos = 0, i;
    for (i = data.size(); i > 2; i-=4) {
        num = (((num << 5) + num + (num >> 27)) ^ data[somePos]);
        num2 = (((num2 << 5) + num2 + (num2 >> 27)) ^ data[somePos+1]);
        somePos += 2;
    }

    if (i > 0) {
        num = (((num << 5) + num + (num >> 27)) ^ data[somePos]);
    }

    return num + num2 * 1566083941;
}

int monoHash(const std::string& data)
{
    int n = 0;
    for (auto i = 0ull; i < data.size(); i++) {
        n = (n << 5) - n + static_cast<int>(data[i]); //why tf is this so much simpler?
    }

    return n;
}

} // DecEncryptDecryptKCImpl
