#ifndef EDISTANCE_HPP
#define EDISTANCE_HPP

#include <string>
#include <vector>

class EDistance {
private:
    std::string x, y;
    std::vector<std::vector<int>> opt;

    int penalty(char a, char b); // Keep this as private if you want
    int min3(int a, int b, int c); // Keep this as private if you want

public:
    EDistance(const std::string& s1, const std::string& s2);
    int optDistance();
    std::string alignment();

    // Make these functions public for testing purposes
    int test_penalty(char a, char b) { return penalty(a, b); }
    int test_min3(int a, int b, int c) { return min3(a, b, c); }
};

#endif