#pragma once

#include <cstdint>
#include "image.hpp"
#include "types.hpp"
// #include <omp.h>

namespace preprocessor {
    // Функция для вычисления яркости пикселей по формуле
    uint8_t calculateLumance(uint8_t r, uint8_t g, uint8_t b);
    Image grayScaleImage(const Image& image, const ROI& roi);
}