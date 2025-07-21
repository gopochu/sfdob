#include "Preprocess.h"
#include "Image.h"

#include <cstdint>
#include <algorithm>

Preprocess::Preprocess(const Image& inputImage, Image& outputImage, const Config& config)
    : inputImage(inputImage), config(config) {};

void Preprocess::process() {
    outputImage = inputImage;
    outputImage = blurImage(outputImage);
    scaleImage(outputImage);
}

Image Preprocess::scaleImage(const Image& inputImage) {
    #if COLOR_MODE == 1
    grayScaleImage();
    #elif COLOR_MODE == 2
    greenScaleImage();
    #elif COLOR_MODE == 3
    maxGradientImage();
    #endif
    return outputImage;
}

void Preprocess::grayScaleImage() {
    const int offset = config.gradient_offset;
    outputImage = inputImage;
    for (int y = 0; y < inputImage.height; ++y) {
        for (int x = 0; x < inputImage.width; ++x) {
            if (!inputImage.is_valid(x, y)) continue;

            uint8_t grayValue = (inputImage.at(x, y, 0) / 4 + inputImage.at(x, y, 1) / 2 + inputImage.at(x, y, 2) / 4);
            outputImage.at(x, y, 0) = grayValue;
            outputImage.at(x, y, 1) = grayValue;
            outputImage.at(x, y, 2) = grayValue;
        }
    }
}

void Preprocess::greenScaleImage() {
    const int offset = config.gradient_offset;
    for (int y = 0; y < inputImage.height; ++y) {
        for (int x = 0; x < inputImage.width; ++x) {
            outputImage.at(x, y, 0) = 0;
            outputImage.at(x, y, 1) = inputImage.at(x, y, 1);
            outputImage.at(x, y, 2) = 0;
        }
    }
}


void Preprocess::maxGradientImage() {
    const int offset = config.gradient_offset;
    for (int y = 0; y < inputImage.height; ++y) {
        for (int x = 0; x < inputImage.width; ++x) {
            if (!inputImage.is_valid(x, y)) continue;

            uint8_t max_grad = 0;
            if (x >= offset && x < inputImage.width - offset && y >= offset && y < inputImage.height - offset) {
                int grad_h = std::abs(inputImage.at(x + offset, y, 1) - inputImage.at(x - offset, y, 1));
                int grad_v = std::abs(inputImage.at(x, y + offset, 1) - inputImage.at(x, y - offset, 1));
                max_grad = std::max(grad_h, grad_v);
            }
            outputImage.at(x, y, 0) = max_grad;
        }
    }
}

Image Preprocess::blurImage(Image& image) {
    outputImage = image;
    const int blur = config.blurRadius;
    for (int y = blur; y < inputImage.height; ++y) {
        for (int x = blur; x < inputImage.width; ++x) {
            uint8_t max_grad = 0;
            uint8_t min_light = 255;

            for (int dy = -blur; dy <= blur; ++dy) {
                for (int dx = -blur; dx <= blur; ++dx) {
                    int current_x = x + dx;
                    int current_y = y + dy;
                    if (!outputImage.is_valid(current_x, current_y)) continue;
                    outputImage.at(x, y, 0) = std::max(max_grad, outputImage.at(x + dx, y + dy, 1));
                    outputImage.at(x, y, 1) = std::min(min_light, outputImage.at(x + dx, y + dy, 0));
                }
            }
        }
    }
    return outputImage;
}