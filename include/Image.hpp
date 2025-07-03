#include <vector>
#include <stdint.h>

struct Image {
    int width, height, channels;
    std::vector<uint8_t> data;
    uint8_t get(int x, int y, int c = 0) const;
    void set(int x, int y, uint8_t value, int c = 0);
};

