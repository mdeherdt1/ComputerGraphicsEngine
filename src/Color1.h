//
// Created by student on 21/02/24.
//

#ifndef ENGINE_COLOR1_H
#define ENGINE_COLOR1_H


class Color1 {
public:
    double red;
    double green;
    double blue;

    Color1(double red, double green, double blue);

    Color1();

    //Color1 operator+(const Color1 &c) const;

    //add == operator
    friend bool operator==(const Color1 &c1, const Color1 &c2);
};


#endif //ENGINE_COLOR1_H
