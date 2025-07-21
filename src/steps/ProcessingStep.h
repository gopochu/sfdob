#pragma once

#include "Image.h"
#include "Config.h"

class ProcessingStep {
public:
    virtual ~ProcessingStep() = default;
    virtual void process() = 0;
    // Image grayScaleImage(const Image& inputImage);
    // Image greenScaleImage(const Image& inputImage);

private:
    // const Image inputImage;
    // Image outputImage;
    const Config config;
};