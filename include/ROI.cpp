// #include "ROI.hpp"

// #include <iostream>
// #include <fstream>

// ROI::ROI(const std::filesystem::path& path) {
//     std::cout << "Loading ROI from: " << path << std::endl;
//     std::ifstream file(path);
//     if (!file) {
//         throw std::runtime_error("Failed to open ROI file: " + path.string());
//     }
//     std::ifstream(path) >> this->x_min >> this->x_max >> this->y_min >> this->y_max;
//     std::cout << "ROI loaded: x_min=" << x_min << ", x_max=" << x_max
//               << ", y_min=" << y_min << ", y_max=" << y_max << std::endl;
// }