// CopyRight 2024 Manasvi Boineypally

#include <iostream>
#include <vector>

#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

namespace SB {

Sokoban::Sokoban() : Sokoban(0, 0) {}

Sokoban::Sokoban(int w, int h) : w_(w), h_(h), playerPos_(0, 0) {
    grid_.resize(h_, std::vector<char>(w_, '.'));
    initTextures();  // Load textures and set up sprites
}

int Sokoban::width() const { return w_; }
int Sokoban::height() const { return h_; }
sf::Vector2i Sokoban::playerLoc() const { return playerPos_; }

void Sokoban::movePlayer(Direction dir) {
    (void)dir;  // Suppress unused parameter warning for now
    // Movement logic will be implemented in Part B
}

bool Sokoban::isWon() const {
    // Check if all boxes are in storage.
    return false;  // Placeholder
}

void Sokoban::reset() {
    // Reset the game state to its initial configuration
    w_ = 0;
    h_ = 0;
    grid_.clear();
    playerPos_ = sf::Vector2i(0, 0);
    // Add any other necessary reset logic
}

// Initialize textures and sprites
void Sokoban::initTextures() {
    // Load textures
    if (!wallTexture.loadFromFile("wall.png") ||
        !boxTexture.loadFromFile("box.png") ||
        !playerTexture.loadFromFile("player_05.png") ||
        !storageTexture.loadFromFile("target.png") ||
        !groundTexture.loadFromFile("empty.png")) {
        std::cerr << "Error loading textures!" << std::endl;
    }

    // Assign textures to sprites
    wallSprite.setTexture(wallTexture);
    boxSprite.setTexture(boxTexture);
    playerSprite.setTexture(playerTexture);
    storageSprite.setTexture(storageTexture);
    groundSprite.setTexture(groundTexture);
}

// Overload >> operator to load grid from level file
std::istream& operator>>(std::istream& is, Sokoban& sokoban) {
    is >> sokoban.h_ >> sokoban.w_;
    sokoban.grid_.resize(sokoban.h_, std::vector<char>(sokoban.w_));
    for (int i = 0; i < sokoban.h_; ++i) {
        for (int j = 0; j < sokoban.w_; ++j) {
            is >> sokoban.grid_[i][j];
            if (sokoban.grid_[i][j] == '@') {
                sokoban.playerPos_ = {j, i};  // Store player position
            }
        }
    }
    return is;
}

// Draw the game
void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int y = 0; y < h_; ++y) {
        for (int x = 0; x < w_; ++x) {
            char tile = grid_[y][x];
            sf::Sprite* spriteToDraw = nullptr;

            // Determine which sprite to draw based on the tile character
            switch (tile) {
                case '#':  // Wall
                    spriteToDraw = &wallSprite;
                    break;
                case 'A':  // Box
                    spriteToDraw = &boxSprite;
                    break;
                case 'a':  // Storage location
                    spriteToDraw = &storageSprite;
                    break;
                case '.':  // Empty ground
                default:
                    spriteToDraw = &groundSprite;
                    break;
            }

            if (spriteToDraw) {
                spriteToDraw->setPosition(x * 64, y * 64);
                target.draw(*spriteToDraw, states);
            }
        }
    }

    // Draw player sprite on top of everything else
    playerSprite.setPosition(playerPos_.x * 64, playerPos_.y * 64);
    target.draw(playerSprite, states);
}

}  // namespace SB
