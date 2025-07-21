#include "Image.h"

// Подключаем stb_image для загрузки и сохранения изображений
// Реализация stb_image будет в main.cpp, чтобы избежать ошибок линковки
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <iostream>

Image::Image(int w, int h, int c) : width(w), height(h), channels(c), data(w * h * c, 0) {}

bool Image::load(const std::string& path) {
    unsigned char* img_data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    if (img_data == nullptr) {
        std::cerr << "ERROR: Could not load image " << path << ". Reason: " << stbi_failure_reason() << std::endl;
        return false;
    }
    data.assign(img_data, img_data + width * height * channels);
    stbi_image_free(img_data);
    return true;
}

void Image::save_png(const std::string& path) const {
    if (data.empty()) {
        std::cerr << "ERROR: Cannot save an empty image." << std::endl;
        return;
    }
    stbi_write_png(path.c_str(), width, height, channels, data.data(), width * channels);
}

unsigned char& Image::at(int x, int y, int c) {
    // Для максимальной производительности убраны проверки границ.
    // Вызывающий код должен гарантировать корректность координат.
    return data[(y * width + x) * channels + c];
}

const unsigned char& Image::at(int x, int y, int c) const {
    return data[(y * width + x) * channels + c];
}

bool Image::is_valid(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}
