//
// Created by student on 1/03/24.
//

#include "Figure.h"

Figure::Figure(const Color1 &color) : color(color) {}

Figure Figure::copy() {
    Figure figure = Figure(color);
    figure.points = points;
    figure.faces = faces;
    figure.color = color;
    figure.rotateX = rotateX;
    figure.rotateY = rotateY;
    figure.rotateZ = rotateZ;
    return figure;
}

Figure::Figure() {}
