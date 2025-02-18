// CopyRight 2024 Manasvi Boinepally

#include <fstream>
#include <iomanip>
#include "Universe.hpp"

namespace NB {

Universe::Universe() : radius(0), windowSize(800, 600), bodyScale(1.0f) {}

Universe::Universe(sf::Vector2u windowSize)
: radius(0), windowSize(windowSize), bodyScale(1.0f) {}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& body : bodies) {
        target.draw(body, states);
    }
}

void Universe::setRadius(double r) {
    radius = r;
}

double Universe::getRadius() const {
    return radius;
}

void Universe::updatePositions() {
    for (auto& body : bodies) {
        body.updateScreenPosition(radius, windowSize);
    }
}

void Universe::setBodyScale(float scale) {
    bodyScale = scale;
    for (auto& body : bodies) {
        body.setScale(bodyScale);
    }
}

void Universe::setWindowSize(sf::Vector2u newSize) {
    windowSize = newSize;
    updatePositions();
}

std::istream& operator>>(std::istream& is, Universe& universe) {
    size_t n;
    is >> n >> universe.radius;
    universe.bodies.resize(n);
    for (auto& body : universe.bodies) {
        is >> body;
    }
    universe.updatePositions();
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
    os << universe.bodies.size() << "\n"
       << std::scientific << std::setprecision(17) << universe.radius << "\n";
    for (const auto& body : universe.bodies) {
        os << body << "\n";
    }
    return os;
}

}  // namespace NB
