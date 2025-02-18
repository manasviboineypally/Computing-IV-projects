# PS4: Sokoban

## Contact
Name:MANASVI BOINEYPALLY
Section:202
Time to Complete:5hrs


## Description
Explain what the project does.

This project is a Sokoban puzzle game built in C++ using the SFML library for graphics and audio. In Sokoban, players control a character that pushes boxes onto specific storage locations within a grid-based level. The project provides a responsive, interactive UI where players can navigate using the arrow keys, reset the level, or undo and redo moves, adding flexibility and ease of play. The game tracks elapsed time and move count, offering feedback on the player's performance, while a win condition is detected when all boxes are correctly placed on storage spots. The game then displays a victory message and plays a congratulatory sound. Level layouts are dynamically loaded from files, making it easy to add and play new levels without altering the code. This modular design separates game logic from rendering, enabling easy updates or modifications to both gameplay and graphics independently.

### Features
Describe what your major decisions were and why you did things that way.


#### Part b

Separation of Game Logic and UI/Rendering
Decision: I separated the core game logic (in Sokoban class) from the main rendering and event handling (in main.cpp).
Reason: This allows for a modular structure where game logic can be modified or tested independently of the graphics code. It also simplifies each file's role, making the main file primarily handle UI and SFML operations while keeping game-specific code in its own namespace.
2. Use of SFML for Graphics and Audio
Decision: I chose SFML for rendering graphics and handling audio.
Reason: SFML is lightweight and user-friendly for 2D game development, providing straightforward APIs for graphics and sound. It's also cross-platform and allows smooth integration with C++. SFML also has simple tools for handling textures and sounds, which fit well with Sokoban's needs.
3. Game State and Undo/Redo Mechanism
Decision: I implemented a stack-based undo and redo system, storing each move’s game state as a GameState struct.
Reason: Sokoban games benefit from undo and redo features, especially when players make mistakes. Using stacks for the undo and redo actions is memory efficient, as it allows players to backtrack with minimal storage overhead by saving only essential game states.
4. Tracking Moves and Displaying Time
Decision: I tracked moves using an incrementing counter and displayed elapsed time in a formatted mm:ss format.
Reason: Move count and elapsed time are common metrics in puzzle games, adding an element of challenge and allowing players to measure their performance. These metrics also enhance replayability, as players can aim to beat previous scores.
5. Dynamic Loading of Level Layouts from Files
Decision: I designed the Sokoban constructor to load a level layout from a file.
Reason: Loading levels from files enables easy creation and modification of new levels without modifying the code. This decision supports extensibility, allowing for multiple levels that can be selected by simply passing different file paths.
6. Using Textures for Game Elements
Decision: I used distinct textures for walls, boxes, ground, and the player, and applied different textures based on movement direction.
Reason: Textures improve the visual quality of the game, making it more engaging than a simple color-based rendering. Using different textures for player movement also gives players better visual feedback about their actions.

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

