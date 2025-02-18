// Copyright [2024] <manasvi boineypally>
#include <iostream>
#include <string>

#include "FibLFSR.hpp"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

using PhotoMagic::FibLFSR;

BOOST_AUTO_TEST_CASE(testStepInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testGenerateInstr) {
  FibLFSR l("1011011000110110");
  BOOST_REQUIRE_EQUAL(l.generate(9), 51);
}

// New test cases
BOOST_AUTO_TEST_CASE(testStepCase2) {
  FibLFSR l("1110001110001110");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
}

BOOST_AUTO_TEST_CASE(testGenerateCase2) {
  FibLFSR l("1110001110001110");
  BOOST_REQUIRE_EQUAL(l.generate(9), 0);
}

BOOST_AUTO_TEST_CASE(testStepCase3) {
  FibLFSR l("0001110001110001");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
}

BOOST_AUTO_TEST_CASE(testGenerateCase3) {
  FibLFSR l("0001110001110001");
  BOOST_REQUIRE_EQUAL(l.generate(9), 0);
}

BOOST_AUTO_TEST_CASE(testStepCase4) {
  FibLFSR l("1100110011001100");
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
}

BOOST_AUTO_TEST_CASE(testGenerateCase4) {
  FibLFSR l("1100110011001100");
  BOOST_REQUIRE_EQUAL(l.generate(9), 0);
}

BOOST_AUTO_TEST_CASE(testStepCase5) {
FibLFSR l("1011100101001100");
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 0);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
  BOOST_REQUIRE_EQUAL(l.step(), 1);
}

BOOST_AUTO_TEST_CASE(testGenerateCase5) {
FibLFSR l("1011100101001100");
  BOOST_REQUIRE_EQUAL(l.generate(5), 23);
}
