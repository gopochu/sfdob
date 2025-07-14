#pragma once

#include <string>
#include <vector>
#include <cstdint>
 
class Image {
public:
    int width = 0, height = 0, channels = 0;
    std::vector<uint8_t> data;

    Image() = default;
    Image(int w, int h, int c);

    bool load(const std::string& path);
    void save_png(const std::string& path) const;

    unsigned char& at(int x, int y, int c);
    const unsigned char& at(int x, int y, int c) const;

    bool is_valid(int x, int y) const;
};
