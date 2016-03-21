// Copyright 2015 <Yusuf Yildiz>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Main
#include <boost/test/unit_test.hpp>

#include <stdint.h>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "RingBuffer.hpp"

BOOST_AUTO_TEST_CASE(RBcontructor) {
  BOOST_REQUIRE_NO_THROW(RingBuffer(100));
  BOOST_REQUIRE_THROW(RingBuffer(0), std::exception);
  BOOST_REQUIRE_THROW(RingBuffer(0), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(RBenque_dequeue) {
  RingBuffer rb(4);
  rb.enqueue(9);
  rb.enqueue(2);
  rb.enqueue(1);
  rb.enqueue(0);

  BOOST_REQUIRE_THROW(rb.enqueue(10), std::runtime_error);
  BOOST_REQUIRE(rb.size() == 4);
  BOOST_REQUIRE(rb.isFull() == true);
  BOOST_REQUIRE(rb.peek() == 9);
  BOOST_REQUIRE(rb.dequeue() == 9);
  BOOST_REQUIRE(rb.peek() == 2);
  BOOST_REQUIRE(rb.dequeue() == 2);
  BOOST_REQUIRE(rb.peek() == 1);

  BOOST_REQUIRE(rb.isEmpty() == false);
  BOOST_REQUIRE(rb.isFull() == false);

  BOOST_REQUIRE(rb.dequeue() == 1);
  BOOST_REQUIRE(rb.peek() == 0);
  BOOST_REQUIRE(rb.dequeue() == 0);

  BOOST_REQUIRE(rb.size() == 0);
  BOOST_REQUIRE(rb.isEmpty() == true);
  BOOST_REQUIRE_THROW(rb.dequeue(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(RBsize_peek) {
  RingBuffer rb(2);
  BOOST_REQUIRE(rb.size() == 0);
  BOOST_REQUIRE_THROW(rb.peek(), std::runtime_error);
  rb.enqueue(10);
  rb.enqueue(11);

  BOOST_REQUIRE(rb.peek() == 10);
  BOOST_REQUIRE(rb.size() == 2);
}
