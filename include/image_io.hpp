#pragma once

#include "image.hpp"
#include "types.hpp"

#include <string>

namespace image_io {
    Image load(const std::string& filename);
    void save(const Image& image, const std::string& filename);
    void saveDefectImage(const Image& image, const std::string& filename, const std::vector<DefectInfo>& defects);
}