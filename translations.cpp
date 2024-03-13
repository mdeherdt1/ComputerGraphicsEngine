//
// Created by student on 13/03/24.
//
#define _USE_MATH_DEFINES
#include "translations.h"


//
// Created by student on 13/03/24.
//
#define USE_MATH_DEFINES

#include "easy_image.h"
#include "Point2D.h"
#include "Line2D.h"
#include "vector3d.h"
#include "Figure.h"
#include "Face.h"

#include <cmath>

Matrix scaleFigure(const double scale){
    Matrix scaleMatrix = Matrix(); //matrix() maakt een 4x4 matrix aan met alle waarden op 0
    scaleMatrix(1,1) = scale;
    scaleMatrix(2,2) = scale;
    scaleMatrix(3,3) = scale;
    scaleMatrix(4,4) = 1;
    return scaleMatrix;
}

Matrix RotateX(const double angle){
    double rad = angle * (M_PI / 180.0);
    Matrix rotateMatrix = Matrix();
    rotateMatrix(1,1) = 1;
    rotateMatrix(2,2) = cos(rad);
    rotateMatrix(2,3) = sin(rad);
    rotateMatrix(3,2) = -sin(rad);
    rotateMatrix(3,3) = cos(rad);
    rotateMatrix(4,4) = 1;
    return rotateMatrix;
}

Matrix RotateY(const double angle){
    double rad = angle * (M_PI / 180.0);
    Matrix rotateMatrix = Matrix();
    rotateMatrix(1,1) = cos(rad);
    rotateMatrix(1,3) = -sin(rad);
    rotateMatrix(2,2) = 1;
    rotateMatrix(3,1) = sin(rad);
    rotateMatrix(3,3) = cos(rad);
    rotateMatrix(4,4) = 1;
    return rotateMatrix;
}

Matrix RotateZ(const double angle){
    double rad = angle * (M_PI / 180.0);
    Matrix rotateMatrix = Matrix();
    rotateMatrix(1,1) = cos(rad);
    rotateMatrix(1,2) = sin(rad);
    rotateMatrix(2,1) = -sin(rad);
    rotateMatrix(2,2) = cos(rad);
    rotateMatrix(3,3) = 1;
    rotateMatrix(4,4) = 1;
    return rotateMatrix;
}

Matrix translate(const Vector3D &vector){
    Matrix translateMatrixback = Matrix();
    translateMatrixback(4, 1) = vector.x;
    translateMatrixback(4, 2) = vector.y;
    translateMatrixback(4, 3) = vector.z;
    return translateMatrixback;
}

void applyTransformation(Figure &fig, const Matrix &m) {
    for(auto &point:fig.points){
        point =  point * m;
    }
}
void toPolar(const Vector3D &point, double &r, double &theta, double &phi){
    r = sqrt(pow(point.x,2) + pow(point.y,2) + pow(point.z,2));
    theta = atan2(point.y,point.x);
    phi = acos(point.z/r);
}

Matrix eyePointTrans(const Vector3D &eyepoint){
    double r, theta, phi;
    toPolar(eyepoint, r, theta, phi);
    // Creëer een identiteitsmatrix voor eyePointMatrix
    Matrix eyePointMatrix2 = Matrix();
    eyePointMatrix2(1,1) = -sin(theta);
    eyePointMatrix2(1,2) = -cos(theta)*cos(phi);
    eyePointMatrix2(1,3) = cos(theta)*sin(phi);
    eyePointMatrix2(2,1) = cos(theta);
    eyePointMatrix2(2,2) = -sin(theta)*cos(phi);
    eyePointMatrix2(2,3) = sin(theta)*sin(phi);
    eyePointMatrix2(3,2) = sin(phi);
    eyePointMatrix2(3,3) = cos(phi);
    eyePointMatrix2(4,3) = -r;
    eyePointMatrix2(4,4) = 1;
    return  eyePointMatrix2 ;
}

void applyTransformation(Figures3D &figs, const Matrix &m){
    for(Figure &fig:figs){
        applyTransformation(fig, m);
    }
}

Point2D doProjection(const Vector3D &point, const double d){
    return Point2D(-point.x * d / point.z, -point.y * d / point.z);
}

Lines2D doProjection(const Figures3D &figures){
    Lines2D lines;
    for(const Figure &fig:figures){
        for(const Face &face:fig.faces){
            for(unsigned int i = 0; i < face.point_indexes.size(); ++i){
                Vector3D point1 = fig.points[face.point_indexes[i]];
                Vector3D point2 = fig.points[face.point_indexes[(i+1)%face.point_indexes.size()]];
                lines.push_back(Line2D(doProjection(point1), doProjection(point2), fig.color));
            }
        }
    }
    return lines;
}