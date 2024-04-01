//
// Created by DH Services BVBA on 3/16/2024.
//

#ifndef ENGINE_DRAW3DLSYSTEM_H
#define ENGINE_DRAW3DLSYSTEM_H
#include "easy_image.h"
#include "ini_configuration.h"
#include "Color1.h"
#include "Point2D.h"
#include "Line2D.h"
#include "introduction.h"
#include "l_parser.h"
#include "vector3d.h"
#include "Figure.h"
#include "Face.h"
#include "PlatonischeLichamen.h"
#include "translations.h"
#include <set>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <ctime>
#include <string>
#include "Line2D.h"
#include "easy_image.h"
#include "ini_configuration.h"
#include "Color1.h"
#include "Point2D.h"
#include "Vector3D.h"

LParser::LSystem3D createLSystem3D(const ini::Configuration &configuration, std::string figureString, double& scaleFactor, double& rotateX, double& rotateY, double& rotateZ, Vector3D& center, Color1& kleur);

void drawLSystem3D(LParser::LSystem3D system3D, Figure &figure, Color1 kleur);


#endif //ENGINE_DRAW3DLSYSTEM_H


