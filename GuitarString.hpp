// Copyright 2015 <Yusuf Yildiz>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include "RingBuffer.hpp"

class GuitarString{
 public:
    explicit GuitarString(double frequency);
    explicit GuitarString(std::vector<sf::Int16> init);
    ~GuitarString();
    void pluck();
    void tic();
    sf::Int16 sample();
    int time();
 private:
    RingBuffer* _rb_ptr;
    int _tics;
};
