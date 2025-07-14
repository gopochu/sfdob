#pragma once

#include <filesystem>

#include "Config.hpp"
#include "ROI.hpp"
#include "image.hpp"
#include "ROI.hpp"

namespace fs = std::filesystem;

class Preprocess {
public:
    Preprocess();
    void run();

private:
    fs::path path;
    Config config;

    ROI roi;
    Image workImage, etalonImage, maskImage;
    Image grayscaleImage();


};