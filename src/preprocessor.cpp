#include "preprocessor.hpp"

#include <cstdint>
#include <image.hpp>
#include <types.hpp>
#include <stdexcept>

uint8_t preprocessor::calculateLumance(uint8_t r, uint8_t g, uint8_t b) {
    int lumance = static_cast<int>(static_cast<int>(r) / 4 + 
                                   static_cast<int>(g) / 2 + 
                                   static_cast<int>(b) / 4);
    return static_cast<uint8_t>(lumance);
};



Image preprocessor::grayScaleImage(const Image &image, const ROI &roi) {
    Image grayImage(image.width, image.height, 1); // Создаем новый Image с одним каналом
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            if (i < roi.x_min || i > roi.x_max || j < roi.y_min || j > roi.y_max) {
                continue;
            }
            uint8_t r = image.get(i, j, 0);
            uint8_t g = image.get(i, j, 1);
            uint8_t b = image.get(i, j, 2);
            uint8_t lumance = calculateLumance(r, g, b);
            grayImage.set(i, j, lumance, 0);
        }
    }
    return grayImage;
};