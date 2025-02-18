// CopyRight 2024 Manasvi Boineypally

#include <fstream>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>


#include <SFML/Graphics.hpp>
#include "Sokoban.hpp"

std::string formatTime(int seconds) {
    int minutes = seconds / 60;
    seconds %= 60;
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << minutes << ":"
       << std::setfill('0') << std::setw(2) << seconds;
    return ss.str();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <level_file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file) {
        std::cerr << "Unable to open level file\n";
        return 1;
    }

    SB::Sokoban sokoban(0, 0);
    file >> sokoban;

    sf::RenderWindow window(sf::VideoMode(sokoban.width() * 64,
    sokoban.height() * 64), "Sokoban");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Unable to load font\n";
        return 1;
    }

    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::Red);
    timeText.setPosition(280, 10);

    time_t startTime = time(nullptr);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        time_t currentTime = time(nullptr);
        int elapsedSeconds = difftime(currentTime, startTime);
        timeText.setString(formatTime(elapsedSeconds));

        window.clear();
        window.draw(sokoban);
        window.draw(timeText);
        window.display();
    }

    return 0;
}
