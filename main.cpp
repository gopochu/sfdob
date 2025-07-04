#include "image.hpp"
#include "saveImagePNG.hpp"
#include <iostream>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main() {
    // tmp code
    Image img;
    img.width = 2;
    img.height = 2;
    img.channels = 3;
    img.data.resize(2 * 2 * 3);

    // (0, 0) — красный
    img.set(0, 0, 255, 0);
    img.set(0, 0, 0,   1);
    img.set(0, 0, 0,   2);

    // (1, 1) — синий
    img.set(1, 1, 0,   0);
    img.set(1, 1, 0,   1);
    img.set(1, 1, 255, 2);

    saveImagePNG("test.png", img);
    return 0;
}