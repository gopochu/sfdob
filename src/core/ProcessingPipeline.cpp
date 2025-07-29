#include "ProcessingPipeline.h"
#include "DefectGrouper.h"
#include "Image.h"
#include "PointDetector.h"
#include "Preprocess.h"

#include <iostream>
#include <fstream>
#include <vector>

Process::Process(const fs::path& path, const Config& config, int numThreads)
    : path(path), config(config), numThreads(numThreads) {
    
}

void Process::process() {
    loadData();

    // TODO доделать blurImage, и сделать определение самих точек дефекта
    // И можно добавить отладку через #if
    // Так же сделать обход по маске

    Image defectMap = workImage;
    Image workImage1 = workImage;
    Preprocess preprocess(defectMap, etalonImage, config);
    preprocess.process();

    defectMap.save_png("Blured.png");

    Image tmpDefectMap(defectMap.width, defectMap.height, 1);
    Image etalonMap(etalonImage.width, etalonImage.height, 1);
        
    PointDetector pointDetector(workImage, etalonImage, maskImage, tmpDefectMap, roi,
        config, 4, etalonMap);
        
    pointDetector.process();

    std::vector<Defect> defectArr;
    DefectGrouper defectGrouper(tmpDefectMap, etalonMap, maskImage, roi, defectArr, config, workImage1);
    defectGrouper.process();

    workImage1.save_png("workImage1.png");
    defectMap.save_png("defect_map1.png");
    etalonMap.save_png("etalonMap.png");
    tmpDefectMap.save_png("tmpDefectMap1.png");
}

bool Process::loadData() {
    if (!fs::exists(path)) {
        std::cerr << "ERROR: Data directory does not exist: " << path << std::endl;
    }
    if(!workImage.load((path / "work.png").string())) return false;
    if(!etalonImage.load((path / "etalon_0.png").string())) return false;
    if(!maskImage.load((path / "work_mask.png").string())) return false;

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