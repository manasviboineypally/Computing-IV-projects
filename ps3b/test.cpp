// Copyright 2024 Manasvi Boinepally

#define BOOST_TEST_MODULE NBodySimulationTest
#include <cmath>
#include <sstream>
#include <boost/test/included/unit_test.hpp>
#include "Universe.hpp"

// Utility function for floating-point comparisons
bool isClose(double a, double b, double epsilon = 1e-9) {
    return std::abs(a - b) < epsilon;
}

BOOST_AUTO_TEST_SUITE(CelestialBodyTests)

BOOST_AUTO_TEST_CASE(Initialization) {
    NB::CelestialBody body;
    BOOST_CHECK_EQUAL(body.getPosition().x, 0);
    BOOST_CHECK_EQUAL(body.getPosition().y, 0);
    BOOST_CHECK_EQUAL(body.getVelocity().x, 0);
    BOOST_CHECK_EQUAL(body.getVelocity().y, 0);
    BOOST_CHECK_EQUAL(body.getMass(), 0);
}

BOOST_AUTO_TEST_CASE(PositionSetting) {
    NB::CelestialBody body;
    body.setPosition(100, 200);
    BOOST_CHECK_EQUAL(body.getPosition().x, 100);
    BOOST_CHECK_EQUAL(body.getPosition().y, 200);
}

BOOST_AUTO_TEST_CASE(VelocitySetting) {
    NB::CelestialBody body;
    body.setVelocity(5, -3);
    BOOST_CHECK_EQUAL(body.getVelocity().x, 5);
    BOOST_CHECK_EQUAL(body.getVelocity().y, -3);
}

BOOST_AUTO_TEST_CASE(MassSetting) {
    NB::CelestialBody body;
    body.setMass(1e24);
    BOOST_CHECK(isClose(body.getMass(), 1e24));
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(UniverseTests)

BOOST_AUTO_TEST_CASE(Initialization) {
    NB::Universe universe(sf::Vector2<double>(800, 600));
    BOOST_CHECK_EQUAL(universe.getRadius(), 0);
    BOOST_CHECK_EQUAL(universe.getElapsedTime(), 0);
}

BOOST_AUTO_TEST_CASE(RadiusSetting) {
    NB::Universe universe;
    universe.setRadius(1e12);
    BOOST_CHECK(isClose(universe.getRadius(), 1e12));
}


BOOST_AUTO_TEST_CASE(SpeedFactorSetting) {
    NB::Universe universe(sf::Vector2<double>(800, 600));
    universe.setSpeedFactor(0.5);

    std::stringstream ss;
    ss << "2 1e11\n";
    ss << "0 0 0 0 1e30 sun.gif\n";
    ss << "1e11 0 0 30000 6e24 earth.gif\n";
    ss >> universe;

    double initialTime = universe.getElapsedTime();
    universe.step(1.0);
    double elapsedTime = universe.getElapsedTime() - initialTime;
    BOOST_CHECK(isClose(elapsedTime, 0.5, 1e-6));
}

BOOST_AUTO_TEST_SUITE_END()
