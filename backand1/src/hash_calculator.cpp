#include "hash_calculator.h"
#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>

std::string HashCalculator::calculateStringHash(const std::string& input) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    SHA256_Update(&sha256, input.c_str(), input.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

// ta metoda jest potrzebna dla porownywania plikow w calosci
std::string HashCalculator::readFileToString(const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}
