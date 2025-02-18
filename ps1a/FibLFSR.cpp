// Copyright [2024] <manasvi boineypally>
#include <iostream>
#include "FibLFSR.hpp"

namespace PhotoMagic {

    // Constructor for FibLFSR: Initializes with the seed
    FibLFSR::FibLFSR(std::string seed) : reg(seed) {
        if (seed.length() != 16) {
            throw std::invalid_argument("Seed must be 16 bits long");
        }
        tap = 0;
    }

    // Perform one step in the LFSR and return the new bit
    int FibLFSR::step() {
        int new_bit = reg[0] ^ reg[2] ^ reg[3] ^ reg[5];
        reg = reg.substr(1) + std::to_string(new_bit);
        return new_bit;
    }

    // Generate a sequence of 'k' steps and return the result as an integer
    int FibLFSR::generate(int k) {
        int result = 0;
        for (int i = 0; i < k; ++i) {
            result = (result << 1) | step();   // Shift result left and OR with new bit
        }
        return result;
    }

    // Overload output stream operator for printing the LFSR
    std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr) {
        out << lfsr.reg;
        return out;
    }

}  //  namespace PhotoMagic
