//
// Created by DH Services BVBA on 4/1/2024.
//

#ifndef ENGINE_ZBUFFERING_H
#define ENGINE_ZBUFFERING_H
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

img::EasyImage zBuffering(const ini::Configuration &confg);

img::EasyImage drawTriangulateFaces(Figures3D figures, int size, img::Color bgColor, Vector3D eyeCords, bool buffer);

void doTriangulation(Figures3D &figures, img::EasyImage &image, ZBuffer &zbuf, double d, double dx, double dy);

std::vector<Face> triangulate(const Face face);

void draw_zbuf_triangle(ZBuffer &zbuf, Vector3D &v0, Vector3D &v1, Vector3D &v2, double d, double dx, double dy, Color1 color);



#endif //ENGINE_ZBUFFERING_H
