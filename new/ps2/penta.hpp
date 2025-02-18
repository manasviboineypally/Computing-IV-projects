// CopyRight 2024 Manasvi Boineypally

#pragma once

#include <cmath>
#include <SFML/Graphics.hpp>


class Pentaflake : public sf::Drawable {
 public:
    Pentaflake(double sideLength, int depth);

    // Method to update rotation
    void updateRotation(float deltaTime);

 protected:
    // Override the draw method to handle rendering
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 private:
    // Recursive function to draw the pentaflake
    void drawPentaflake(sf::RenderTarget& target,
                        sf::Vector2f center, double sideLength,
                        int depth, const sf::Transform& transform) const;

    // Function to create a single pentagon shape
    sf::ConvexShape createPentagon(sf::Vector2f center,
                                 double sideLength, double rotation) const;

    double m_sideLength;         // Side length of the pentaflake
    int m_depth;                 // Recursion depth
    float m_rotationAngle;       // Current rotation angle
    static constexpr double PHI = 1.6180339887;  // Golden ratio
};
