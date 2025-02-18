// CopyRight [2024] <manasvi boineypally>
#include <iostream>
#include "FibLFSR.hpp"
int main() {
FibLFSR lfsr;
lfsr.initialize();
std::cout << "Running PhotoMagic..." << std::endl;
for (int i = 0; i < 10; ++i) {
std::cout << "Generated value: " << lfsr.next() << std::endl;
}
return 0;
}
