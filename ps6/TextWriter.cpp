// Copyright 2024 <Manasvi Boineypally>
#include <iostream>
#include <string>
#include <stdexcept>
#include "RandWriter.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <k> <L>" << std::endl;
        return 1;
    }

    size_t k, L;
    try {
        k = std::stoul(argv[1]);
        L = std::stoul(argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Invalid argument: " << e.what() << std::endl;
        return 1;
    }

    std::string input_text;
    std::string line;
    while (std::getline(std::cin, line)) {
        input_text += line;
    }

    if (input_text.length() < k) {
        std::cerr << "Input text length must be at least k." << std::endl;
        return 1;
    }

    if (L < k) {
        std::cerr << "L must be greater than or equal to k." << std::endl;
        return 1;
    }

    try {
        RandWriter model(input_text, k);
        std::string kgram = input_text.substr(0, k);
        std::string generated = model.generate(kgram, L);
        std::cout << generated << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

