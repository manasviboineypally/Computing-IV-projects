// Copyright 2024 Manasvi Boinepally

#include <vector>
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>

namespace NB {

class Universe : public sf::Drawable {
 private:
    std::vector<CelestialBody> bodies;
    double radius;
    sf::Vector2u windowSize;
    float bodyScale;

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 public:
    Universe();
    explicit Universe(sf::Vector2u windowSize);

    void setRadius(double r);
    double getRadius() const;
    void updatePositions();
    void setBodyScale(float scale);
    void setWindowSize(sf::Vector2u newSize);

    friend std::istream& operator>>(std::istream& is, Universe& universe);
    friend std::ostream& operator<<(std::ostream& os, const Universe& universe);
};

}  // namespace NB

#endif  // UNIVERSE_HPP
