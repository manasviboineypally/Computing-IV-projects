// CopyRight 2024 Manasvi Boineypally

#include<iostream>
#include "penta.hpp"
#include <SFML/Graphics.hpp>

int main() {
    // Create the render window with the specified size and title
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pentaflake Rotation");

    // Initialize the Pentaflake with side length 200 and depth 3
    Pentaflake pentaflake(200, 3);

    sf::Clock clock;  // Clock to track time

    while (window.isOpen()) {
        sf::Time deltaTime =
         clock.restart();  // Get the time elapsed since the last frame

        // Process events like window closing
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();  // Close the window if the close event occurs
            }
        }

        // Update the rotation of the pentaflake
        pentaflake.updateRotation(deltaTime.asSeconds());
        // Clear the window, draw the pentaflake,and display the updated content
        window.clear();
        window.draw(pentaflake);
        window.display();
    }

    return 0;
}
