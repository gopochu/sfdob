#include "Process.hpp"

#include <iostream>
#include <fstream>

Process::Process(const fs::path& path, const Config& config, int numThreads)
    : path(path), config(config), numThreads(numThreads) {
    
}

void Process::process() {}

bool Process::loadData() {
    if (!fs::exists(path)) {
        std::cerr << "ERROR: Data directory does not exist: " << path << std::endl;
    }
    if(!workImage.load((path / "work.png").string())) return false;
    if(!etalonImage.load((path / "etalon.png").string())) return false;
    if(!maskImage.load((path / "mask.png").string())) return false;
    
    std::fstream roi((path / "roi.txt").string());
    if(roi.is_open()) {
        int x, y, w, h;
        roi >> x >> y >> w >> h;
        roi.close();
        this->roi = Rect(x, y, w, h);
    } else {
        std::cerr << "ERROR: Could not open ROI file." << std::endl;
        return false;
    }
    return true;
}