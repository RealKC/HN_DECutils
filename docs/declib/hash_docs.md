# Hash.hpp documentation

This header files provides one C++11 scoped enum, a compile-time known constant  and 3 free function prototypes implemented in hash.cpp. All of the previous declarations are within the namespace `DecEncryptDecryptKCImpl`.

This header includes the standard library header `<string>` for `std::string`.

## CsHashType

This is a C++11 scoped enum. It has the following 3 values:
* `Net`, representing the .NET C# platform
* `Mono`, representing the Mono C# platform
* `Auto`, which is generally passed to functions to tell them to do their own thing.

A compile-time known constant `currentPlatform` of type CsHashType is provided which will be set to either `Net` or `Mono` as appropriate is provided.

## Functions

The following free functions are provided:

### platformAgnosticHash

Prototype: `int platformAgnosticHash(const std::string&, CsHashType);`

Params:
* A string which should become the hash.
* A variable indicating which platforms hash should be used.

This function will call the appropriate hashing function for the C# platform provided.

### netHash

Prototype: `int netHash(const std::string&)`

Params:
* A string which will become the hash.

This functions implements the hashing algorithm used by .NET, as that is what Hacknet uses on Windows

### monoHash

Prototype: `int monoHash(const std::string&)`

Params:
* A string which will become the hash.

This functions implements the hashing algorithm implemented by Mono, as that is what Hacknet uses when ran on Linux distribution, not through Wine, and on MacOS.
