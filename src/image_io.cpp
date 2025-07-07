#include "image_io.hpp"
#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdexcept>

Image image_io::load(const std::string& filename) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &channels, 0);
    
    if (!data) {
        throw std::runtime_error("Failed to load image: " + filename);
    }

    Image img(width, height, channels);

    std::copy(data, data + (static_cast<size_t>(width) * height * channels), img.data.begin());
    stbi_image_free(data);
    return img;
}

void image_io::save(const Image& image, const std::string& filename) {
    //TODO: Доделать
    int result = stbi_write_png(filename.c_str(), image.width, image.height, image.channels, image.data.data(), image.width * image.channels);
    if (result == 0) {
        throw std::runtime_error("Failed to save image: " + filename);
    }
}