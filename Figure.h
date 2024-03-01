//
// Created by student on 1/03/24.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H
#include "vector3d.h"
#include "vector"
#include "Color.h"
#include "Face.h"

class Figure {


public:
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    Color color;

    explicit Figure(const Color &color);
};
typedef std::vector<Figure> Figures3D;

#endif //ENGINE_FIGURE_H
