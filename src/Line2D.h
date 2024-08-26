//
// Created by student on 21/02/24.
//

#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H
#include "Point2D.h"
#include "Color1.h"
#include <vector>


class Line2D {
public:
    Point2D p1;
    Point2D p2;
    Color1 color;

    double z1 = p1.z;
    double z2 = p2.z;

    bool draw = true;

    Line2D(const Point2D &p1, const Point2D &p2, const Color1 &color);

};

using Lines2D = std::vector<Line2D>;

#endif //ENGINE_LINE2D_H
