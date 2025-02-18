// Copyright 2024 <Manasvi Boineypally>
#define BOOST_TEST_MODULE RandWriterTest
#include <boost/test/included/unit_test.hpp>
#include "RandWriter.hpp"

BOOST_AUTO_TEST_CASE(constructor_test) {
    BOOST_REQUIRE_NO_THROW(RandWriter("abcde", 2));
    BOOST_REQUIRE_THROW(RandWriter("abc", 4), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(order_k_test) {
    RandWriter rw("abcdeabcde", 3);
    BOOST_REQUIRE_EQUAL(rw.orderK(), 3);
}

BOOST_AUTO_TEST_CASE(freq_test) {
    RandWriter rw("abcdeabcde", 2);
    BOOST_REQUIRE_EQUAL(rw.freq("ab"), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("bc"), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("de"), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("ea"), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("ab", 'c'), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("de", 'a'), 2);
    BOOST_REQUIRE_EQUAL(rw.freq("de", 'x'), 0);
    BOOST_REQUIRE_THROW(rw.freq("a"), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.freq("abc"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(krand_test) {
    RandWriter rw("abcdeabcde", 2);
    BOOST_REQUIRE_NO_THROW(rw.kRand("ab"));
    BOOST_REQUIRE_THROW(rw.kRand("xy"), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.kRand("a"), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(generate_test) {
    RandWriter rw("abcdeabcde", 2);
    std::string generated = rw.generate("ab", 10);
    BOOST_REQUIRE_EQUAL(generated.length(), 10);
    BOOST_REQUIRE_EQUAL(generated.substr(0, 2), "ab");
    BOOST_REQUIRE_THROW(rw.generate("xy", 10), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.generate("a", 10), std::invalid_argument);
    BOOST_REQUIRE_THROW(rw.generate("ab", 1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(zero_order_test) {
    RandWriter rw("abcdeabcde", 0);
    BOOST_REQUIRE_EQUAL(rw.freq(""), 10);
    BOOST_REQUIRE_EQUAL(rw.freq("", 'a'), 3);
    BOOST_REQUIRE_EQUAL(rw.freq("", 'x'), 0);
    BOOST_REQUIRE_NO_THROW(rw.kRand(""));
    std::string generated = rw.generate("", 10);
    BOOST_REQUIRE_EQUAL(generated.length(), 10);
}
