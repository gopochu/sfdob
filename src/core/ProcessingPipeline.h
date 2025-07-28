#pragma once

#include "ProcessingStep.h"
#include "Config.h"
#include "Types.h"
#include "Image.h"

#include <filesystem>
#include <chrono>

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
    Rect roi;

    std::chrono::time_point<std::chrono::high_resolution_clock> end;
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    
    void stopTimer();
    void startTimer();

    bool loadData();
    void saveResult() const;
    void printResults() const;
};