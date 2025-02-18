# PS3: N-Body Simulation

## Contact
Name: Manasvi Boineypally
Section: 202
Time to Complete: 7hrs


## Description
This project implements an N-Body simulation, visualizing celestial bodies in a 2D space using SFML for graphics and audio. It reads celestial body data from a file, simulates their positions, and renders them on screen with a starfield background.

### Features
1.SFML-based graphical rendering of celestial bodies
2.Background music toggle (press 'M' to play/pause)
3.Resizable window with dynamic scaling of the universe and background
4.Reading celestial body data from a file ("planets.txt")
5.Custom scaling of celestial bodies for better visualization
6.Unit tests using Boost Test framework

### Memory
The project primarily uses stack-allocated objects and standard containers (std::vector) for managing CelestialBody objects.
No explicit dynamic memory allocation or smart pointers were used in the provided code snippets.
The SFML objects (like sf::RenderWindow, sf::Texture, sf::Sprite, sf::Music) manage their own resources.

### Issues
No issuses found

### Extra Credit
1.Added background music feature with toggle functionality.
2.Implemented dynamic window resizing with proper scaling of the universe and background.

## Acknowledgements
1.SFML Documentation
2.ps3a.pdf from BlackBoard
