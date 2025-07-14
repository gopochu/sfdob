#pragma once

#include "Types.hpp"
#include "Image.hpp"
#include "Config.hpp"

class ProcessingStep {
public:
    virtual ~ProcessingStep() = default;
    virtual void process() = 0;
};