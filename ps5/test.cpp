#define BOOST_TEST_MODULE EDistanceTest
#include <boost/test/included/unit_test.hpp>
#include "EDistance.hpp"

BOOST_AUTO_TEST_CASE(test_penalty)
{
    EDistance ed("", ""); // Create an instance of EDistance
    BOOST_CHECK_EQUAL(ed.test_penalty('A', 'A'), 0);
    BOOST_CHECK_EQUAL(ed.test_penalty('A', 'T'), 1);
    BOOST_CHECK_EQUAL(ed.test_penalty('C', 'G'), 1);
}

BOOST_AUTO_TEST_CASE(test_min3)
{
    EDistance ed("", ""); // Create an instance of EDistance
    BOOST_CHECK_EQUAL(ed.test_min3(1, 2, 3), 1);
    BOOST_CHECK_EQUAL(ed.test_min3(3, 1, 2), 1);
    BOOST_CHECK_EQUAL(ed.test_min3(3, 3, 3), 3);
}

BOOST_AUTO_TEST_CASE(test_optDistance)
{
    EDistance ed1("AACAGTTACC", "TAAGGTCA");
    BOOST_CHECK_EQUAL(ed1.optDistance(), 7);

    EDistance ed2("ACTG", "ACTTG");
    BOOST_CHECK_EQUAL(ed2.optDistance(), 2);

    EDistance ed3("", "");
    BOOST_CHECK_EQUAL(ed3.optDistance(), 0);
}

BOOST_AUTO_TEST_CASE(test_alignment)
{
    EDistance ed("AACAGTTACC", "TAAGGTCA");
    
    std::string expected_alignment = 
        "A T 1\n"
        "A A 0\n"
        "C - 2\n"
        "A A 0\n"
        "G G 0\n"
        "T G 1\n"
        "T T 0\n"
        "A - 2\n"
        "C C 0\n"
        "C A 1\n";

    std::string actual_alignment = ed.alignment();
    
    BOOST_CHECK_EQUAL(actual_alignment, expected_alignment);
}