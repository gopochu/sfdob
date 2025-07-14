#include "Config.hpp"
#include "Preprocess.hpp"

int main() {
    Image inputImage;
    inputImage.load("C:/programming/C++/sfdob/testdata/etalon.png");
    // Image outputImage(inputImage.width, inputImage.height, 2);
    Image outputImage = inputImage;
    outputImage.save_png("C:/programming/C++/sfdob/testdata/res.png");
    Config config;
    Preprocess pr(inputImage, outputImage, config);
    pr.process();
    outputImage.save_png("C:/programming/C++/sfdob/testdata/result.png");
}