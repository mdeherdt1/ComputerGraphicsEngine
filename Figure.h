//
// Created by student on 1/03/24.
//

#ifndef ENGINE_FIGURE_H
#define ENGINE_FIGURE_H
#include "vector3d.h"
#include "vector"
#include "Color1.h"
#include "Face.h"

class Figure {


public:
    std::vector<Vector3D> points;
    std::vector<Face> faces;
    Color1 color;

    Matrix totalMatrix;
    bool firstTime = true;

    double rotateX;
    double rotateY;
    double rotateZ;
    double scale;
    Vector3D center;
    Vector3D eyePoint;

    explicit Figure(const Color1 &color);
};
typedef std::vector<Figure> Figures3D;


#endif //ENGINE_FIGURE_H
