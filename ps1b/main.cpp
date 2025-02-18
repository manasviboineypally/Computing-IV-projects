// Copyright 2024 manasvi boineypally

#include <iostream>
#include <bitset>
#include <string>
#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"
#include "PhotoMagic.hpp"

std::string seedToBinary(const std::string &seed) {
    std::string binarySeed;

    for (char c : seed) {
        std::bitset<8> bits(c);
        binarySeed += bits.to_string();
    }

    if (binarySeed.length() > 16) {
        binarySeed = binarySeed.substr(0, 16);
    } else if (binarySeed.length() < 16) {
        binarySeed = std::string(16 - binarySeed.length(), '0') + binarySeed;
    }

    return binarySeed;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0]
        << " <input image> <output image> <LFSR seed>\n";
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    std::string lfsrSeed = argv[3];

    try {
        std::string binarySeed = seedToBinary(lfsrSeed);

        PhotoMagic::FibLFSR lfsr(binarySeed);

        sf::Image originalImage;
        if (!originalImage.loadFromFile(inputFile)) {
            std::cerr << "Error loading image: " << inputFile << "\n";
            return 1;
        }

        sf::Image transformedImage = originalImage;

        PhotoMagic::transform(transformedImage, &lfsr);

        if (!transformedImage.saveToFile(outputFile)) {
            std::cerr << "Error saving image: " << outputFile << "\n";
            return 1;
        }

        sf::RenderWindow window1(sf::VideoMode(originalImage.getSize().x,
         originalImage.getSize().y), "Original Image");
        sf::RenderWindow window2(sf::VideoMode(transformedImage.getSize().x,
         transformedImage.getSize().y), "Transformed Image");

        sf::Texture texture1, texture2;
        texture1.loadFromImage(originalImage);
        texture2.loadFromImage(transformedImage);

        sf::Sprite sprite1(texture1);
        sf::Sprite sprite2(texture2);

        while (window1.isOpen() && window2.isOpen()) {
            sf::Event event;
            while (window1.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window1.close();
                }
            }

            while (window2.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window2.close();
                }
            }

            window1.clear();
            window1.draw(sprite1);
            window1.display();

            window2.clear();
            window2.draw(sprite2);
            window2.display();
        }
    } catch (const std::invalid_argument &e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
