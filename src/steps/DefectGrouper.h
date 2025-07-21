#pragma once

#include "ProcessingStep.h"
#include "Types.h"

class DefectGrouper : public ProcessingStep {
public:
    DefectGrouper(const Image& defectMap, const Rect& roi, std::vector<Defect> defects, const Config& config)
        : defectMap(defectMap), defects(defects),roi(roi), config(config) {}

    void process() override;
private:
    const Image& defectMap;
    std::vector<Defect> defects;
    const Rect& roi;
    const Config& config;
};