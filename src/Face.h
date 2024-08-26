//
// Created by student on 1/03/24.
//

#ifndef ENGINE_FACE_H
#define ENGINE_FACE_H
#include "vector"


class Face {
public:
    std::vector<int> point_indexes;

    explicit Face(const std::vector<int> &pointIndexes);

    std::vector<Face> triangulate();
};


#endif //ENGINE_FACE_H
