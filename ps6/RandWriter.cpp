// Copyright 2024 <Manasvi Boineypally>
#include "RandWriter.hpp"
#include <random>
#include <stdexcept>
#include <algorithm>
#include <string>

RandWriter::RandWriter(const std::string& text, size_t k) : text(text), k(k) {
    if (text.length() < k) {
        throw std::invalid_argument("Text length must be at least k.");
    }
    buildFrequencyMap();
    // Use a fixed seed for deterministic behavior
    gen = std::mt19937(12345);  // Fixed seed
}

size_t RandWriter::orderK() const {
    return k;
}

int RandWriter::freq(const std::string& kgram) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must be equal to k.");
    }
    if (k == 0 && kgram.empty()) {
        return text.length();   // For k=0, return the length of the text
    }
    auto it = frequencyMap.find(kgram);
    int total = 0;
    if (it != frequencyMap.end()) {
        for (const auto& pair : it->second) {
            total += pair.second;
        }
    }
    return total;
}

int RandWriter::freq(const std::string& kgram, char c) const {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must be equal to k.");
    }
    auto it = frequencyMap.find(kgram);
    if (it != frequencyMap.end()) {
        auto charIt = it->second.find(c);
        return charIt != it->second.end() ? charIt->second : 0;
    }
    return 0;
}

char RandWriter::kRand(const std::string& kgram) {
    if (kgram.length() != k) {
        throw std::invalid_argument("kgram length must be equal to k.");
    }
    auto it = frequencyMap.find(kgram);
    if (it == frequencyMap.end()) {
        throw std::invalid_argument("No such kgram found.");
    }

    int totalFreq = 0;
    for (const auto& pair : it->second) {
        totalFreq += pair.second;
    }

    std::uniform_int_distribution<> dis(1, totalFreq);
    int randVal = dis(gen);

    // Using a lambda expression to find the selected character
    auto findChar = [&randVal](const auto& pair) {
        randVal -= pair.second;
        return randVal <= 0;
    };

    auto selectedPair = std::find_if(it->second.begin(), it->second.end(), findChar);
    if (selectedPair != it->second.end()) {
        return selectedPair->first;
    }

    throw std::runtime_error("Random selection failed.");
}

std::string RandWriter::generate(const std::string& kgram, size_t L) {
    if (kgram.length() != k || L < k) {
        throw std::invalid_argument("Invalid arguments for generation.");
    }

    std::string result = kgram;

    while (result.length() < L) {
        char nextChar = kRand(result.substr(result.length() - k));
        result += nextChar;
    }

    return result;
}

void RandWriter::buildFrequencyMap() {
    size_t n = text.length();

    // Build frequency map considering wrap-around
    for (size_t i = 0; i < n; ++i) {
        std::string kgram;

        for (size_t j = 0; j < k; ++j) {
            kgram += text[(i + j) % n];
        }

        char nextChar = text[(i + k) % n];

        frequencyMap[kgram][nextChar]++;

        if (alphabet.find(nextChar) == std::string::npos) {
            alphabet += nextChar;
        }

        if (k == 0 && i == 0) {
            for (char c : text) {
                frequencyMap[""][c]++;
            }

            break;
        }
    }
}
