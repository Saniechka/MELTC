#include <iostream>
#include <fstream>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <vector>

std::string calculateStringHash(const std::string& input) {
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


int main() {
    std::string filePath = "cos.txt";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return 1;
    }

    const size_t lines_per_chunk = 4; // Число строк в одном чанке
    std::vector<std::string> chunkStrings;
    std::vector<std::string> hashes; // Вектор для хранения хешей

    while (!file.eof()) {
        std::string line;
        for (size_t i = 0; i < lines_per_chunk && std::getline(file, line); ++i) {
            chunkStrings.push_back(line);
        }

        // Проверяем, что у нас достаточно строк для расчета хеша
        if (chunkStrings.size() == lines_per_chunk) {
            // Обрабатываем строки в текущем чанке и сохраняем хеш в массив
            std::string hash = calculateStringHash(chunkStrings[0] + chunkStrings[1] + chunkStrings[2] + chunkStrings[3]);
            hashes.push_back(hash);
        }

        // Очищаем массив перед следующим чанком
        chunkStrings.clear();
    }

    file.close();

    // Выводим хеши
    for (const auto& hash : hashes) {
        std::cout << "SHA-256 Hash: " << hash << std::endl;
    }

    return 0;
}
