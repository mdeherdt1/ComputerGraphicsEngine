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

    Color1 ambientReflection;
    Color1 diffuseReflection;
    Color1 specularReflection;

    double reflectionCoefficient;


    Matrix totalMatrix;
    bool firstTime = true;

    double rotateX;
    double rotateY;
    double rotateZ;
    double scale;
    Vector3D center;
    Vector3D eyePoint;
    Matrix eyepointMatrix;

    bool fractal = false;

    explicit Figure(const Color1 &color);

    Figure();

    Figure copy();
};
typedef std::vector<Figure> Figures3D;


#endif //ENGINE_FIGURE_H
