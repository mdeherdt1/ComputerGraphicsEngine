//
// Created by student on 13/03/24.
//

#ifndef ENGINE_TRANSLATIONS_H
#define ENGINE_TRANSLATIONS_H
#define USE_MATH_DEFINES

#include "easy_image.h"
#include "ini_configuration.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "introduction.h"
#include "l_parser.h"
#include "vector3d.h"
#include "Figure.h"
#include "Face.h"
#include "PlatonischeLichamen.h"

#include <set>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <ctime>

Matrix scaleFigure(const double scale);

Matrix RotateX(const double angle);

Matrix RotateY(const double angle);

Matrix RotateZ(const double angle);

Matrix translate(const Vector3D &vector);

void applyTransformation(Figure &fig, const Matrix &m);

void toPolar(const Vector3D &point, double &r, double &theta, double &phi);

Matrix eyePointTrans(const Vector3D &eyepoint);

void applyTransformation(Figures3D &figs, const Matrix &m);

Point2D doProjection(const Vector3D &point, const double d = 1.0);

Lines2D doProjection(const Figures3D figuren3D);


#endif //ENGINE_TRANSLATIONS_H
