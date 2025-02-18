// CelestialBody.cpp
// Copyright 2024 Manasvi Boinepally

#include "CelestialBody.hpp"
#include <iostream>
#include <iomanip>

namespace NB {

CelestialBody::CelestialBody() : position(0, 0), velocity(0, 0), mass(0) {}

void CelestialBody::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void CelestialBody::setPosition(double x, double y) {
    position.x = x;
    position.y = y;
}

sf::Vector2<double> CelestialBody::getPosition() const {
    return position;
}

void CelestialBody::setVelocity(double vx, double vy) {
    velocity.x = vx;
    velocity.y = vy;
}

sf::Vector2<double> CelestialBody::getVelocity() const {
    return velocity;
}

void CelestialBody::setMass(double m) {
    mass = m;
}

double CelestialBody::getMass() const {
    return mass;
}

bool CelestialBody::loadTexture(const std::string& filename) {
    if (!texture.loadFromFile(filename)) {
        return false;
    }
    this->filename = filename;
    sprite.setTexture(texture);
    sprite.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
    return true;
}

void CelestialBody::setScale(float scale) {
    sprite.setScale(scale, scale);
}

std::string CelestialBody::getFilename() const {
    return filename;
}

void CelestialBody::updateScreenPosition(double universeRadius,
const sf::Vector2<double>& windowSize) {
    double screenX = (position.x + universeRadius) / (2 * universeRadius) * windowSize.x;
    double screenY = (universeRadius - position.y) / (2 * universeRadius) * windowSize.y;
    sprite.setPosition(static_cast<float>(screenX), static_cast<float>(screenY));
}

std::istream& operator>>(std::istream& is, CelestialBody& body) {
    is >> body.position.x >> body.position.y >> body.velocity.x
       >> body.velocity.y >> body.mass >> body.filename;
    body.loadTexture(body.filename);
    return is;
}

std::ostream& operator<<(std::ostream& os, const CelestialBody& body) {
    os << std::scientific << std::setprecision(4)
       << body.position.x << " " << body.position.y << " "
       << body.velocity.x << " " << body.velocity.y << " "
       << std::defaultfloat << std::setprecision(4) << body.mass << " " << body.filename;
    return os;
}

}  // namespace NB
