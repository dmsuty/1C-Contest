#include "find_similar_files.hpp"
#include "dist.hpp"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include <openssl/sha.h>

// TODO add concurrency
// TODO add 100%-similarity check with sha1sum

namespace fs = std::filesystem;

std::string getSHA1Sum(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);

    SHA_CTX sha1Context;
    SHA1_Init(&sha1Context);
    char buffer[8192];

    while (file.read(buffer, sizeof(buffer))) {
        SHA1_Update(&sha1Context, buffer, file.gcount());
    }

    SHA1_Final(reinterpret_cast<unsigned char*>(buffer), &sha1Context);

    std::ostringstream sha1Stream;
    sha1Stream << std::hex << std::setfill('0');
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        sha1Stream << std::setw(2) << static_cast<unsigned>(buffer[i]);
    }

    return sha1Stream.str();
}

void FindSimilarFiles(const std::string& firstDir, const std::string& secondDir, int border) {
    std::vector<std::string> firstDirFiles, firstDirContent;
    std::vector<std::string> secondDirFiles, secondDirContent;
    for (const auto& file : fs::directory_iterator(firstDir)) {
        firstDirFiles.push_back(file.path().string());
        std::ifstream fin(file);
        if (fin.is_open()) {
            std::stringstream buffer;
            buffer << fin.rdbuf();
            firstDirContent.push_back(buffer.str());
        }
    }

    for (const auto& file : fs::directory_iterator(secondDir)) {
        secondDirFiles.push_back(file.path().string());
        std::ifstream fin(file);
        if (fin.is_open()) {
            std::stringstream buffer;
            buffer << fin.rdbuf();
            secondDirContent.push_back(buffer.str());
        }
    }

    for (size_t i = 0; i < firstDirContent.size(); ++i) {
        for (size_t j = 0; j < secondDirContent.size(); ++j) {
            if (whichPercent(firstDirContent[i].size(), secondDirContent[j].size()) < border) {
                continue;
            }

            if (firstDirContent[i].size() == secondDirContent[j].size()) {
                std::string sum1 = getSHA1Sum(firstDirFiles[i]);
                std::string sum2 = getSHA1Sum(secondDirFiles[j]);
                if (sum1 == sum2) {
                    std::cout << firstDirFiles[i] << " and " << secondDirFiles[i] << "are the same files\n";
                }
            }

            int sim_koef = similarity(firstDirContent[i], secondDirContent[j]);
            if (sim_koef >= border) {
                std::cout << firstDirFiles[i] << " and " << secondDirFiles[i] << "are similar at " << sim_koef << "%\n";
            }   
        }
    }
}