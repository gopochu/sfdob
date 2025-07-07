#include "image.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>

Image::Image() : width(0), height(0), channels(0) {};

Image::Image(int width, int height, int channels)
    : width(width), height(height), channels(channels), data(width * height * channels) {
    if (width <= 0 || height <= 0 || channels <= 0) {
        throw std::invalid_argument("Width, height, and channels must be positive integers.");
    }
    data.resize(static_cast<size_t>(width) * height * channels);
}

// Храним значение всех пикселей по каналам
uint8_t Image::get(int x, int y, int c) const{
    if (x < 0 || x >= width || y < 0 || y >= height || c < 0 || c >= channels)
        throw std::out_of_range("Invalid coordinates in Image::get()");
    return data[(static_cast<size_t>(y) * width + x) * channels + c];
}

// Устанавливаем цвет для каждого пикселя
void Image::set(int x, int y, uint8_t value, int c) {
    if (x < 0 || x >= width || y < 0 || y >= height || c < 0 || c >= channels)
        throw std::out_of_range("Invalid coordinates in Image::set()");
    data[(static_cast<size_t>(y) * width + x) * channels + c] = value;
}

void Image::setRGB(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if(channels < 3) {
        throw std::runtime_error("Image must have at least 3 channels for RGB.");
    }
    set(x, y, r, 0);
    set(x, y, g, 1);
    set(x, y, b, 2);
}