//
// Created by Mathis De Herdt on 24/04/2024.
//

#ifndef ENGINE_LIGHTCLASS_H
#define ENGINE_LIGHTCLASS_H
#include "Color1.h"
#include "vector3d.h"
#include <list>

enum type {point, infinity2};


class Light {
public:
    //de ambiente licht component
    Color1 ambientLight;
    //de diffuse licht component
    Color1 diffuseLight;
    //de diffuse licht component
    Color1 specularLight;

    //als het false is dan is het een puntlicht
    bool infinity = false;
    //de locatie van de puntbron
    Vector3D location;
    double spotAngle;

    //als het true is
    Vector3D ldVector;

    type lightType;




    Light(const Color1 &ambientLight, const Color1 &diffuseLight, const Color1 &specularLight);
};


//
// class InfLight: public Light {
// public:
//     //de richting waarin het
//     //licht schijnt
//     Vector3D ldVector;
//
//
//
//
// };
//
//
// class PointLight: public Light {
// public:
//
//     //de locatie van de puntbron
//     Vector3D location;
//
//     //de hoek van een spotlicht
//     double spotAngle;
// };

typedef std::list<Light> Lights3D;


#endif //ENGINE_LIGHTCLASS_H
