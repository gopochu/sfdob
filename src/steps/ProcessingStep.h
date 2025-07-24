#pragma once

#include "Image.h"
#include "Config.h"

class ProcessingStep {
public:
    virtual ~ProcessingStep() = default;
    virtual void process() = 0;

private:
    const Config config;
};