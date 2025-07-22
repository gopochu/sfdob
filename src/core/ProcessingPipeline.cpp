#include "ProcessingPipeline.h"
#include "PointDetector.h"
#include "Preprocess.h"

#include <iostream>
#include <fstream>

Process::Process(const fs::path& path, const Config& config, int numThreads)
    : path(path), config(config), numThreads(numThreads) {
    
}

void Process::process() {
    loadData();

    // TODO Нужно передавать defectMap и etalonImage в processRoiChunk, и только затем сравнивать
    // Так же переделать preprocessor, так как process() безполезный и очень запутанный со всеми этими ссылками на ссылки
    // И можно добавить отладку через #if
    // Так же сделать обход по маске

    // Image defectMap(workImage.width, workImage.height, workImage.channels);
    Image defectMap = workImage;
    Preprocess preprocess(workImage, defectMap, config);

    etalonImage = preprocess.scaleImage(etalonImage);
    defectMap = preprocess.scaleImage(defectMap);
    defectMap.save_png("defect_map1.png");

    PointDetector pointDetector(workImage, etalonImage, maskImage, defectMap, roi, config, 4);
    pointDetector.process();

    defectMap.save_png("defect_map2.png");
    etalonImage.save_png("etalon_scaled.png");
}

bool Process::loadData() {
    if (!fs::exists(path)) {
        std::cerr << "ERROR: Data directory does not exist: " << path << std::endl;
    }
    if(!workImage.load((path / "work.png").string())) return false;
    else workImage.load((path / "work.png").string());
    if(!etalonImage.load((path / "etalon_0.png").string())) return false;
    else etalonImage.load((path / "etalon_0.png").string());
    if(!maskImage.load((path / "work_mask.png").string())) return false;
    else maskImage.load((path / "work_mask.png").string());

    std::ifstream roi((path / "etalon_roi.txt").string());
    if (!roi.is_open()) {
        std::cerr << "ERROR: Could not open ROI file." << std::endl;
        return false;
    }

    int left = 0, top = 0, right = 0, bottom = 0;
    std::string line;
    while (std::getline(roi, line)) {
        std::istringstream iss(line);
        std::string key;
        int value;
        if (std::getline(iss, key, '=') && (iss >> value)) {
            if (key == "left") left = value;
            else if (key == "top") top = value;
            else if (key == "right") right = value;
            else if (key == "bottom") bottom = value;
        }
    }
    roi.close();
    int x = left;
    int y = top;
    int w = right - left;
    int h = bottom - top;

    this->roi = Rect(x, y, w, h);

    return true;
}

void Process::startTimer() {
    auto start = std::chrono::high_resolution_clock::now();
}

void Process::stopTimer() {
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Processing time: " << duration.count() << " ms" << std::endl;
}