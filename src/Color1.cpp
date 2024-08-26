//
// Created by student on 21/02/24.
//

#include "Color1.h"

Color1::Color1(double red, double green, double blue) : red(red), green(green), blue(blue) {}

Color1::Color1() {}

bool operator==(const Color1 &c1, const Color1 &c2) {
    return c1.red == c2.red && c1.green == c2.green && c1.blue == c2.blue;
}
