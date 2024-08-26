//
// Created by DH Services BVBA on 3/20/2024.
//

#ifndef ENGINE_ZBUFFER_H
#define ENGINE_ZBUFFER_H

#include "vector"
#include "limits"


class ZBuffer: public std::vector<std::vector<double>>
{
public:
    ZBuffer(const int width, const int height);
    std::vector<std::vector<double>> v;
};



#endif //ENGINE_ZBUFFER_H
