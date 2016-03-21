// Copyright 2015 <Yusuf Yildiz>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include <math.h>
#include <limits.h>

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <vector>

#include "RingBuffer.hpp"
#include "GuitarString.hpp"

#define CONCERT_A 220.0
#define SAMPLES_PER_SEC 44100

std::vector<sf::Int16> makeSamplesFromString(GuitarString gs) {
  std::vector<sf::Int16> samples;

  gs.pluck();
  int duration = 8;  // seconds
  int i;
  for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
    gs.tic();
    samples.push_back(gs.sample());
  }

  return samples;
}

int main() {
  sf::RenderWindow window(sf::VideoMode(300, 200), "SFML Guitar Hero Lite");
  sf::Event event;
  double freq;
  int size = 37;
  std::vector<sf::SoundBuffer> buffers(size);
  std::vector<sf::Sound> sounds(size);
  std::vector<std::vector<sf::Int16> > samples(size);

  for (int i = 0; i < size; i++) {
    freq = 100 + (i * 20);
    GuitarString gString = GuitarString(freq);
    samples[i] = makeSamplesFromString(gString);
    buffers[i].loadFromSamples(&samples[i][0], samples[i].size(), 2, SAMPLES_PER_SEC);//NOLINT
    sounds[i].setBuffer(buffers[i]);
  }
  int index;
  std::string keyboard = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";
  while (window.isOpen()) {
    while (window.pollEvent(event)) {
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::TextEntered:
          index = keyboard.find(event.text.unicode);
          if (index != std::string::npos)
            sounds[index].play();
          break;

        default:
          break;
      }
      window.clear();
      window.display();
    }
  }
  return 0;
}

