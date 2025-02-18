// CopyRight 2024 Manasvi Boinepally

#include <sstream>
#define BOOST_TEST_MODULE NBodySimulationTest
#include "CelestialBody.hpp"
#include "Universe.hpp"
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(CelestialBodyInitialization) {
    NB::CelestialBody body;
    BOOST_CHECK_EQUAL(body.getPosition().x, 0);
    BOOST_CHECK_EQUAL(body.getPosition().y, 0);
}

BOOST_AUTO_TEST_CASE(CelestialBodyPositionSetting) {
    NB::CelestialBody body;
    body.setPosition(100, 200);
    BOOST_CHECK_EQUAL(body.getPosition().x, 100);
    BOOST_CHECK_EQUAL(body.getPosition().y, 200);
}

BOOST_AUTO_TEST_CASE(CelestialBodyInputOutput) {
    NB::CelestialBody body;
    std::stringstream ss;
    ss << "100 200 10 20 1e24 mars.gif";
    ss >> body;
    BOOST_CHECK_EQUAL(body.getPosition().x, 100);
    BOOST_CHECK_EQUAL(body.getPosition().y, 200);
}

BOOST_AUTO_TEST_CASE(UniverseInitialization) {
    NB::Universe universe(sf::Vector2u(800, 600));
    BOOST_CHECK_EQUAL(universe.getRadius(), 0);
}

BOOST_AUTO_TEST_CASE(UniverseInputOutput) {
    NB::Universe universe(sf::Vector2u(800, 600));
    std::stringstream ss;
    ss << "2 1e11\n";
    ss << "0 0 0 0 1e30 sun.gif\n";
    ss << "1e11 0 0 30000 6e24 earth.gif\n";
    ss >> universe;
    BOOST_CHECK_EQUAL(universe.getRadius(), 1e11);

    std::stringstream output;
    output << universe;
    std::string expected = "2 1e+11\n0 0 0 0 1e+30\n1e+11 0 0 30000 6e+24\n";
}
