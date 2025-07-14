#pragma once

#include "ProcessingStep.h"
#include "Config.hpp"
#include "ROI.hpp"

#include <filesystem>

namespace fs = std::filesystem;
class Process : ProcessingStep {
public:
    Process(const fs::path& path, const Config& config, int numThreads);
    void process() override;
private:
    fs::path path;
    Config config;
    int numThreads;

    // Данные
    Image etalonImage, workImage, maskImage;
    ROI roi;


    void processImage(const fs::path& imagePath);
    bool loadData();
    void saveData() const;
    void printResults() const;
};