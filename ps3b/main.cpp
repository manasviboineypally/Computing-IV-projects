// Copyright 2020 Matt Zagame
#include "Universe.hpp"
#include <fstream>
#include <SFML/Audio.hpp>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "usage: ./NBody T Δt < input_file" << std::endl;
        exit(-1);
    }
    double time = strtod(argv[1], nullptr);
    double deltaT = strtod(argv[2], nullptr);
    int elapsed_time = 0;

    Universe universe;
    try {
        universe = Universe("starfield.jpg");
        std::cin >> universe;       // get universe data from file input
    }
    catch (const std::invalid_argument& err) {
        std::cout << err.what() << std::endl;
        exit(-1);
    }
    sf::Vector2u windowSize = universe.getImage().getSize();
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y),
    "The Solar System!");
    window.setFramerateLimit(60);

    sf::Music music;
    if (!music.openFromFile("2001.wav")) {
        std::cout << "Cannot load music nbody/2001.wav" << std::endl;
    }
    music.play();
    music.setLoop(true);

    sf::Text timer;
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) { 
        std::cout << "Cannot load font nbody/verdana.ttf" << std::endl;
    }
    timer.setFont(font);
    timer.setFillColor(sf::Color::White);
    timer.setCharacterSize(16);

    // SFML display loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        timer.setString("Elapsed time: " + std::to_string(elapsed_time) +
        "seconds");
        window.clear();
        window.draw(universe);
        for (int i = 0; i < universe.getNumOfPlanets(); i++) {
            window.draw(*universe.planets[i]);
        }
        window.draw(timer);
        if (elapsed_time < time) {
            universe.step(deltaT);      // call to step function
            elapsed_time += deltaT;
        }
        else music.stop();
        window.display();
    }

    // print output to file
    std::ofstream outfile;
    outfile.open("output.txt");
    outfile << universe.getNumOfPlanets() << std::endl;
    outfile << std::scientific << universe.getRadius() << std::endl;
    for (int i = 0; i < universe.getNumOfPlanets(); i++) {
        outfile << std::scientific << universe.planets[i]->getXPos()
        << "  " << std::scientific << universe.planets[i]->getYPos()
        << "  " << std::scientific << universe.planets[i]->getXVel()
        << "  " << std::scientific << universe.planets[i]->getYVel()
        << "  " << std::scientific << universe.planets[i]->getMass()
        << "  " << universe.planets[i]->getImageFilename() << std::endl;
    }
    outfile.close();

    return 0;
}
