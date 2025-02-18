#include "EDistance.hpp"
#include <algorithm>

EDistance::EDistance(const std::string& s1, const std::string& s2) : x(s1), y(s2) {
    opt.resize(x.length() + 1, std::vector<int>(y.length() + 1, 0));
}

int EDistance::penalty(char a, char b) {
    return (a == b) ? 0 : 1; // Keep substitution penalty as is
}

int EDistance::min3(int a, int b, int c) {
    return std::min({a, b, c});
}

int EDistance::optDistance() {
    std::string::size_type M = x.length(), N = y.length();

    // Initialize the last row and column with penalties for deletions and insertions
    for (std::string::size_type i = 0; i <= M; i++) opt[i][N] = M - i; // Penalty for deletion
    for (std::string::size_type j = 0; j <= N; j++) opt[M][j] = N - j; // Penalty for insertion

    // Fill the matrix
    for (int i = M - 1; i >= 0; i--) {
        for (int j = N - 1; j >= 0; j--) {
            opt[i][j] = min3(
                opt[i + 1][j + 1] + penalty(x[i], y[j]), // Substitution
                opt[i + 1][j] + 1, // Insertion (penalty of 1)
                opt[i][j + 1] + 1  // Deletion (penalty of 1)
            );
        }
    }

    return opt[0][0];
}

std::string EDistance::alignment() {
    std::string result;
    std::string::size_type i = 0, j = 0;

    while (i < x.length() && j < y.length()) {
        if (opt[i][j] == opt[i + 1][j + 1] + penalty(x[i], y[j])) {
            result += x[i] + std::string(" ") + y[j] + std::string(" ") +
                      std::to_string(penalty(x[i], y[j])) + "\n";
            i++; j++;
        } else if (opt[i][j] == opt[i + 1][j] + 1) { // Insertion penalty of 1
            result += x[i] + std::string(" - 1\n");
            i++;
        } else { // Deletion penalty of 1
            result += "- " + std::string(1, y[j]) + " 1\n";
            j++;
        }
    }

    while (i < x.length()) {
        result += x[i] + std::string(" - 1\n");
        i++;
    }

    while (j < y.length()) {
        result += "- " + std::string(1, y[j]) + " 1\n";
        j++;
    }

    return result;
}