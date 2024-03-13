//
// Created by student on 13/03/24.
//

#ifndef ENGINE_PLATONISCHELICHAMEN_H
#define ENGINE_PLATONISCHELICHAMEN_H

#include "Figure.h"
#include <cmath>


void createCube(Figure& figure);

void createTetrahedron(Figure& figure);

void createOctahedron(Figure& figure);

void createIcosahedron(Figure& figure);

void createDodecahedron(Figure& figure);

void createCone(Figure& figure, const int n, const double h);

void createCylinder(Figure& figure, const int n, const double h);

int findOrAddPoint(Figure &figure, Vector3D point);

void subdivide(Figure &figure, int n);

void createSphere(Figure& figure, const int n);

void createTorus(Figure& figure, const int n, const int m, const double R, const double r);



#endif //ENGINE_PLATONISCHELICHAMEN_H
