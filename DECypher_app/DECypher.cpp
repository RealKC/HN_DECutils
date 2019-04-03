#include <iostream>
#include <fstream>

#include <CLI/CLI.hpp>
#include <dec.hpp>

#include "file_io.hpp"

int main(int argc, char* argv[])
{
    CLI::App app{"A CLI application that allows one to easily encrypt or decrypt "
        "files with the DEC \"encryption\" featured in the game Hacknet.", "DECypher"};
    app.allow_windows_style_options();

    std::string inputFile, outputFile,
         signature = "", password="", header = "";

    auto encode = app.add_flag("-e,--encode,--encrypt", "Tells the program to \"encrypt\" the input file.")
        ->ignore_case();
    auto decode = app.add_flag("-d,--decode,--decrypt","Tells the program to \"decrypt\" the input file")
        ->ignore_case()->excludes(encode);
    auto verboseDecoding = app.add_flag("-r,--RAMviewer",
        "Whether to include the details shown in the RAM viewer in Hacknet or not.")
        ->needs(decode)->ignore_case();

    app.add_option("-p,--pass,--password", password, "The password to be used for \"encryption\" or \"decryption\".");

    app.add_option("-i,--input", inputFile, "The path to the file from which to read.")->required();
    app.add_option("-o,--output", outputFile, "The path to the file to which to write.")->required();
    app.add_option("-a,--header", header, "This is most likely supposed to be a descriptive file name, probably.");
    app.add_option("-s,--signature", signature, "The signature for your file.(In hacknet generally an IPv4 address).");



    CLI11_PARSE(app, argc, argv);

    if (*encode) {
        std::string data = DECypher::readWholeFile(inputFile),
            extension = inputFile.substr(inputFile.find_last_of('.'));
        std::ofstream outfile {outputFile};
        outfile << dec::encrypt(data, header, signature, extension, password);
    } else if (*decode) {
        dec::DecFile decryptedFile = dec::decrypt(dec::readEncryptedFile(inputFile), password);
        if (decryptedFile.valid) {
            std::ofstream outfile {outputFile, std::ios::out};
            if (*verboseDecoding) {
                outfile << "HEADER: " << decryptedFile.header.header << "\n"
                    << "SIGNATURE: " << decryptedFile.header.signature << "\n"
                    << "EXTENSIONL: " << decryptedFile.header.extension << "\n"
                    << "BODY: ";
            }
            outfile << decryptedFile.body;
        } else {
            std::cout << "Your input file was not valid, or the password was wrong. No bytes were written to disk.\n";
        }
    } else {
        std::cout << "Either -e/--encode/--encrypt or -d/--decode/--decrypt are required."
            << "Please include one of them.";
    }

    return 0;
}
