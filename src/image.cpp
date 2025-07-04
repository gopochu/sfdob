#include "image.hpp"
#include <iostream>

uint8_t Image::get(int x, int y, int c) const{
    return data[(y * width + x) * channels + c];
}

void Image::set(int x, int y, uint8_t value, int c) {
    if (x < 0 || x >= width || y < 0 || y >= height || c < 0 || c >= channels)
        throw std::out_of_range("Invalid coordinates in Image::set()");
    data[(y * width + x) * channels + c] = value;
}

void setRGB(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    set(x, y, r, 0);
    set(x, y, g, 1);
    set(x, y, b, 2);
}