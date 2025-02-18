# PS3: N-Body Simulation

## Contact
Name: Manasvi Boineypally
Section: 202
Time to Complete: 7hrs


## Description
This project implements an N-Body simulation, visualizing celestial bodies in a 2D space using SFML for graphics and audio. It reads celestial body data from a file, simulates their positions, and renders them on screen with a starfield background.


N-Body Simulation:
The core of the simulation is in the Universe class, which manages multiple CelestialBody objects.
It uses gravitational calculations to determine the forces between bodies and update their positions and velocities over time.
The simulation step is handled in the Universe::step() method, which calculates accelerations and updates positions using numerical integration.
Visualization with SFML:
The program creates a window using SFML's sf::RenderWindow.
Celestial bodies are represented as sprites with loaded textures.
A starfield background image is used to create a space-like atmosphere.
Input and Output:
Initial celestial body data is read from standard input (likely redirected from a file).
The final state of the universe is output at the end of the simulation.
User Interface:
The simulation time is displayed on screen.
Window resizing is supported, with the simulation area adjusting accordingly.
Audio:
Background music (likely space-themed, given the "2001.wav" filename) is played using SFML's audio capabilities.
Performance Considerations:
Frame rate control is implemented to maintain consistent animation speed.
A speed factor allows adjusting the simulation speed without changing the underlying physics calculations.
Customization:
The simulation duration (T) and time step (dt) are passed as command-line arguments.
The scale of the celestial bodies can be adjusted.

### Features
1.SFML-based graphical rendering of celestial bodies
2.Background music toggle (press 'M' to play/pause)
3.Resizable window with dynamic scaling of the universe and background
4.Reading celestial body data from a file ("planets.txt")
5.Custom scaling of celestial bodies for better visualization
6.Unit tests using Boost Test framework

SFML-based graphical rendering of celestial bodies:
This is already implemented in your current code. The CelestialBody class uses SFML sprites to render the bodies, and the Universe class handles drawing them.
Background music toggle:
Add a new function in main.cpp to handle music toggling:
cpp
void toggleMusic(sf::Music& music) {
    if (music.getStatus() == sf::Music::Playing) {
        music.pause();
    } else {
        music.play();
    }
}

In the main event loop, add:
cpp
if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::M) {
    toggleMusic(backgroundMusic);
}

Resizable window with dynamic scaling:
Your current implementation already handles window resizing. To improve it, update the Universe::setWindowSize method:
cpp
void Universe::setWindowSize(sf::Vector2<double> newSize) {
    windowSize = newSize;
    updatePositions();
    // Update background sprite scale
    float scaleX = static_cast<float>(newSize.x) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(newSize.y) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
}

Reading celestial body data from a file:
Modify the main function to read from "planets.txt":
cpp
std::ifstream inputFile("planets.txt");
if (inputFile.is_open()) {
    inputFile >> universe;
} else {
    std::cerr << "Failed to open planets.txt" << std::endl;
    return -1;
}

Custom scaling of celestial bodies:
You've already implemented this with the setBodyScale method. To make it adjustable during runtime, add key controls:
cpp
if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Up) {
        universe.setBodyScale(universe.getBodyScale() * 1.1f);
    } else if (event.key.code == sf::Keyboard::Down) {
        universe.setBodyScale(universe.getBodyScale() / 1.1f);
    }
}

Unit tests using Boost Test framework:
Create a new file tests.cpp and implement some tests:
cpp
#define BOOST_TEST_MODULE NBodySimulationTests
#include <boost/test/included/unit_test.hpp>
#include "Universe.hpp"
#include "CelestialBody.hpp"

BOOST_AUTO_TEST_CASE(UniverseInitialization) {
    NB::Universe universe;
    BOOST_CHECK_EQUAL(universe.getRadius(), 0.0);
    BOOST_CHECK_EQUAL(universe.getBodies().size(), 0);
}

BOOST_AUTO_TEST_CASE(CelestialBodyProperties) {
    NB::CelestialBody body;
    body.setPosition(1.0, 2.0);
    body.setVelocity(3.0, 4.0);
    body.setMass(5.0);

    BOOST_CHECK_EQUAL(body.getPosition().x, 1.0);
    BOOST_CHECK_EQUAL(body.getPosition().y, 2.0);
    BOOST_CHECK_EQUAL(body.getVelocity().x, 3.0);
    BOOST_CHECK_EQUAL(body.getVelocity().y, 4.0);
    BOOST_CHECK_EQUAL(body.getMass(), 5.0);
}

### Memory
The project primarily uses stack-allocated objects and standard containers (std::vector) for managing CelestialBody objects.
No explicit dynamic memory allocation or smart pointers were used in the provided code snippets.
The SFML objects (like sf::RenderWindow, sf::Texture, sf::Sprite, sf::Music) manage their own resources.

Stack-allocated objects:
The project indeed primarily uses stack-allocated objects for most of its functionality. This includes the main Universe object and local variables in functions.
Standard containers:
std::vector is used to store CelestialBody objects in the Universe class. This is a good choice as it provides dynamic sizing and automatic memory management.
No explicit dynamic memory allocation:
The code snippets don't show any use of new or delete operators, which is generally a good practice in modern C++.
No smart pointers:
The code doesn't use smart pointers like std::unique_ptr or std::shared_ptr. While these can be useful for managing dynamic memory, they aren't necessary in this case due to the use of stack allocation and standard containers.
SFML resource management:
SFML objects like sf::RenderWindow, sf::Texture, sf::Sprite, and sf::Music indeed manage their own resources internally. This simplifies memory management for the programmer.
This approach has several advantages:
Simplicity: Stack allocation and standard containers are straightforward to use and understand.
Safety: Automatic memory management reduces the risk of memory leaks.
Performance: Stack allocation is generally faster than heap allocation.
However, there are a couple of points to consider:
Resource management for textures: While SFML manages the resources, it might be beneficial to implement a resource manager for textures to avoid loading the same texture multiple times.
Potential for large objects: If CelestialBody objects become very large or numerous, stack allocation might become inefficient. In such cases, considering heap allocation or smart pointers might be beneficial.

### Issues
No issuses found

### Extra Credit
1.Added background music feature with toggle functionality.
2.Implemented dynamic window resizing with proper scaling of the universe and background.

## Acknowledgements
1.SFML Documentation
2.ps3b.pdf from BlackBoard
