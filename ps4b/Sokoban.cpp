// Sokoban.cpp
// Copyright 2024 Manasvi Boineypally
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Sokoban.hpp"
#include <SFML/Graphics.hpp>

namespace SB {

Sokoban::Sokoban() : Sokoban(0, 0) {}

Sokoban::Sokoban(const std::string& filename) : w_(0), h_(0), playerPos_(0, 0),
lastDirection_(Direction::Down), moveCount_(0) {
    std::ifstream file(filename);
    if (file) {
        file >> *this;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }

    initTextures();

    initialState_ = {grid_, playerPos_, lastDirection_};
}

Sokoban::Sokoban(int w, int h) : w_(w), h_(h), playerPos_(0, 0),
lastDirection_(Direction::Down), moveCount_(0) {
    grid_.resize(h_, std::vector<char>(w_, '.'));
    initTextures();
    initialState_ = {grid_, playerPos_, lastDirection_};
}

int Sokoban::width() const { return w_; }
int Sokoban::height() const { return h_; }
sf::Vector2i Sokoban::playerLoc() const { return playerPos_; }

void Sokoban::movePlayer(Direction dir) {
    int dx = 0, dy = 0;

    switch (dir) {
        case Direction::Up: dy = -1; break;
        case Direction::Down: dy = 1; break;
        case Direction::Left: dx = -1; break;
        case Direction::Right: dx = 1; break;
    }

    int newX = playerPos_.x + dx;
    int newY = playerPos_.y + dy;

    if (canMove(newX, newY)) {
        saveState();
        incrementMoveCount();

        if (grid_[newY][newX] == 'A' || grid_[newY][newX] == 'B') {
            int boxNewX = newX + dx;
            int boxNewY = newY + dy;

            if (canMove(boxNewX, boxNewY) && grid_[boxNewY][boxNewX]
             != 'A' && grid_[boxNewY][boxNewX] != 'B') {
                if (grid_[boxNewY][boxNewX] == 'a') {
                    grid_[boxNewY][boxNewX] = 'B';
                } else {
                    grid_[boxNewY][boxNewX] = 'A';
                }
                grid_[newY][newX] = (grid_[newY][newX] == 'B') ? 'a' : '.';
            } else {
                return;
            }
        }

        grid_[playerPos_.y][playerPos_.x] = (grid_[playerPos_.y][playerPos_.x] == 'a') ? 'a' : '.';
        playerPos_ = sf::Vector2i(newX, newY);
        lastDirection_ = dir;
        updatePlayerSprite();
    }
}

bool Sokoban::isWon() const {
    return std::all_of(grid_.begin(), grid_.end(), [](const auto& row) {
        return std::none_of(row.begin(), row.end(), [](char c) { return c == 'A'; });
    });
}

void Sokoban::reset() {
    grid_ = initialState_.grid;
    playerPos_ = initialState_.playerPos;
    lastDirection_ = initialState_.lastDirection;

    updatePlayerSprite();

    undoStack = std::stack<GameState>();
    redoStack = std::stack<GameState>();
    moveCount_ = 0;
}

void Sokoban::undo() {
    if (!undoStack.empty()) {
        redoStack.push({grid_, playerPos_, lastDirection_});
        auto state = undoStack.top();
        undoStack.pop();

        grid_ = state.grid;
        playerPos_ = state.playerPos;
        lastDirection_ = state.lastDirection;

        updatePlayerSprite();

        if (moveCount_ > 0) {
            moveCount_--;
        }
    }
}

void Sokoban::redo() {
    if (!redoStack.empty()) {
        undoStack.push({grid_, playerPos_, lastDirection_});
        auto state = redoStack.top();
        redoStack.pop();

        grid_ = state.grid;
        playerPos_ = state.playerPos;
        lastDirection_ = state.lastDirection;

        updatePlayerSprite();

        moveCount_++;
    }
}

void Sokoban::initTextures() {
    if (!wallTexture.loadFromFile("wall.png") ||
        !boxTexture.loadFromFile("box.png") ||
        !playerTextureUp.loadFromFile("player_08.png") ||
        !playerTextureDown.loadFromFile("player.png") ||
        !playerTextureLeft.loadFromFile("player_20.png") ||
        !playerTextureRight.loadFromFile("player_17.png") ||
        !storageTexture.loadFromFile("ground_04.png") ||
        !groundTexture.loadFromFile("ground_01.png")) {
        std::cerr << "Error loading textures!" << std::endl;
    }

    wallSprite.setTexture(wallTexture);
    boxSprite.setTexture(boxTexture);
    storageSprite.setTexture(storageTexture);
    groundSprite.setTexture(groundTexture);

    updatePlayerSprite();
}

std::istream& operator>>(std::istream& is, Sokoban& sokoban) {
    is >> sokoban.h_ >> sokoban.w_;
    sokoban.grid_.resize(sokoban.h_, std::vector<char>(sokoban.w_));

    for (int i = 0; i < sokoban.h_; ++i) {
        for (int j = 0; j < sokoban.w_; ++j) {
            is >> sokoban.grid_[i][j];
            if (sokoban.grid_[i][j] == '@') {
                sokoban.playerPos_ = {j, i};
                sokoban.grid_[i][j] = '.';
            }
        }
    }

    return is;
}

void Sokoban::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Sprite tempSprite;
    for (int y = 0; y < h_; ++y) {
        for (int x = 0; x < w_; ++x) {
            char tile = grid_[y][x];
            const sf::Sprite* spriteToDraw = &groundSprite;  // Default to ground
            switch (tile) {
                case '#': spriteToDraw = &wallSprite; break;
                case 'A': spriteToDraw = &boxSprite; break;
                case 'a': spriteToDraw = &storageSprite; break;
            }
            tempSprite = *spriteToDraw;
            tempSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
            target.draw(tempSprite, states);
            if (tile == 'A') {
                tempSprite = boxSprite;
                tempSprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
                target.draw(tempSprite, states);
            }
            // Don't draw boxes on storage locations ('B')
        }
    }

    tempSprite = playerSprite;
    tempSprite.setPosition(playerPos_.x * TILE_SIZE, playerPos_.y * TILE_SIZE);
    target.draw(tempSprite, states);
}

bool Sokoban::canMove(int x, int y) const {
    if (x < 0 || x >= w_ || y < 0 || y >= h_) return false;
    return grid_[y][x] != '#';
}

void Sokoban::saveState() {
    undoStack.push({grid_, playerPos_, lastDirection_});
    redoStack = std::stack<GameState>();
}

void Sokoban::updatePlayerSprite() {
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

void Sokoban::incrementMoveCount() {
    moveCount_++;
}

int Sokoban::pixelWidth() const {
    return w_ * TILE_SIZE;
}

int Sokoban::pixelHeight() const {
    return h_ * TILE_SIZE;
}

int Sokoban::getMoveCount() const {
    return moveCount_;
}

}  // namespace SB
