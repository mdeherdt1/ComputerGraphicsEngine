//
// Created by DH Services BVBA on 3/20/2024.
//

#ifndef ENGINE_WIREFRAMES_H
#define ENGINE_WIREFRAMES_H
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
#include "draw3DLsystem.h"
#include "ZBuffer.h"

Figures3D configure3D(const ini::Configuration &confg, int& size, img::Color &backGroundColor, Vector3D &eyeCords);
img::EasyImage CreateZBufferedWireframe(const ini::Configuration &configuration, int size);


#endif //ENGINE_WIREFRAMES_H
