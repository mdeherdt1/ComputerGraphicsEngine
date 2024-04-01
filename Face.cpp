//
// Created by student on 1/03/24.
//

#include "Face.h"


Face::Face(const std::vector<int> &pointIndexes) : point_indexes(pointIndexes) {}

std::vector<Face> Face::triangulate() {
    std::vector<Face> faces;
    for (int i = 1; i < point_indexes.size() - 1; i++) {
        faces.push_back(Face({point_indexes[0], point_indexes[i], point_indexes[i + 1]}));
    }
    return faces;
}
