//
// Created by DH Services BVBA on 3/20/2024.
//

#ifndef ENGINE_ZBUFFERING_H
#define ENGINE_ZBUFFERING_H
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

img::EasyImage CreateZBufferedWireframe(const ini::Configuration &configuration, int size);


#endif //ENGINE_ZBUFFERING_H
