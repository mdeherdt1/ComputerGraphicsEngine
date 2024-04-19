//
// Created by student on 13/03/24.
//

#ifndef ENGINE_PLATONISCHELICHAMEN_H
#define ENGINE_PLATONISCHELICHAMEN_H

#include "Figure.h"
#include <cmath>
#include "easy_image.h"
#include "ini_configuration.h"

void configFigure(double& rotateX, double& rotateY, double& rotateZ, double& scale, Vector3D& center, const ini::Configuration &confg, std::string figureString);

void createCube(Figure& figure);

void createTetrahedron(Figure& figure);

void createOctahedron(Figure& figure);

void createIcosahedron(Figure& figure);

void createDodecahedron(Figure& figure);

void createCone(Figure& figure, const int n, const double h);

void configCylinder(double& rotateX, double& rotateY, double& rotateZ, double& scale, Vector3D& center, const ini::Configuration &confg, std::string figureString, double& h, int& n);
void createCylinder(Figure& figure, const int n, const double h);

int findOrAddPoint(Figure &figure, Vector3D point);

void subdivide(Figure &figure, int n);

void configSphere(double& rotateX, double& rotateY, double& rotateZ, double& scale, Vector3D& center, const ini::Configuration &confg, std::string figureString, int& n);
void createSphere(Figure& figure, const int n);

void configTorus(double& rotateX, double& rotateY, double& rotateZ, double& scale, Vector3D& center, const ini::Configuration &confg, std::string figureString, double& R, int& r, int& n, int& m);
void createTorus(Figure& figure,  int n,  int m,  double R,  double r);

void applyAllTransformations(Figure& figure, double scaleFactor, double rotateX, double rotateY, double rotateZ, Vector3D center);

void calculateTotalMatrix(Figure& fig);

void configFigureTranslations(Figure &figure, double rotateX, double rotateY, double rotateZ, double scale, Vector3D center, Vector3D eyeCords);



//voor de fractalen
void configFigureFractal(double& rotateX, double& rotateY, double& rotateZ, double& scale, Vector3D& center, const ini::Configuration &confg, std::string figureString, int &nr_iterations, double &scaleFactor);
void generateFractal(Figure &fig, Figures3D &fractal, const int nr_iterations, const double scale);
#endif //ENGINE_PLATONISCHELICHAMEN_H
