#pragma once

#include <array>

struct Config {
    int blurRadius = 1000; // радиус размытия
    int gradient_offset = 2;
    
    // 0 - зелёный, 1 - усреднённый, 2 - максимальный по цветам
    int colorMode = 1;
    
    // количество направлений для поиска точек
    int numDirections = 2;

    // толщина линиий
    // std::vector<int> tikness = {3, 5};
    std::array<int, 3> tikness = {3, 4, 5};
    // int tikness = 5;

    // порог темноты
    int darknessThreshold = 10; 
};