#include "PointDetector.hpp"
#include "Types.hpp"
#include <thread>
#include <vector>
#include <algorithm>

PointDetector::PointDetector(const Image& workImage, const Image& referenceImage, const Image& maskImage, Image& defectMap, const Rect& roi, const Config& config, const int numThreads)
    : workImage(workImage), referenceImage(referenceImage), maskImage(maskImage), defectMap(defectMap), roi(roi), config(config), numThreads(numThreads) {};

void PointDetector::process() {
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    int rowsPerThread = roi.height / numThreads;

    for (int i = 0; i < numThreads; ++i) {
        int startRow = roi.y + i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? roi.y + roi.height: startRow + rowsPerThread;
        threads.emplace_back(&PointDetector::processRoiChunk, this, startRow, endRow);
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

void PointDetector::processRoiChunk(int startRow, int endRow) {
    std::vector<Point> directions = {{1,0 }, {0, 1}};
    if (config.numDirections == 4) {
        directions.push_back({-1, 1});
        directions.push_back({1, -1});
    }

    int max_offset = config.offsets.empty() ? 0 : *std::max_element(config.offsets.begin(), config.offsets.end());

    for (int y = startRow; y < endRow; ++y) {
        for (int x = roi.x; x < roi.x + roi.width; ++x) {
            if (workImage.is_valid(x + max_offset, y + max_offset) || !workImage.is_valid(x - max_offset, y - max_offset)) continue;
            if (maskImage.at(x, y, 0) == 0) continue;
            
            int referenceImageLightness = referenceImage.at(x, y, 0);
            if (referenceImageLightness < config.darknessThreshold) continue;
            auto getPixelValue = [&](const Image& img, int px, int py) {
                switch (config.colorMode) {
                    case 1 : return (img.at(px, py, 0) + img.at(px, py, 1) + img.at(px, py, 2));
                    case 2 : return (img.at(px, py, 0) / 4 + img.at(px, py, 1) / 2 + img.at(px, py, 2) / 4);
                    default: return int(img.at(px, py, 1));
                }
            };
            int workImageLightness = getPixelValue(workImage, x, y);
            int lineDefectValue = 0;
            int blotchDefectValue = 0;

            for (int offset : config.offsets) {
                for (const auto& direction : directions) {
                    int val1 = getPixelValue(workImage, x + direction.x * offset, y + direction.y * offset);
                    int val2 = getPixelValue(workImage, x - direction.x * offset, y - direction.y * offset);
                    int diff = std::min(val1, val2) - workImageLightness;
                    if (diff > lineDefectValue) lineDefectValue = diff;
                }
            }

            blotchDefectValue = referenceImageLightness - workImageLightness;
            lineDefectValue = referenceImage.at(x, y, 1);
            int resultDefectValue = std::max(lineDefectValue, blotchDefectValue);

            if (resultDefectValue > config.darknessThreshold) {
                defectMap.at(x, y, 0) = std::min(255, resultDefectValue);
            }
        }
    }
}