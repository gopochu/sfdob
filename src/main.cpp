#include "Config.h"
#include "ProcessingPipeline.h"

namespace fs = std::filesystem;

int main() {
    fs::path dataPath = "../data";
    Config config;
    Process process(dataPath, config, 4);
    process.process();
}