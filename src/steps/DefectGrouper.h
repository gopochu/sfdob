#pragma once

#include "ProcessingStep.h"
#include "Types.h"
#include "Image.h"

class DefectGrouper : public ProcessingStep {
public:
    DefectGrouper(Image& defectMap, const Image& etalonMap, const Image& maskImage, const Rect& roi, std::vector<Defect> defects, const Config& config, Image& workImage);
    void process() override;
private:
    Image& workImage;
    const Image& defectMap;
    const Image& etalonMap;
    const Image& maskImage;
    std::vector<Defect> defects;
    const Rect& roi;
    const Config& config;
};