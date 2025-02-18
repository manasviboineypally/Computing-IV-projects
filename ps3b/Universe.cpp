// Universe.cpp
// Copyright 2024 Manasvi Boinepally

#include <fstream>
#include <iomanip>
#include <cmath>
#include "Universe.hpp"

namespace NB {

Universe::Universe() : radius(0), windowSize(800.0, 600.0), bodyScale(1.0f),
elapsedTime(0.0), speedFactor(1.0) {}

Universe::Universe(sf::Vector2<double> windowSize)
: radius(0), windowSize(windowSize), bodyScale(1.0f), elapsedTime(0.0), speedFactor(1.0) {}

void Universe::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (const auto& body : bodies) {
        target.draw(*body, states);
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
        body->updateScreenPosition(radius, windowSize);
    }
}

void Universe::setBodyScale(float scale) {
    bodyScale = scale;
    for (auto& body : bodies) {
        body->setScale(bodyScale);
    }
}

void Universe::setWindowSize(sf::Vector2<double> newSize) {
    windowSize = newSize;
    updatePositions();
}

void Universe::setSpeedFactor(double factor) {
    speedFactor = factor;
}

sf::Vector2<double> Universe::calculateAcceleration(const CelestialBody& body) {
    const double G = 6.67430e-11;
    sf::Vector2<double> acceleration(0, 0);

    for (const auto& other : bodies) {
        if (other.get() != &body) {
            sf::Vector2<double> delta = other->getPosition() - body.getPosition();
            double distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
            double forceMagnitude = G * body.getMass() * other->getMass() / (distance * distance);
            acceleration.x += forceMagnitude * delta.x / (distance * body.getMass());
            acceleration.y += forceMagnitude * delta.y / (distance * body.getMass());
        }
    }

    return acceleration;
}

void Universe::step(double dt) {
    double adjustedDt = dt * speedFactor;
    std::vector<sf::Vector2<double>> accelerations;

    // Calculate accelerations
    for (const auto& body : bodies) {
        accelerations.push_back(calculateAcceleration(*body));
    }

    // Update positions and velocities
    for (size_t i = 0; i < bodies.size(); ++i) {
        sf::Vector2<double> position = bodies[i]->getPosition();
        sf::Vector2<double> velocity = bodies[i]->getVelocity();

        position.x += velocity.x * adjustedDt + 0.5 * accelerations[i].x * adjustedDt * adjustedDt;
        position.y += velocity.y * adjustedDt + 0.5 * accelerations[i].y * adjustedDt * adjustedDt;

        velocity.x += accelerations[i].x * adjustedDt;
        velocity.y += accelerations[i].y * adjustedDt;

        bodies[i]->setPosition(position.x, position.y);
        bodies[i]->setVelocity(velocity.x, velocity.y);
    }

    elapsedTime += adjustedDt;
    updatePositions();
}

double Universe::getElapsedTime() const {
    return elapsedTime;
}

const std::vector<std::unique_ptr<CelestialBody>>& Universe::getBodies() const {
    return bodies;
}

std::istream& operator>>(std::istream& is, Universe& universe) {
    size_t n;
    is >> n >> universe.radius;
    universe.bodies.clear();
    for (size_t i = 0; i < n; ++i) {
        auto body = std::make_unique<CelestialBody>();
        is >> *body;
        universe.bodies.push_back(std::move(body));
    }
    universe.updatePositions();
    return is;
}

std::ostream& operator<<(std::ostream& os, const Universe& universe) {
    os << universe.bodies.size() << "\n"
       << std::scientific << std::setprecision(3) << universe.radius << "\n";
    for (const auto& body : universe.bodies) {
        os << std::scientific << std::setprecision(4)
           << body->getPosition().x << " " << body->getPosition().y << " "
           << body->getVelocity().x << " " << body->getVelocity().y << " "
           << std::defaultfloat << std::setprecision(4) << body->getMass() << " "
           << body->getFilename() << "\n";
    }
    return os;
}

}  // namespace NB
