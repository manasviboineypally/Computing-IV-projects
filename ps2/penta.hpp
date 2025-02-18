// CopyRight 2024 Manavi Boineypally

#pragma once

#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

class FractalShape : public sf::Drawable {
 public:
    FractalShape(double initialLength, int recursionDepth);
    void buildPattern(double centerX, double centerY);
    void rotate(double angle);
    void zoom(double scaleFactor);

 private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void createFractal(double x, double y, double sideLength, int depth);
    sf::ConvexShape createPentagon(double centerX, double centerY,
                        double sideLength, const sf::Color& fill) const;
    sf::Color calculateColor(double x) const;

    double sideLength;
    int maxDepth;
    double currentRotation;
    double scale;
    std::vector<sf::ConvexShape> shapes;
    const sf::Color PENTAGON_COLOR{255, 182, 193};
};
