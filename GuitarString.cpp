// Copyright 2015 <Yusuf Yildiz>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <stdexcept>
#include <exception>
#include "GuitarString.hpp"
#include "RingBuffer.hpp"

GuitarString::GuitarString(double frequency) {
  _tics = 0;
  if (frequency <= 0) {
    throw std::invalid_argument("Capacity must be > 0");
  } else {
    int size = ceil(44100 / frequency);
    _rb_ptr = new RingBuffer(size);
    while (!_rb_ptr->isFull()) {
      _rb_ptr->enqueue(0);
    }
  }
}

GuitarString::GuitarString(std::vector<sf::Int16> init) {
  _tics = 0;
  if (init.size() <= 0) {
    throw std::invalid_argument("Capacity must be > 0");
  } else {
    _rb_ptr = new RingBuffer(init.size());
    int i = 0;
    while (!_rb_ptr->isFull()) {
      _rb_ptr->enqueue(init[i]);
      i++;
    }
  }
}

GuitarString::~GuitarString() {
}

void GuitarString::pluck() {
  if (_rb_ptr->isFull()) {
    for (int j = 0; j < _rb_ptr->size(); j++) {
      _rb_ptr->dequeue();
    }
  }
  while (!_rb_ptr->isFull()) {
    _rb_ptr->enqueue((sf::Int16)(rand() * 0xffff));//NOLINT
  }
}

void GuitarString::tic() {
  sf::Int16 t = 0.5 * 0.996 * (_rb_ptr->dequeue() + _rb_ptr->peek());
  _rb_ptr->enqueue(t);
  _tics++;
}

sf::Int16 GuitarString::sample() {
  return _rb_ptr->peek();
}

int GuitarString::time() {
  return _tics;
}
