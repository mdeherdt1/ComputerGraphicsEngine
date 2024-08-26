//
// Created by Mathis De Herdt on 24/04/2024.
//

#include "lightedZbuffering.h"

img::EasyImage lightedZBuffering(const ini::Configuration &confg) {
    int size = confg["General"]["size"].as_int_or_die();
    int nrOfFigures = confg["General"]["nrFigures"].as_int_or_die();

    img::Color backGroundColor = img::Color();
    Vector3D eyeCords = Vector3D();

    Figures3D figures3D = configure3D(confg,size,backGroundColor,eyeCords, true);

    Lights3D lights = configureLights(confg, figures3D[0].eyepointMatrix);

    return drawTriangulateFaces(figures3D, size, backGroundColor, eyeCords, true, lights);

}

Lights3D configureLights(const ini::Configuration &confg, Matrix eyepointMatrix) {
    Lights3D lights;
    int nrOfLights = confg["General"]["nrLights"].as_int_or_die();

    for(int i = 0; i < nrOfLights; ++i) {
        std::string lightString = "Light" + std::to_string(i);

        ini::DoubleTuple ambientLight = confg[lightString]["ambientLight"].as_double_tuple_or_default(std::vector<double>({0,0,0}));
        ini::DoubleTuple diffuseLight = confg[lightString]["diffuseLight"].as_double_tuple_or_default(std::vector<double>({0,0,0}));
        ini::DoubleTuple specularLight = confg[lightString]["specularLight"].as_double_tuple_or_default(std::vector<double>({0,0,0}));

        bool infinity = confg[lightString]["infinity"].as_bool_or_default(false);

        if(infinity) {
            std::vector<double> direction = confg[lightString]["direction"].as_double_tuple_or_die();
            Vector3D directionVector;
            Light light(Color1(ambientLight[0],ambientLight[1],ambientLight[2]),
                        Color1(diffuseLight[0],diffuseLight[1],diffuseLight[2]),
                        Color1(specularLight[0],specularLight[1],specularLight[2]));
            light.infinity = true;
            light.lightType = infinity2;
            light.ldVector = directionVector.vector(direction[0], direction[1], direction[2]) * eyepointMatrix;
            light.ldVector = -Vector3D::normalise(light.ldVector);

            lights.push_back(light);
        }
        else if(confg[lightString]["location"].exists()){
            std::vector<double> location = confg[lightString]["location"].as_double_tuple_or_die();
            double spotAngle = confg[lightString]["spotAngle"].as_double_or_default(360);
            Light light(Color1(ambientLight[0],ambientLight[1],ambientLight[2]),
                        Color1(diffuseLight[0],diffuseLight[1],diffuseLight[2]),
                        Color1(specularLight[0],specularLight[1],specularLight[2]));

            light.lightType = point;

            light.spotAngle = spotAngle;

            light.location = Vector3D::point(location[0],location[1],location[2]) * eyepointMatrix;

            lights.push_back(light);
        }
        else {
            lights.push_back(Light(Color1(ambientLight[0],ambientLight[1],ambientLight[2]),
                                   Color1(diffuseLight[0],diffuseLight[1],diffuseLight[2]),
                                   Color1(specularLight[0],specularLight[1],specularLight[2])));
        }
    }

    return lights;
}


