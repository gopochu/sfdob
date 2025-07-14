#pragma once

#include "Config.hpp"
#include "Image.hpp"
#include "ProcessingStep.h"

class Preprocess : public ProcessingStep {
public:
    Preprocess(const Image& inputImage, Image& outputImage, const Config& config);
    void process() override;

private:
    const Image& inputImage;
    Image outputImage;
    Config config;
};