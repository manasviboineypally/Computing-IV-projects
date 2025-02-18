// CopyRight 2024 Manasvi Boinepally

#include <iostream>
#include <fstream>
#include "Universe.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "N-Body Simulation");

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("starfield.jpg")) {
        std::cerr << "Failed to load background image!" << std::endl;
        return -1;
    }

    // Create sprite for background
    sf::Sprite backgroundSprite(backgroundTexture);

    // Scale background to fit window
    float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Load music
    sf::Music music;
    if (!music.openFromFile("2001.wav")) {
        std::cerr << "Failed to load music!" << std::endl;
        return -1;
    }

    bool musicPlaying = false;

    NB::Universe universe(window.getSize());

    // Load universe data
    std::ifstream input("planets.txt");
    if (input.is_open()) {
        input >> universe;
        input.close();
    } else {
        std::cerr << "Failed to open planets.txt" << std::endl;
        return -1;
    }

    universe.setBodyScale(1.2f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Handle music toggle
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
                if (musicPlaying) {
                    music.stop();
                    musicPlaying = false;
                } else {
                    music.play();
                    musicPlaying = true;
                }
            }

            // Handle window resize
            if (event.type == sf::Event::Resized) {
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                universe.setWindowSize(window.getSize());

                // Rescale background
                scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
                scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
                backgroundSprite.setScale(scaleX, scaleY);
            }
        }

        window.clear();

        // Draw background
        window.draw(backgroundSprite);

        // Draw universe
        window.draw(universe);

        window.display();
    }

    return 0;
}
