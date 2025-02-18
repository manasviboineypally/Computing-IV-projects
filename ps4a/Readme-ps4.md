 # PS4: Sokoban

## Contact
Name: Manasvi Boineypally
Section: 202
Time to Complete: 7hrs


## Description

This project is an implementation of the classic puzzle game Sokoban using C++ and the SFML graphics library.
Sokoban, Japanese for "warehouse keeper", is a puzzle game where the player pushes boxes around a warehouse to designated storage locations.
The game features a grid-based layout, sprite-based graphics, and level loading from files.

	
### Features

-Grid-based game world representation
-Sprite-based rendering using SFML graphics library
-Level loading from external files
-Player movement (to be implemented)
-Box pushing mechanics (to be implemented)
-Win condition checking (to be implemented)
-Texture loading for different game elements:
    -Walls
    -Boxes
    -Player character
    -Storage locations
    -Ground tiles

### Memory

This project employs several memory management techniques and considerations:
-Dynamic memory allocation using std::vector for the game grid
-Efficient use of SFML textures and sprites, likely utilizing GPU memory
-Game state primarily stored in the grid_ member variable (2D vector of characters)

### Lambdas

While the current implementation doesn't use lambda functions, potential future uses could include:
-Event handling for player input
-Custom sorting or filtering of game objects
-Implementing game logic in a functional style

### Issues
None

### Extra Credit
1.Added time on the Window in MM:SS format

## Acknowledgements

1.SFML Document
2.ps4a pdf from BlackBoard

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban
