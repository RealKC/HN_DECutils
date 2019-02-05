#include <string>
#include <fstream>
#include <sstream>

#include "dec.hpp"

namespace DecEncryptDecryptKCImpl
{

std::string encrypt(
    std::string data,
    std::string header,
    std::string signature,
    std::string extension,
    std::string password,
    CsHashType  hashType
)
{
    CsHashType hashToUse = (hashType == CsHashType::Auto) ? currentPlatform : hashType;
    int emptyHash = static_cast<short>(platformAgnosticHash("", hashToUse)),
        hash = static_cast<short>(platformAgnosticHash(password, hashToUse));

    std::string ret
        /* Header Part */
        = "#DEC_ENC::"
        + encryptString(header, emptyHash) + "::"
        + encryptString(signature, emptyHash) + "::"
        + encryptString("ENCODED", hash) + "::"
        + encryptString(extension, emptyHash) + "\n"
        /*Body Part */
        + encryptString(data, hash)
        + '\n';
        ;

    return ret;
}

std::string encryptString(
    std::string data,
    int         hash
)
{
    std::stringstream ret;

    for (auto i = data.begin(), end = data.end(); i != end; ++i) {
        if (i != data.begin()) {
            ret << " ";
        }
        ret << static_cast<int>(*i) * 0x71E + 0x7FFF + hash;
    }

    return ret.str();
}

DecFile decrypt(
    DecFile     file,
    std::string pass,
    CsHashType  hashType
)
{
    CsHashType hashToUse = (hashType == CsHashType::Auto ? currentPlatform : hashType);
    DecFile out;

    out.header = decryptHeader(file.header, pass, hashToUse);

    if (out.header.key == "ENCODED") {
        out.valid = true;
        out.body = decryptString(file.body, platformAgnosticHash(pass, hashToUse));
    } else { out.valid = false; }

    return out;
}

DecHeader decryptHeader(
    DecHeader   head,
    std::string pass,
    CsHashType  hashType
)
{
    DecHeader out;
    CsHashType hashToUse = (hashType == CsHashType::Auto ? currentPlatform : hashType);

    int emptyHash = static_cast<short>(platformAgnosticHash("", hashToUse));

    out.header = decryptString(head.header, emptyHash);
    out.signature = decryptString(head.signature, emptyHash);
    out.key = decryptString(head.key, platformAgnosticHash(pass, hashToUse));
    out.extension = decryptString(head.extension, emptyHash);

    return out;
}

std::string decryptString(std::string data, int hash)
{
    if (data.empty()) {
        return "";
    }

    std::stringstream toDecrypt(data);
    std::string out, tmp;

    while (toDecrypt >> tmp) {
        int dehashed = std::stoi(tmp);
        dehashed -= (0x7FFF + hash);
        dehashed /= 0x71E;

        out += static_cast<char>(dehashed);
    }

    return out;
}

DecFile readEncryptedFile(std::string srcPath)
{
    std::ifstream src {srcPath};

    DecFile out;

    bool wellReadLine = false;
    std::string tmp;

    //Process Header (line 1)
    if (std::getline(src, tmp)) {
        wellReadLine = true;
    } else {
        out.valid = false;
        return out;
    }

    int pos = 0, k = 0;
    while (wellReadLine && pos != std::string::npos) {
        if (tmp.substr(pos, tmp.find_first_of("::", pos)) == "#DEC_ENC") {
            pos += tmp.find_first_of("::", pos) + 1;
        } else {
            k++; // this approach introduces least indentation levels
            switch(k) {
                case 1:
                    out.header.header = tmp.substr(pos, tmp.find_first_of("::", pos));
                    break;
                case 2:
                    out.header.signature = tmp.substr(pos, tmp.find_first_of("::", pos));
                    break;
                case 3:
                    out.header.key = tmp.substr(pos, tmp.find_first_of("::", pos));
                    break;
                case 4:
                    out.header.extension = tmp.substr(pos, tmp.find_first_of("::", pos));
                    break;
                default:
                    break;
            }
            pos += tmp.find_first_of("::", pos) + 1;
        }
    }

    if (std::getline(src, tmp)) {
        out.body = tmp;
    } else {
        out.body = "";
    }

    out.valid = true;
    return out;
}

} // DecEncryptDecryptKCImpl
