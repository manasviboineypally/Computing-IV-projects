// Copyright 2024 manasvi boineypally

#include "PhotoMagic.hpp"

// Implement the transform function
void PhotoMagic::transform(sf::Image& image, FibLFSR *lfsr) {
    // Ensure FibLFSR is correctly referenced
    unsigned int width = image.getSize().x;
    unsigned int height = image.getSize().y;

    for (unsigned int x = 0; x < width; ++x) {
        for (unsigned int y = 0; y < height; ++y) {
            sf::Color pixel = image.getPixel(x, y);

            // XOR the RGB values with LFSR-generated values
            pixel.r ^= lfsr->generate(8);
            pixel.g ^= lfsr->generate(8);
            pixel.b ^= lfsr->generate(8);

            image.setPixel(x, y, pixel);
        }
    }
}
