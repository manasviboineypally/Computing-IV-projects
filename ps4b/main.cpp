// Copyright 2024 Manasvi Boineypally
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Sokoban.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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

    SB::Sokoban sokoban(argv[1]);
    sf::RenderWindow window(sf::VideoMode(sokoban.pixelWidth(),
                            sokoban.pixelHeight()), "Sokoban");

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Unable to load font\n";
        return 1;
    }

    sf::Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(24);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition(10, 10);

    sf::Text moveCountText;
    moveCountText.setFont(font);
    moveCountText.setCharacterSize(24);
    moveCountText.setFillColor(sf::Color::White);
    moveCountText.setPosition(10, 40);  // Position below time text

    sf::Text victoryText;
    victoryText.setFont(font);
    victoryText.setCharacterSize(50);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setString("You Win!");
    victoryText.setPosition(sokoban.pixelWidth() / 2 -
                            victoryText.getGlobalBounds().width / 2,
                            sokoban.pixelHeight() / 2 -
                            victoryText.getGlobalBounds().height / 2);

    sf::SoundBuffer victoryBuffer;
    if (!victoryBuffer.loadFromFile("victory.wav")) {
        std::cerr << "Unable to load victory sound\n";
        return 1;
    }

    sf::Sound victorySound(victoryBuffer);

    sf::Text instructionsText;
    instructionsText.setFont(font);
    instructionsText.setCharacterSize(16);
    instructionsText.setFillColor(sf::Color::White);
    instructionsText.setString("Arrow keys: Move | R: Reset | Z: Undo | Y: Redo");
    instructionsText.setPosition(10, sokoban.pixelHeight() - 30);

    time_t startTime = time(nullptr);
    bool gameWon = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Up:
                        if (!gameWon) sokoban.movePlayer(SB::Direction::Up);
                        break;
                    case sf::Keyboard::Down:
                        if (!gameWon) sokoban.movePlayer(SB::Direction::Down);
                        break;
                    case sf::Keyboard::Left:
                        if (!gameWon) sokoban.movePlayer(SB::Direction::Left);
                        break;
                    case sf::Keyboard::Right:
                        if (!gameWon) sokoban.movePlayer(SB::Direction::Right);
                        break;
                    case sf::Keyboard::R:
                        sokoban.reset();
                        startTime = time(nullptr);
                        gameWon = false;
                        break;
                    case sf::Keyboard::Z:
                        if (!gameWon) {
                            sokoban.undo();
                            gameWon = sokoban.isWon();
                        }
                        break;
                    case sf::Keyboard::Y:
                        if (!gameWon) {
                            sokoban.redo();
                            gameWon = sokoban.isWon();
                        }
                        break;
                    default:
                        break;
                }
            }
        }

        if (!gameWon && sokoban.isWon()) {
            gameWon = true;
            victorySound.play();
        }

        time_t currentTime = time(nullptr);
        int elapsedSeconds = difftime(currentTime, startTime);

        timeText.setString("Time: " + formatTime(elapsedSeconds));
        moveCountText.setString("Moves: " + std::to_string(sokoban.getMoveCount()));

        window.clear(sf::Color(50, 50, 50));  // Dark gray background
        window.draw(sokoban);
        window.draw(timeText);
        window.draw(moveCountText);  // Draw move count text
        window.draw(instructionsText);

        if (gameWon) {
            window.draw(victoryText);
        }

        window.display();
    }

    return 0;
}
