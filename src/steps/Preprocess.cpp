#include "Preprocess.hpp"

#include <cstdint>

Preprocess::Preprocess(const Image& inputImage, Image& outputImage, const Config& config)
    : inputImage(inputImage), outputImage(outputImage), config(config) {};

void Preprocess::process() {
    Image preprocessedImage(inputImage.width, inputImage.height, 2);
    int offset = config.gradient_offset;

    for (int y = 0; y < inputImage.height; ++y) {
        for (int x = 0; x < inputImage.width; ++x) {
            if (!inputImage.is_valid(x, y)) continue;

            // Пример обработки: копирование пикселей с учетом смещения
            preprocessedImage.at(x, y, 0) = inputImage.at(x, y, 0) / 4 + inputImage.at(x, y, 1) / 2 + inputImage.at(x, y, 2) / 4;
            if (x < offset || x >= inputImage.width - offset || y < offset || y >= inputImage.height - offset) continue;
            int diff_h = std::abs((inputImage.at(x + offset, y, 0) / 4 + inputImage.at(x + offset, y, 1) / 2 + inputImage.at(x + offset, y, 2) / 4)
            - (inputImage.at(x - offset, y, 0) / 4 + inputImage.at(x - offset, y, 1) / 2 + inputImage.at(x - offset, y, 2) / 4));
            int diff_v = std::abs((inputImage.at(x, y + offset, 0) / 4 + inputImage.at(x, y + offset, 1) / 2 + inputImage.at(x, y + offset, 2) / 4)
             - (inputImage.at(x, y - offset, 0) / 4 + inputImage.at(x, y - offset, 1) / 2 + inputImage.at(x, y - offset, 2) / 4));
        }
    }

    int blur = config.blurRadius;
    for (int y = blur; y < inputImage.height; ++y) {
        for (int x = blur; x < inputImage.width; ++x) {
            uint8_t max_grad = 0;
            uint8_t min_light = 255;

            for (int dy = -blur; dy <= blur; ++dy) {
                for (int dx = -blur; dx <= blur; ++dx) {
                    int current_x = x + dx;
                    int current_y = y + dy;
                    if (!preprocessedImage.is_valid(current_x, current_y)) continue;
                    max_grad = std::max(max_grad, preprocessedImage.at(x + dx, y + dy, 1));
                    min_light = std::min(min_light, preprocessedImage.at(x + dx, y + dy, 0));
                }
            }
            outputImage.at(x, y, 0) = min_light;
            outputImage.at(x, y, 1) = max_grad;
        }
    }
}