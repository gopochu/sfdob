#include "image.hpp"
#include "image_io.hpp"

#include "stb_image_write.h"

#include <chrono>
#include <iostream>

int main() {
    // tmp code
    
    auto start = std::chrono::high_resolution_clock::now();
    Image img(2, 2, 3); // 2x2 image with 3 channels (RGB)

    img.setRGB(0, 0, 0, 0, 255);
    img.setRGB(1, 0, 0, 255, 0);
    img.setRGB(0, 1, 255, 0, 0);


    image_io::save(img, "test.png");

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Image saved in " << elapsed.count() << " seconds." << std::endl;

    return 0;
}