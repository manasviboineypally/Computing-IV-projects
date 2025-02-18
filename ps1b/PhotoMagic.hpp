// Copyright 2024 manasvi boineypally

#ifndef PHOTOMAGIC_HPP
#define PHOTOMAGIC_HPP

#include <SFML/Graphics.hpp>
#include "FibLFSR.hpp"  // Include the LFSR header

namespace PhotoMagic {
    void transform(sf::Image& image, FibLFSR *lfsr);  // Correct declaration
}

#endif
