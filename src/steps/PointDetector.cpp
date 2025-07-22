#include "PointDetector.h"
#include "Preprocess.h"
#include "Types.h"

#include <thread>
#include <vector>
#include <algorithm>
#include <stdexcept>

PointDetector::PointDetector(const Image& workImage, const Image& referenceImage, const Image& maskImage, Image& defectMap, const Rect& roi, const Config& config, const int numThreads)
    : workImage(workImage), referenceImage(referenceImage), maskImage(maskImage), defectMap(defectMap), roi(roi), config(config), numThreads(numThreads) {};

void PointDetector::process() {
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    int rowsPerThread = roi.height / numThreads;

    // Если количество строк не делится на количество потоков, последний поток обработает оставшиеся строки
    for (int i = 0; i < numThreads; ++i) {
        // Определяем диапазон строк для каждого потока
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
    if (startRow < roi.y || endRow > roi.y + roi.height) {
        throw std::out_of_range("Row range is out of bounds of the ROI");
    }
    // Вертикальное и горизонтальное направление
    // std::vector<Point> directions = {{1,0 }, {0, 1}};
    std::array<Point, 4> directions = {Point{1, 0}, Point{0, 1}, Point{-1, 1}, Point{1, -1}};

    // Preprocess preprocess(referenceImage, defectMap, config);
    defectMap.save_png("defect_mapPreprocessed.png");

    for (int y = startRow; y < endRow; ++y) {
        for (int x = roi.x; x < roi.x + roi.width; ++x) {
            int referenceImageLightness = referenceImage.at(x, y, 0);
            if (referenceImageLightness < config.darknessThreshold) continue;

            int lineDefectValue = 0;
            int blotchDefectValue = 0;
            int workImageLightness = workImage.at(x, y, 0);

            for (int offset : config.tikness) {
                for (int i = 0; i < config.numDirections; ++i) {
                    const Point& direction = directions[i];
                    int val1 = workImage.at(x + direction.x * offset, y + direction.y * offset, 0);
                    int val2 = workImage.at(x - direction.x * offset, y - direction.y * offset, 0);
                    
                    int diff = std::min(val1, val2) - workImageLightness;
                    if (diff > lineDefectValue) lineDefectValue = diff;
                }
            }

            blotchDefectValue = referenceImageLightness - workImageLightness;
            // lineDefectValue = referenceImage.at(x, y, 1);
            int resultDefectValue = std::max(lineDefectValue, blotchDefectValue);

            if (resultDefectValue > config.darknessThreshold) {
                defectMap.at(x, y, 0) = std::min(255, resultDefectValue);
            }
        }
    }
}