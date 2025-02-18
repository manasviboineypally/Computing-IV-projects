//  Copyright 2024 Manasvi Boinneypally

#include "penta.hpp"

FractalShape::FractalShape(double initialLength, int recursionDepth)
    : sideLength(initialLength), maxDepth(recursionDepth),
      currentRotation(-18.0), scale(1.0) {}

void FractalShape::buildPattern(double centerX, double centerY) {
    shapes.clear();
    createFractal(centerX, centerY, sideLength, maxDepth);
}

void FractalShape::draw(sf::RenderTarget& target,
        sf::RenderStates states) const {
    states.transform.rotate(currentRotation, target.getSize().x / 2.0f,
                            target.getSize().y / 2.0f);
    states.transform.scale(scale, scale, target.getSize().x / 2.0f,
                           target.getSize().y / 2.0f);

    for (const auto& pentagon : shapes) {
        target.draw(pentagon, states);
    }
}

void FractalShape::createFractal(double x, double y, double length, int depth) {
    if (depth == 0) {
        sf::Color fillColor = calculateColor(x);
        shapes.push_back(createPentagon(x, y, length, fillColor));
        return;
    }

    double ratio = length / (1 + (1.0 + std::sqrt(5.0)) / 2.0);
    double mainRadius = length / (2 * std::sin(M_PI / 5));
    double innerRadius = ratio / (2 * std::sin(M_PI / 5));

    createFractal(x, y, ratio, depth - 1);

    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        double offsetX = (mainRadius - innerRadius) * std::cos(angle);
        double offsetY = (mainRadius - innerRadius) * std::sin(angle);
        createFractal(x + offsetX, y + offsetY, ratio, depth - 1);
    }
}

sf::ConvexShape FractalShape::createPentagon(double centerX, double centerY,
                        double length, const sf::Color& fill) const {
    sf::ConvexShape pentagon;
    pentagon.setPointCount(5);

    double radius = length / (2 * std::sin(M_PI / 5));
    for (int i = 0; i < 5; ++i) {
        double angle = 2 * M_PI * i / 5;
        pentagon.setPoint(i, sf::Vector2f(centerX + radius * std::cos(angle),
                        centerY + radius * std::sin(angle)));
    }
    pentagon.setFillColor(fill);
    pentagon.setOutlineColor(sf::Color::White);
    pentagon.setOutlineThickness(1.0f);

    return pentagon;
}

sf::Color FractalShape::calculateColor(double x) const {
    double position = x / 600.0;
    sf::Color colorStart(255, 0, 255);   // Vibrant purple
    sf::Color colorMid1(0, 255, 255);    // Cyan
    sf::Color colorMid2(255, 165, 0);    // Orange
    sf::Color colorEnd(0, 255, 0);       // Lime green

    if (position < 0.33) {
        int red = static_cast<int>((1 - position / 0.33) *
        colorStart.r + (position / 0.33) * colorMid1.r);
        int green = static_cast<int>((1 - position / 0.33) *
        colorStart.g + (position / 0.33) * colorMid1.g);
        int blue = static_cast<int>((1 - position / 0.33) *
        colorStart.b + (position / 0.33) * colorMid1.b);
        return sf::Color(red, green, blue);
    } else if (position < 0.66) {
        int red = static_cast<int>((1 - (position - 0.33) / 0.33) *
        colorMid1.r + ((position - 0.33) / 0.33) * colorMid2.r);
        int green = static_cast<int>((1 - (position - 0.33) / 0.33) *
        colorMid1.g + ((position - 0.33) / 0.33) * colorMid2.g);
        int blue = static_cast<int>((1 - (position - 0.33) / 0.33) *
        colorMid1.b + ((position - 0.33) / 0.33) * colorMid2.b);
        return sf::Color(red, green, blue);
    } else {
        int red = static_cast<int>((1 - (position - 0.66) / 0.34) *
        colorMid2.r + ((position - 0.66) / 0.34) * colorEnd.r);
        int green = static_cast<int>((1 - (position - 0.66) / 0.34) *
        colorMid2.g + ((position - 0.66) / 0.34) * colorEnd.g);
        int blue = static_cast<int>((1 - (position - 0.66) / 0.34) *
        colorMid2.b + ((position - 0.66) / 0.34) * colorEnd.b);
        return sf::Color(red, green, blue);
    }
}

void FractalShape::rotate(double angle) {
    currentRotation += angle;
    if (currentRotation >= 360.0) {
        currentRotation -= 360.0;
    } else if (currentRotation < 0.0) {
        currentRotation += 360.0;
    }
}

void FractalShape::zoom(double scaleFactor) {
    scale = scaleFactor;
}
