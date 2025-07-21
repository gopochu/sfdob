#pragma once

#include "ProcessingStep.h"
#include "Types.h"
#include "Image.h"
#include "Config.h"

class PointDetector : ProcessingStep {
public:
    PointDetector(const Image& workImage, const Image& referenceImage, const Image& maskImage, Image& defectMap, const Rect& roi, const Config& config, const int numThreads);
    void process() override;
private:
    void processRoiChunk(int startY, int endY);

    const Image& workImage;
    const Image& referenceImage;
    const Image& maskImage;
    Image& defectMap;
    const Rect& roi;
    const Config& config;
    int numThreads;
};