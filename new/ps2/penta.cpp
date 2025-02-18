// Copyright 2024 Manasvi Boineypally

#include <iostream>
#include <ctime>
#include "penta.hpp"
#include <SFML/Graphics.hpp>

Pentaflake::Pentaflake(double sideLength, int depth)
    : m_sideLength(sideLength), m_depth(depth), m_rotationAngle(0.0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Pentaflake::updateRotation(float deltaTime) {
    const float rotationSpeed = 45.0f;  // degrees per second
    m_rotationAngle += rotationSpeed * deltaTime;

    if (m_rotationAngle >= 360.0f) {
        m_rotationAngle -= 360.0f;
    }
}

void Pentaflake::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    sf::Vector2f center(target.getSize().x / 2.0f, target.getSize().y / 2.0f);

    // Create a transform for rotation
    sf::Transform rotationTransform;
    rotationTransform.rotate(m_rotationAngle, center);

    drawPentaflake(target, center, m_sideLength, m_depth, rotationTransform);
}

void Pentaflake::drawPentaflake(sf::RenderTarget& target, sf::Vector2f center,
                                double sideLength, int depth,
                                const sf::Transform& transform) const {
    if (depth == 0) {
        sf::ConvexShape pentagon = createPentagon(center, sideLength, 0);
        target.draw(pentagon, transform);
        return;
    }

    double childSideLength = sideLength / (1 + PHI);
    double R = sideLength / (2 * std::sin(M_PI / 5));

    for (int i = 0; i < 5; ++i) {
        double angle = i * 2 * M_PI / 5;
        sf::Vector2f childCenter(
            center.x + R * std::sin(angle),
            center.y - R * std::cos(angle));
        drawPentaflake(target, childCenter,
                        childSideLength, depth - 1, transform);
    }

    drawPentaflake(target, center, childSideLength, depth - 1, transform);
}

sf::ConvexShape Pentaflake::createPentagon(sf::Vector2f center,
                                           double sideLength,
                                           double rotation) const {
    sf::ConvexShape pentagon;
    pentagon.setPointCount(5);

    // Generate random color in RGB format
    sf::Color pentagonColor(std::rand() % 256,
                             std::rand() % 256, std::rand() % 256);

    // Set points of the pentagon
    for (int i = 0; i < 5; ++i) {
        double angle = rotation + i * 2 * M_PI / 5;
        pentagon.setPoint(i, sf::Vector2f(
            center.x + sideLength * std::cos(angle),
            center.y + sideLength * std::sin(angle)));
    }

    pentagon.setFillColor(pentagonColor);  // Set random color
    pentagon.setOutlineColor(sf::Color::Black);
    pentagon.setOutlineThickness(1);

    return pentagon;
}
