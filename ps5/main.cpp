#include "EDistance.hpp"
#include <iostream>
#include <SFML/System.hpp>

int main() {
    std::string s1, s2;
    std::getline(std::cin, s1);
    std::getline(std::cin, s2);

    sf::Clock clock;

    EDistance ed(s1, s2);
    int distance = ed.optDistance();
    std::string align = ed.alignment();

    sf::Time t = clock.getElapsedTime();

    std::cout << "Edit distance = " << distance << std::endl;
    std::cout << align;
    std::cout << "Execution time is " << t.asSeconds() << " seconds" << std::endl;

    return 0;
}