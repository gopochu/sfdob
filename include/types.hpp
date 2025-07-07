#pragma once

#include <vector>

struct Point {
    int x, y;
};

struct ROI {
    int x_min, x_max;
    int y_min, y_max;
};

struct DefectInfo {
    Point coords;
    double magnitude; // Величина дефекта
    Point direction; // Направление наибольшего перепада (dx, dy)
    double thickness; // Вычисленная толщина линии
};

struct ComponentInfo {
    int id;
    ROI bbox; // Bounding box компоненты
    int num_points;
    double total_defect_value;
    std::vector<Point> points; // Опционально, для отладки или визуализации
};