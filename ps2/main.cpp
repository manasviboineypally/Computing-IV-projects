//  Copyright 2024 Manasvi Boinneypally

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "penta.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0]
                  << " <initial_side_length> <max_depth>" << std::endl;
        return EXIT_FAILURE;
    }

    double initialSize = std::stod(argv[1]);
    int depthLimit = std::stoi(argv[2]);
    sf::RenderWindow window(sf::VideoMode(600, 600), "Pentaflake View");
    FractalShape fractal(initialSize, depthLimit);
    fractal.buildPattern(window.getSize().x / 2.0, window.getSize().y / 2.0);

    bool rotatingClockwise = false;
    bool rotatingCounterclockwise = false;
    double zoomLevel = 1.0;

    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("sound.ogg")) {
        std::cerr << "Error: Could not load audio file." << std::endl;
        return EXIT_FAILURE;
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::L) {
                    rotatingClockwise = !rotatingClockwise;
                }
                if (event.key.code == sf::Keyboard::R) {
                    rotatingCounterclockwise = !rotatingCounterclockwise;
                }
                if (event.key.code == sf::Keyboard::Up) {
                    zoomLevel += 0.1;  // Zoom in
                    fractal.zoom(zoomLevel);
                }
                if (event.key.code == sf::Keyboard::Down) {
                    zoomLevel = std::max(0.1, zoomLevel - 0.1);
                    fractal.zoom(zoomLevel);
                }
            }
        }

        if (rotatingClockwise) {
            fractal.rotate(-1.0);
        }
        if (rotatingCounterclockwise) {
            fractal.rotate(1.0);
        }

        window.clear(sf::Color::Black);
        window.draw(fractal);
        window.display();
    }

    return EXIT_SUCCESS;
}
