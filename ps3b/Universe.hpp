// Universe.hpp
// Copyright 2024 Manasvi Boinepally

#include <vector>
#include <memory>
#include "CelestialBody.hpp"
#include <SFML/Graphics.hpp>

namespace NB {

class Universe : public sf::Drawable {
 private:
    std::vector<std::unique_ptr<CelestialBody>> bodies;
    double radius;
    sf::Vector2<double> windowSize;
    float bodyScale;
    double elapsedTime;
    double speedFactor;

    sf::Vector2<double> calculateAcceleration(const CelestialBody& body);

 protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

 public:
    Universe();
    explicit Universe(sf::Vector2<double> windowSize);
    virtual ~Universe() = default;
    const std::vector<std::unique_ptr<CelestialBody>>& getBodies() const;
    void setRadius(double r);
    double getRadius() const;
    void updatePositions();
    void setBodyScale(float scale);
    void setWindowSize(sf::Vector2<double> newSize);
    void step(double dt);
    double getElapsedTime() const;
    void setSpeedFactor(double factor);

    friend std::istream& operator>>(std::istream& is, Universe& universe);
    friend std::ostream& operator<<(std::ostream& os, const Universe& universe);
};

}  // namespace NB
