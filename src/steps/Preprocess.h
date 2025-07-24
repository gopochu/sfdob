#pragma once

#include "Config.h"
#include "Image.h"
#include "ProcessingStep.h"

class Preprocess : public ProcessingStep {
public:
    Preprocess(Image& workImage, Image& etalonImage, const Config& config);
    void process() override;
    // void run(Image& workImage, Image& etalonImage);
    
    void scaleImage();
    void blurImage(Image& image);

private:
    void grayScaleImage(Image& img);
    void greenScaleImage(Image& img);
    void maxGradientImage(Image& img);

    Image& workImage;
    Image& etalonImage;
    const Config& config;
};