#include "image.hpp"
#include "image_io.hpp"

#include "preprocessor.hpp"
#include "stb_image_write.h"
#include "types.hpp"

#include <chrono>
#include <iostream>

int main() {
    // tmp code  
    auto start = std::chrono::high_resolution_clock::now();
    Image img = image_io::load("C:/programming/C++/sfdob/testdata/source.png");
    ROI roi = {0, img.width - 1, 0, img.height - 1};

    std::cout << "Image loaded: " << img.width << "x" << img.height << " with " << img.channels << " channels." << std::endl;

    img = preprocessor::grayScaleImage(img, roi);
    image_io::save(img, "test.png");

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Image saved in " << elapsed.count() << " seconds." << std::endl;

    return 0;
}