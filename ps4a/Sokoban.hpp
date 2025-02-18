// CopyRight 2024 Manasvi Boineypally

#ifndef _MNT_C_USERS_MANAS_ONEDRIVE_DESKTOP_UML_COMP_4_PS4A_SOKOBAN_HPP_
#define _MNT_C_USERS_MANAS_ONEDRIVE_DESKTOP_UML_COMP_4_PS4A_SOKOBAN_HPP_

#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>

namespace SB {

enum class Direction { Up, Down, Left, Right };

class Sokoban : public sf::Drawable {
 public:
    Sokoban();  // Add default constructor
    Sokoban(int w, int h);
    int width() const;
    int height() const;
    sf::Vector2i playerLoc() const;
    void movePlayer(Direction dir);
    bool isWon() const;
    void reset();  // Add reset method
    friend std::istream& operator>>(std::istream& is, Sokoban& sokoban);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    int w_, h_;
    std::vector<std::vector<char>> grid_;
    sf::Vector2i playerPos_;

    // Sprites and Textures
    sf::Texture wallTexture, boxTexture, playerTexture, storageTexture;
    sf::Texture groundTexture;

    // Declare sprites as mutable since they need to be modified in const method
    mutable sf::Sprite wallSprite, boxSprite, playerSprite, storageSprite;
    mutable sf::Sprite groundSprite;

    void initTextures();  // For loading textures and setting sprites
};

}  // namespace SB

#endif  // _MNT_C_USERS_MANAS_ONEDRIVE_DESKTOP_UML_COMP_4_PS4A_SOKOBAN_HPP_