For storing level data in this Sokoban project, I chose a 2D vector of characters (std::vector<std::vector<char>>) to represent the grid layout of each level. Each character represents a specific game element—such as walls (#), boxes (A), storage locations (a), ground (.), and the player’s initial position (@). This setup allows for easy, direct access to each tile within the grid, making movement calculations and rendering straightforward.

### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

std::all_of for Win Condition
In the Sokoban::isWon() function, I used std::all_of to determine if the player has successfully completed the level:

bool Sokoban::isWon() const {
  return std::all_of(grid_.begin(), grid_.end(), [](const auto& row) {
      return std::none_of(row.begin(), row.end(), [](char c) { return c == 'A'; });
  });
}


### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.
no issues
### Extra Credit
Anything special you did.  This is required to earn bonus points.

MOVE COUNTER: For counting the number of moves


Implementation of moveCount_
Initialization: moveCount_ is initialized to zero in the constructor, which sets the counter to zero at the start of each level.

Incrementing the Move Counter:

In the movePlayer() method, each time a player successfully moves to a new position, the incrementMoveCount() method is called. This increments moveCount_ by one:


void Sokoban::incrementMoveCount() { 
    moveCount_++; 
}
The counter only increments if a move is successfully executed, meaning if the player attempts to move but is blocked (e.g., by a wall), the counter does not increment.

Undo and Redo Adjustments:

The moveCount_ variable also adjusts based on undo and redo operations:
Undo: When the player undoes a move, moveCount_ is decremented by one (if it’s greater than zero) to reflect that a move has been “taken back.”
Redo: When the player redoes a move, moveCount_ is incremented by one to account for re-executing the previously undone move.
These adjustments ensure that moveCount_ accurately represents the current number of completed moves, even with undo and redo functionality.
Displaying the Move Count:

The moveCount_ variable is accessed through the getMoveCount() method, which returns the current move count. This value is used to update the on-screen display within the main game loop:

moveCountText.setString("Moves: " + std::to_string(sokoban.getMoveCount()));

PLAYS VICTORY SOUND:

Include SFML Audio Header:

The project includes the necessary header for audio functionality:

#include <SFML/Audio.hpp>
Declare SoundBuffer and Sound:

In the main.cpp file, two objects are declared for handling the audio:

sf::SoundBuffer victoryBuffer;
sf::Sound victorySound(victoryBuffer);
The sf::SoundBuffer object (victoryBuffer) is responsible for loading and storing the audio file data, while the sf::Sound object (victorySound) is used to play the sound.
Load the Audio File:

The victory sound file is loaded from a specified file path using the loadFromFile() method. If the loading fails, an error message is displayed, and the program exits:

if (!victoryBuffer.loadFromFile("victory.wav")) {
    std::cerr << "Unable to load victory sound\n";
    return 1;
}
Playing the Sound:

In the game loop, the sound is triggered when the player achieves the win condition. The isWon() method of the Sokoban class checks if the game has been won:

if (!gameWon && sokoban.isWon()) {
    gameWon = true;
    victorySound.play();
}

Player changes direction while moving:

Direction Enum:

The player’s movement directions are represented by an enumeration called Direction, which defines four possible values:

enum class Direction { Up, Down, Left, Right };
This enum allows the code to easily reference and manage player directions.
Current Direction Tracking:

The lastDirection_ member variable in the Sokoban class stores the player's last movement direction:

Direction lastDirection_;
This variable is updated each time the player makes a valid move, ensuring that the correct direction is known for sprite rendering.
Movement Logic:

The player's movement is handled in the movePlayer(Direction dir) method, which takes a direction as an argument. The method calculates the new position based on the current direction:

int dx = 0, dy = 0;
switch (dir) {
    case Direction::Up: dy = -1; break;
    case Direction::Down: dy = 1; break;
    case Direction::Left: dx = -1; break;
    case Direction::Right: dx = 1; break;
}
Based on the selected direction, the corresponding dx (change in the x-coordinate) and dy (change in the y-coordinate) values are set.
Position Update and Validity Check:

The method then computes the potential new position (newX, newY) by adding the calculated dx and dy to the current player's position. It checks if the move is valid by calling the canMove(int x, int y) method, which ensures the player doesn’t move out of bounds or into walls:

if (canMove(newX, newY)) {
    // Move logic here
}
If the move is valid, the player's position is updated, and the lastDirection_ variable is set to the direction of the movement.
Updating the Player Sprite:

After moving, the player’s sprite is updated to reflect the current direction using the updatePlayerSprite() method:

void updatePlayerSprite() {
    switch (lastDirection_) {
        case Direction::Up:
            playerSprite.setTexture(playerTextureUp);
            break;
        case Direction::Down:
            playerSprite.setTexture(playerTextureDown);
            break;
        case Direction::Left:
            playerSprite.setTexture(playerTextureLeft);
            break;
        case Direction::Right:
            playerSprite.setTexture(playerTextureRight);
            break;
    }
}
This method selects the appropriate texture for the player sprite based on the last direction the player moved, ensuring that the visual representation of the player matches their current movement direction.
User Input Handling:

Player input is captured in the main game loop using SFML event handling. When arrow keys are pressed, the movePlayer() function is called with the corresponding direction, triggering the entire movement logic:

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


UNDO function:

Game State Structure:

The project defines a GameState struct that stores the necessary information to restore a previous state of the game. This includes the game grid, the player’s position, and the last direction the player moved:

struct GameState {
    std::vector<std::vector<char>> grid;
    sf::Vector2i playerPos;
    Direction lastDirection;
};
Stacks for Undo and Redo:

The Sokoban class maintains two stacks to manage the game states:

std::stack<GameState> undoStack;
std::stack<GameState> redoStack;
The undoStack holds the states that can be reverted to, while the redoStack holds states that can be restored after an undo operation.
Saving the Game State:

Before the player makes a move, the current state of the game is saved onto the undoStack. This is done in the saveState() method:

void saveState() {
    undoStack.push({grid_, playerPos_, lastDirection_});
    redoStack = std::stack<GameState>(); // Clear redo stack
}
When a move is made, saveState() is called, capturing the current game state before any changes occur. This allows the player to revert back to this state if needed.
Undo Method Implementation:

The actual undo functionality is implemented in the undo() method:

void Sokoban::undo() {
    if (!undoStack.empty()) {
        redoStack.push({grid_, playerPos_, lastDirection_}); // Save current state to redo stack
        auto state = undoStack.top(); // Get the last state to revert to
        undoStack.pop(); // Remove it from the undo stack

        // Restore the game state
        grid_ = state.grid;
        playerPos_ = state.playerPos;
        lastDirection_ = state.lastDirection;

        updatePlayerSprite(); // Update the player sprite to reflect the restored state

        // Decrement move count on undo
        if (moveCount_ > 0) {
            moveCount_--;
        }
    }
}


## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban

victory.wav file :https://pixabay.com/sound-effects/search/victory/
