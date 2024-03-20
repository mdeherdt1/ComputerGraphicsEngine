//
// Created by student on 13/03/24.
//

#ifndef ENGINE_PLATONISCHELICHAMEN_H
#define ENGINE_PLATONISCHELICHAMEN_H

#include "Figure.h"
#include <cmath>
#include "easy_image.h"
#include "ini_configuration.h"

void confgCube(double& rotateX, double& rotateY, double& rotateZ, double& scale, Vector3D& center, const ini::Configuration &configuration, std::string figureString);
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

void applyAllTransformations(Figure& figure, double scaleFactor, double rotateX, double rotateY, double rotateZ, Vector3D center);

#endif //ENGINE_PLATONISCHELICHAMEN_H
