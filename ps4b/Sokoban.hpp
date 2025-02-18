// Sokoban.hpp
// Copyright 2024 Manasvi Boineypally
#ifndef SOKOBAN_HPP
#define SOKOBAN_HPP

#include <vector>
#include <stack>
#include <SFML/Graphics.hpp>

namespace SB {

enum class Direction { Up, Down, Left, Right };

class Sokoban : public sf::Drawable {
 public:
    Sokoban();
    explicit Sokoban(const std::string& filename);
    Sokoban(int w, int h);

    int width() const;
    int height() const;
    sf::Vector2i playerLoc() const;

    void movePlayer(Direction dir);
    bool isWon() const;
    void reset();
    void undo();
    void redo();

    int pixelWidth() const;
    int pixelHeight() const;
    int getMoveCount() const;

    static int getTileSize() { return TILE_SIZE; }

 private:
    int w_, h_;
    std::vector<std::vector<char>> grid_;
    sf::Vector2i playerPos_;
    Direction lastDirection_;
    int moveCount_;

    struct GameState {
        std::vector<std::vector<char>> grid;
        sf::Vector2i playerPos;
        Direction lastDirection;
    };

    GameState initialState_;
    std::stack<GameState> undoStack;
    std::stack<GameState> redoStack;

    void initTextures();
    bool canMove(int x, int y) const;
    void saveState();
    void updatePlayerSprite();
    void incrementMoveCount();

    sf::Texture wallTexture, boxTexture, playerTextureUp, playerTextureDown,
                playerTextureLeft, playerTextureRight, storageTexture, groundTexture;
    sf::Sprite wallSprite, boxSprite, playerSprite, storageSprite, groundSprite;

    static const int TILE_SIZE = 64;  // Increased tile size
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    friend std::istream& operator>>(std::istream& is, Sokoban& sokoban);
};

}  // namespace SB

#endif  // SOKOBAN_HPP
