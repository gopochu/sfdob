#include "Image.h"
#include "Preprocess.h"

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <iostream>

Preprocess::Preprocess(Image& workImage, Image& etalonImage, const Config& config)
    : workImage(workImage), etalonImage(etalonImage), config(config) {};

void Preprocess::process() {
    // outputImage = blurImage(outputImage);
    blurImage(workImage);
    scaleImage();
}

void Preprocess::scaleImage() {
    #if COLOR_MODE == 1
    grayScaleImage(workImage);
    grayScaleImage(etalonImage);
    #elif COLOR_MODE == 2
    greenScaleImage();
    #elif COLOR_MODE == 3
    maxGradientImage();
    #endif
}

void Preprocess::grayScaleImage(Image& img) {
    const int offset = config.gradient_offset;
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            if (!img.is_valid(x, y)) continue;

            uint8_t grayValue = (img.at(x, y, 0) / 4 + img.at(x, y, 1) / 2 + img.at(x, y, 2) / 4);
            img.at(x, y, 0) = grayValue;
            img.at(x, y, 1) = grayValue;
            img.at(x, y, 2) = grayValue;
        }
    }
    std::cout << "grayscaled" << std::endl;
}

void Preprocess::greenScaleImage(Image& img) {
    const int offset = config.gradient_offset;
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            img.at(x, y, 0) = 0;
            // outputImage.at(x, y, 1) = inputImage.at(x, y, 1);
            img.at(x, y, 2) = 0;
        }
    }
}


void Preprocess::maxGradientImage(Image& img) {
    const int offset = config.gradient_offset;
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            if (!img.is_valid(x, y)) continue;

            uint8_t max_grad = 0;
            if (x >= offset && x < img.width - offset && y >= offset && y < img.height - offset) {
                int grad_h = std::abs(img.at(x + offset, y, 1) - img.at(x - offset, y, 1));
                int grad_v = std::abs(img.at(x, y + offset, 1) - img.at(x, y - offset, 1));
                max_grad = std::max(grad_h, grad_v);
            }
            img.at(x, y, 0) = max_grad;
        }
    }
}

void Preprocess::blurImage(Image& image) {
    const int blur = config.blurRadius;
    
    for (size_t y = 0; y < image.width; ++y) {
        for (size_t x = 0; x < image.height; ++x) {
            for (size_t c = 0; c < image.channels; ++c) {
                int sum = 0;
                int count = 0;

                for (size_t dy = -config.blurRadius; dy <= config.blurRadius; ++dy) {
                    for (size_t dx = -config.blurRadius; dx <= config.blurRadius; ++dx) {
                        int nx = dx + x;
                        int ny = dy + y;

                        if (nx >= 0 && nx < image.width && ny >= 0 && ny < image.height) {
                            sum += image.at(nx, ny, c);
                            ++count;
                        }
                    }
                }
                if (count != 0) image.at(x, y, c) = sum / count;
            }
        }
    }
    std::cout << "blured" << std::endl;
    // for (int y = blur; y < image.height; ++y) {
    //     for (int x = blur; x < image.width; ++x) {
    //         uint8_t max_grad = 0;
    //         uint8_t min_light = 255;

    //         for (int dy = -blur; dy <= blur; ++dy) {
    //             for (int dx = -blur; dx <= blur; ++dx) {
    //                 int current_x = x + dx;
    //                 int current_y = y + dy;
    //                 if (!image.is_valid(current_x, current_y)) continue;
    //                 image.at(x, y, 0) = std::max(max_grad, image.at(x + dx, y + dy, 1));
    //                 image.at(x, y, 1) = std::max(max_grad, image.at(x + dx, y + dy, 1));
    //                 image.at(x, y, 2) = std::max(max_grad, image.at(x + dx, y + dy, 1));
    //             }
    //         }
    //     }
    // }
}