//
// Created by Mathis De Herdt on 24/04/2024.
//

#ifndef ENGINE_LIGHTEDZBUFFERING_H
#define ENGINE_LIGHTEDZBUFFERING_H
#include "vector3d.h"
#include "ZBuffering.h"
#include "Color1.h"
#include "Face.h"
#include "Figure.h"
#include "lightClass.h"
#include <list>
#include <vector>
#include <iostream>
#include <cmath>
#include "easy_image.h"
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
#include <limits>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <ctime>
#include <string>
#include "draw3DLsystem.h"
#include "Wireframes.h"
#include <algorithm>

img::EasyImage lightedZBuffering(const ini::Configuration &confg);

Lights3D configureLights(const ini::Configuration &confg, Matrix eyepointMatrix);

#endif //ENGINE_LIGHTEDZBUFFERING_H
