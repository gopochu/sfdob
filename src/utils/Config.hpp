#pragma once

#include <vector>

struct Config {
    int blurRadius = 4; // радиус размытия
    int gradient_offset = 2;
    
    // 0 - зелёный, 1 - усреднённый, 2 - максимальный по цветам
    int colorMode = 1;
    
    // количество направлений для поиска точек
    int numDirections = 2;

    // толщина линиий
    std::vector<int> offsets = {3, 5};

    // порог темноты
    int darknessThreshold = 10; 
};