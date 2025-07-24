#include "PointDetector.h"
#include "Types.h"

#include <thread>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

PointDetector::PointDetector(const Image& workImage, const Image& referenceImage, const Image& maskImage, Image& defectMap, const Rect& roi, const Config& config, const int numThreads, Image& etalonMap)
    : workImage(workImage), referenceImage(referenceImage), maskImage(maskImage), defectMap(defectMap), roi(roi), config(config), numThreads(numThreads), etalonMap(etalonMap) {};

void PointDetector::process() {
    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    int rowsPerThread = roi.height / numThreads;

    int startRow;
    int endRow;

    // Если количество строк не делится на количество потоков, последний поток обработает оставшиеся строки
    for (int i = 0; i < numThreads; ++i) {
        // Определяем диапазон строк для каждого потока
        startRow = roi.y + i * rowsPerThread;
        endRow = (i == numThreads - 1) ? roi.y + roi.height: startRow + rowsPerThread;
        threads.emplace_back(&PointDetector::processRoiChunk, this, startRow, endRow);
    }

    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    processEtalonChunk(248, 1282);
}



void PointDetector::processRoiChunk(int startRow, int endRow) {
    if (startRow < roi.y || endRow > roi.y + roi.height) {
        throw std::out_of_range("Row range is out of bounds of the ROI");
    }
    // Вертикальное и горизонтальное направление
    // std::vector<Point> directions = {{1,0 }, {0, 1}};
    std::array<Point, 4> directions = {Point{1, 0}, Point{0, 1}, Point{-1, 1}, Point{1, -1}};

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

void PointDetector::processEtalonChunk(int startRow, int endRow) {
    std::cout << "Etalon chunk: " << startRow << " to " << endRow << std::endl;
    std::cout << "ROI y: " << roi.y << ", height: " << roi.height << std::endl;

    if (startRow < roi.y || endRow > roi.y + roi.height) {
        throw std::out_of_range("Row range is out of bounds of the ROI");
    }

    std::array<Point, 4> directions = {Point{1, 0}, Point{0, 1}, Point{-1, 1}, Point{1, -1}};

    for (int y = startRow; y < endRow; ++y) {
        for (int x = roi.x; x < roi.x + roi.width; ++x) {
            int etalonLightness = referenceImage.at(x, y, 1); // <-- канал 1, как ты хочешь

            if (etalonLightness < config.darknessThreshold) continue;

            int lineDefectValue = 0;

            for (int offset : config.tikness) {
                for (int i = 0; i < config.numDirections; ++i) {
                    const Point& direction = directions[i];
                    int val1 = referenceImage.at(x + direction.x * offset, y + direction.y * offset, 1);
                    int val2 = referenceImage.at(x - direction.x * offset, y - direction.y * offset, 1);

                    int diff = std::min(val1, val2) - etalonLightness;
                    if (diff > lineDefectValue) lineDefectValue = diff;
                }
            }

            if (lineDefectValue > config.darknessThreshold) {
                etalonMap.at(x, y, 0) = std::min(255, lineDefectValue);  // В канал 0
            }
        }
    }
}

