// Copyright 2024 Manasvi Boinepally

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

namespace NB {

class CelestialBody : public sf::Drawable {
 private:
    sf::Vector2<double> position;
    sf::Vector2<double> velocity;
    double mass;
    sf::Texture texture;
    sf::Sprite sprite;
    std::string filename;

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 public:
    CelestialBody();
    void setPosition(double x, double y);
    sf::Vector2<double> getPosition() const;
    void setVelocity(double vx, double vy);
    sf::Vector2<double> getVelocity() const;
    void setMass(double mass);
    double getMass() const;
    bool loadTexture(const std::string& filename);
    void setScale(float scale);
    std::string getFilename() const;
    void updateScreenPosition(double universeRadius, const sf::Vector2<double>& windowSize);

    friend std::istream& operator>>(std::istream& is, CelestialBody& body);
    friend std::ostream& operator<<(std::ostream& os, const CelestialBody& body);
};

}  // namespace NB
