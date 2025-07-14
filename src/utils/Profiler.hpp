#pragma once

#include <string>
#include <chrono>

class Profiler {
public:
    void start(const std::string& name) {
        auto startTimes = std::chrono::high_resolution_clock::now();
    }
    long long stop(const std::string& name) {
        auto endTime = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTimes).count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTimes;
};