//
// Created by DH Services BVBA on 3/20/2024.
//

#include "ZBuffer.h"

ZBuffer::ZBuffer(const int width, const int height) {
    double inf = std::numeric_limits<double>::infinity();
    v = vector<std::vector<double>>(width, vector<double>(height, inf));
}
