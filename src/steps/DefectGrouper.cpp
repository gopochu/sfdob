#include "DefectGrouper.h"
#include "Image.h"

DefectGrouper::DefectGrouper(Image& defectMap, const Image& etalonMap, const Image& maskImage, const Rect& roi, std::vector<Defect> defects, const Config& config, Image& workImage)
    : defectMap(defectMap), etalonMap(etalonMap), maskImage(maskImage), defects(defects), roi(roi), config(config), workImage(workImage){};

void DefectGrouper::process() {
    int numDifferences = 0;

    Image tmpDefectMap(defectMap.width, defectMap.height, 1);
    int gq = 60;
    for (int y = 0; y < defectMap.height; ++y) {
        for (int x = 0; x < defectMap.width; ++x) {
            // Проверка маски: если пиксель маски — белый (255), то пропускаем
            if (maskImage.at(x, y, 0) == 255) continue;

            int etalonValue = etalonMap.at(x, y, 0);
            int defectValue = defectMap.at(x, y, 0);

            if ((etalonMap.at(x, y, 0) - defectMap.at(x, y, 0) > gq || etalonMap.at(x, y, 0) - defectMap.at(x, y, 0) < -gq) &&
             (etalonMap.at(x, y, 1) - defectMap.at(x, y, 1) > gq || etalonMap.at(x, y, 1) - defectMap.at(x, y, 1) < -gq)  &&
              (etalonMap.at(x, y, 2) - defectMap.at(x, y, 2) > gq || etalonMap.at(x, y, 2) - defectMap.at(x, y, 2) < -gq)) {
                ++numDifferences;
                // Закрашиваем пиксель в красный
                // defectMap.at(x, y, 0) = 255; // R
                // defectMap.at(x, y, 1) = 0;   // G
                // defectMap.at(x, y, 2) = 0;   // B
                workImage.at(x, y, 0) = 255;
                workImage.at(x, y, 1) = 0;
                workImage.at(x, y, 2) = 0;
            }
        }
    }
}