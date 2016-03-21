// Copyright 2015 <Yusuf Yildiz>
#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP
#include <stdint.h>
#include <iostream>

class RingBuffer {
 public:
    explicit RingBuffer(int capacity);
    int size();  // return number of items currently in the buffer
    bool isEmpty();  // is the buffer empty (size equals zero)?
    bool isFull();  // is the buffer full  (size equals capacity)?
    void enqueue(int16_t x);  // add item x to the end
    int16_t dequeue();  // delete and return item from the front
    int16_t peek();  // return (but do not delete) item from the front
 private:
    int _size;
    int _capacity;
    int16_t _first;
    int16_t * _data;
};
#endif
