//
// Created by student on 21/02/24.
//

#ifndef ENGINE_INTRODUCTION_H
#define ENGINE_INTRODUCTION_H
#include "easy_image.h"
#include "ini_configuration.h"
#include "iostream"
#include "string"


img::EasyImage ColorRectangle(const std::string &type,const int &w, const int &h);


img::EasyImage Blocks(const std::string &type, const int &w, const int &h, const ini::DoubleTuple &cw, const ini::DoubleTuple &cb, const int &nxB, const int &nyB, bool &invert );

img::EasyImage QuarterCircle(const ini::DoubleTuple backGroundColor, const ini::DoubleTuple lineColor, int nrLines, const int height, const int width);


img::EasyImage Eye(ini::DoubleTuple backGroundColor, ini::DoubleTuple lineColor, int nrLines, int height, int width);

img::EasyImage Diamond(ini::DoubleTuple backGroundColor, ini::DoubleTuple lineColor, int nrLines, int height, int width);
#endif //ENGINE_INTRODUCTION_H
