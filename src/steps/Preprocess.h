#pragma once

#include "Config.h"
#include "Image.h"
#include "ProcessingStep.h"

class Preprocess : public ProcessingStep {
public:
    Preprocess(const Image& inputImage, Image& outputImage, const Config& config);
    void process() override;
    
    Image scaleImage(const Image& inputImage);
    Image blurImage(Image& image);

private:
    void grayScaleImage();
    void greenScaleImage();
    void maxGradientImage();

    const Image& inputImage;
    Image outputImage;
    const Config& config;
};