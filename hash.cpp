#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <iomanip>
#include <chrono>

std::string calculateStringHash(const std::string& input) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    // stringst o bytes
    SHA256_Update(&sha256, input.c_str(), input.length());

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }

    return ss.str();
}

std::string readFileToString(const std::string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}


int main() {

    std::string filePath = "cos.txt";
    std::string fileContent = readFileToString(filePath);

    std::string filePath1 = "sin.txt"; 
    std::string fileContent1 = readFileToString(filePath1);
   

    std::string text1 = fileContent;
    std::string text2 = fileContent1;


    auto start_time = std::chrono::high_resolution_clock::now();
    std::string hash1 = calculateStringHash(text1);
    std::string hash2 = calculateStringHash(text2);
    auto end_time = std::chrono::high_resolution_clock::now();

    // Рассчитываем продолжительность выполнения
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Выводим результат
    std::cout << "Время выполнения функции: " << duration.count() << " микросекунд." << std::endl;


    std::cout << "SHA-256 Hash of text1: " << hash1 << std::endl;
    std::cout << "SHA-256 Hash of text2: " << hash2 << std::endl;


    return 0;
}
