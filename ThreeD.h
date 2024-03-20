//
// Created by DH Services BVBA on 3/20/2024.
//

#ifndef ENGINE_THREED_H
#define ENGINE_THREED_H
#include "Figure.h"
#include "translations.h"
#include "PlatonischeLichamen.h"
#include "draw3DLsystem.h"
#include "ZBuffer.h"
#include "easy_image.h"
#include "ini_configuration.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "introduction.h"
#include "l_parser.h"
#include "vector3d.h"
#include "Face.h"
#include <set>

class ThreeD {
private:
    Figures3D figures3D;
    Matrix allTransformations;

    Matrix SchaalMatrix(double schaalFactor);
    Matrix RotateXMatrix(double hoek);
    Matrix RotateYMatrix(double hoek);
    Matrix RotateZMatrix(double hoek);
    Matrix TranslateMatrix(double x, double y, double z);






public:
    ThreeD();


};


#endif //ENGINE_THREED_H
