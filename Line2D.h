//
// Created by student on 21/02/24.
//

#ifndef ENGINE_LINE2D_H
#define ENGINE_LINE2D_H
#include "Point2D.h"
#include "Color.h"
#include <vector>


class Line2D {
public:
    Point2D p1;
    Point2D p2;
    Color color;

    Line2D(const Point2D &p1, const Point2D &p2, const Color &color);

};

using Lines2D = std::vector<Line2D>;

#endif //ENGINE_LINE2D_H
