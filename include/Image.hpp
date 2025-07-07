#pragma once

#include <vector>
#include <stdint.h>

struct Image {
    int width, height, channels;
    
    Image();
    Image(int width, int height, int channels);

    //Храним значение всех пикселей по каналам
    //255, 0, 0,     Pixel 1: Red
    //0, 255, 0,     Pixel 2: Green
    //0, 0, 255      Pixel 3: Blue
    //Каждый канал имеет значение от 0 до 255, ровно 1 байт (8 бит)
    std::vector<uint8_t> data;
    
    //index = (y * width + x) * channels + c, где c - номер канала (0 - R, 1 - G, 2 - B)
    //Например для изображения 2x2
    //R (0,0); index = (0 * 2 * 0) * 3 + 0 = 0
    //G (1,0); index = (0 * 2 + 1) * 3 + 1 = 4
    //B (0,1); index = (1 * 2 + 0) * 3 + 2 = 8
    uint8_t get(int x, int y, int c = 0) const;

    // Устанавливаем для каждого пикселя цвета
    // Например, в кооржинату (0, 0) устанавливаем красный цвет.
    // Для этого в системе RGB задаём максимальное значение для красного цвета, и ноль для остальных цветов
    // img.set(0, 0, 255, 0);
    // img.set(0, 0, 0,   1);
    // img.set(0, 0, 0,   2);
    void set(int x, int y, uint8_t value, int c = 0);

    // Просто более удобная обёртка для set
    void setRGB(int x, int y, uint8_t r, uint8_t g, uint8_t b);
};