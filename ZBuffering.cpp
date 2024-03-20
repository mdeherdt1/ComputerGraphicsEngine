//
// Created by DH Services BVBA on 3/20/2024.
//

#include "ZBuffering.h"

img::EasyImage CreateZBufferedWireframe(const ini::Configuration &configuration, int size) {
    std::vector<double> backgroundcolor = configuration["General"]["backgroundcolor"].as_double_tuple_or_die();
    Color background = Color(backgroundcolor[0], backgroundcolor[1], backgroundcolor[2]);


}


