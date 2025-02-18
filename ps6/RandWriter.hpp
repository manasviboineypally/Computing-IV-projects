// Copyright 2024 <Manasvi Boineypally>
#ifndef RANDWRITER_HPP
#define RANDWRITER_HPP

#include <string>
#include <map>
#include <random>

class RandWriter {
 public:
    RandWriter(const std::string& text, size_t k);
    size_t orderK() const;
    int freq(const std::string& kgram) const;
    int freq(const std::string& kgram, char c) const;
    char kRand(const std::string& kgram);
    std::string generate(const std::string& kgram, size_t L);

 private:
    std::string text;
    size_t k;
    std::map<std::string, std::map<char, int>> frequencyMap;
    std::string alphabet;
    std::mt19937 gen;

    void buildFrequencyMap();
};

std::ostream& operator<<(std::ostream& os, const RandWriter& rw);

#endif   // RANDWRITER_HPP

