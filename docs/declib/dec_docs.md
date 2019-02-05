# dec.hpp documentation

This header provides 3 macro definitions(for version info), 6 free function prototypes, 2 struct declarations and definitions and 1 anonymous struct definition providing version info. All of the previous declarations(minus the macros) are done within the namespace `DecEncryptDecryptKCImpl`, and the namespace `dec` is provided as an alias for the previous namespace.

This header includes the standard library headers `<cstdint>` and `<string>`.

Recommended reading: [hash_docs](hash_docs.md).

## Macros

The following macros are defined within this header for version info: `DECLIB_KC_VERSION_MAJOR`,`DECLIB_KC_VERSION_MINOR`, `DECLIB_KC_VERSION_PATCH`.

## Structs

`DecFile` and `DecHeader` are declared and defined within this header, and `version` is a variable of an annonymous struct type for version info.

### version

It provides version info, its members are `major`, `minor`, and `patch` and they are of type `std::uint8`. It is declared `static constexpr`.

### DecFile

This struct provides a representation of a file encrypted using the DEC algorithm.

Members:
* valid (`bool`) specifies whether the file is valid or not.
* header (`DecHeader`) the header line of a file encrypted using DEC.
* body (`std::string`) the body/contents of the file.

### DecHeader

This struct provides a representation of the header of a file encrypted using the DEC Algorithm.

Members:
* header (`std::string`) most likely a descriptive file name.
* signature (`std::string`) a signature for the file. In Hacknet it is generally an IPv4 address.
* key (`std::string`) the string `ENCODED`.
* extension (`std::string`) the original file extension.

## Functions

### encrypt

Prototype: `std::string encrypt( std::string data, std::string header, std::string signature, std::string extension, std::string password, CsHashType  hashType = CsHashType::Auto
)`

Params:
* data coresponds to `DecFile::body`
* header corresponds to `DecHeader::header`
* signature corresponds to `DecHeader::signature`
* extension corresponds to `DecHeader::extension`
* password the password to be used for DEC encryption.
* hashType the method for hashing(by default this will use the compilation target one)

Returns the DEC encrypted string for the given input.

### encryptString

Prototype: `std::string encryptString(std::string data, int hash)`

Params:
* data a string to be "encrypted"
* hash the hash to be used

Returns a hashed string.

### decrypt

Prototype: `DecFile decrypt( DecFile file, std::string pass, CsHashType hashType = CsHashType::Auto)`

Params:
* file, a DEC encrypted file
* pass, the password for decryption
* hashType, which hash to use, by default it will be the one for the target-compilation system.

Returns a decrypted DecFile representation of the input file.

### decryptHeader

Prototype: `DecHeader decryptHeader( DecHeader head, std::string pass, CsHashType hashType = CsHashType::Auto)`

Params:
* head, the DecHeader part of a file
* pass, the password for decryption
* hashType, which hash to use, by default it will be the one for the target-compilation system

Returns a decrypted DecHeader represenation of the input header.

### decryptString

Prototype: `std::string decryptString(std::string data, int hash)`

Params:
* data, the string to be decrypted
* hash, the hash to be used for decryption

Returns a decrypted string.

### readEncryptedFile

Prototype: `DecFile readEncryptedFile(std::string srcPath)`

Params:
* srcPath, a path pointing to the file.

Returns a DecFile representation of the given file.
