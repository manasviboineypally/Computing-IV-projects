// Copyright  2024 manasvi boineypally
#ifndef FIBLFSR_HPP
#define FIBLFSR_HPP

#include <string>


namespace PhotoMagic {
class FibLFSR {
 public:
     // Constructor: initializes the register with a seed string
FibLFSR(std::string seed);

        // Performs one step of the LFSR and returns the output bit
        int step();

        // Generates a number based on 'k' steps
        int generate(int k);
        friend std::ostream& operator<<(std::ostream& out, const FibLFSR& lfsr);
    std::string reg;
    int tap;
};
}  // namespace PhotoMagic

#endif
