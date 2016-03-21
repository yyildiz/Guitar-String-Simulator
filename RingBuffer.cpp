// Copyright 2015 <Yusuf Yildiz>
#include "RingBuffer.hpp"
#include <stdint.h>
#include <iostream>
#include <exception>
#include <stdexcept>
RingBuffer::RingBuffer(int capacity) {
  if (capacity < 1)
    throw std::invalid_argument("Cannot Instantiate with capacity < 1)\n");
  _size = 0;
  _first = 0;
  _capacity = capacity;
  _data = new int16_t[_capacity];
}

int RingBuffer::size() {
  return _size;
}

bool RingBuffer::isEmpty() {
  return _size == 0;
}

bool RingBuffer::isFull() {
  return _size == _capacity;
}
void RingBuffer::enqueue(int16_t x) {
  if (isFull()) throw std::runtime_error("RingBuffer is Already Full\n");
  _data[(_first + _size) % _capacity] = x;
  _size++;
}

int16_t RingBuffer::dequeue() {
  if (isEmpty()) throw std::runtime_error("RingBuffer is Already Empty\n");
  _size--;
  int dequeued = _first;
  _first = (_first + 1) % _capacity;
  return _data[dequeued];
}

int16_t RingBuffer::peek() {
  if (isEmpty()) throw std::runtime_error("RingBuffer is Empty\n");
  return _data[_first];
}
