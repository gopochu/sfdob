#pragma once

#include <vector>

struct Point {
    int x, y;
};

struct Rect {
    int x, y, width, height;
};

struct DefectInfo {
    Point coords;
    double magnitude; // Величина дефекта
    Point direction; // Направление наибольшего перепада (dx, dy)
    double thickness; // Вычисленная толщина линии
};

struct ComponentInfo {
    int id;
    // ROI bbox; // Bounding box компоненты
    int num_points;
    double total_defect_value;
    std::vector<Point> points; // Опционально, для отладки или визуализации
};

enum class ColorMode {
    GrayScaleImage,
    GreenImage,
    MaxColorProwlImage
};

struct Defect {
    Rect bounds;
    int pixel_count = 0;
    double total_magnitude = 0.0;
};