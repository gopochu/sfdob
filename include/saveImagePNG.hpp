#pragma once

#include <string>

#include "image.hpp"
#include "stb_image_write.h"

void saveImagePNG(const std::string& path, Image image) {
    stbi_write_png(path.c_str(), image.width, image.height, image.channels, image.data.data(), image.width * image.channels);
}
