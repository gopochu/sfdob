#pragma once

#include "ProcessingStep.h"
#include "Types.hpp"
#include "Image.hpp"

class PointDetector : ProcessingStep {
public:
    PointDetector(const Image& workImage, const Image& referenceImage, const Image& maskImage, Image& defectMap, const Rect& roi, const Config& config, const int numThreads);
    void process() override;
private:
    void processRoiChunk(int startY, int endY);

    Image workImage;
    Image referenceImage;
    Image maskImage;
    Image defectMap;
    Rect roi;
    Config config;
    int numThreads;
};