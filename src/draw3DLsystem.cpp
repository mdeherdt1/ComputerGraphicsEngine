//
// Created by DH Services BVBA on 3/16/2024.
//
#define _USE_MATH_DEFINES


#include "draw3DLsystem.h"
#include "Face.h"
#include "vector3d.h"
#include <stack>
#include <array>

/// Global index counter
void drawLSystem3D(LParser::LSystem3D l_system, Figure &figure, Color1 color) {
    int point_index = 0;
    Vector3D position = Vector3D::point(0, 0, 0); // Startpositie in 3D
    double angle = l_system.get_angle() * (M_PI / 180.0); // Omrekenen naar radialen
    unsigned int iterations = l_system.get_nr_iterations();
    std::string currentString = l_system.get_initiator();
    std::set<char> alfabet = l_system.get_alphabet();
    std::stack<Vector3D> positionStack;
    std::stack<std::array<Vector3D, 3>> directionStack; // Voor H, U, en L vectoren.


    Vector3D Hforward = Vector3D::vector(1, 0, 0);

    // Initialisatie van H, U, L vectoren.
    Vector3D H = Vector3D::vector(1, 0, 0);
    Vector3D L = Vector3D::vector(0, 1, 0);
    Vector3D U = Vector3D::vector(0, 0, 1);


    // Verwerk iteraties.
    for (unsigned int i = 0; i < iterations; i++) {
        std::string newString = "";
        for (char c : currentString) {
            if (alfabet.find(c) != alfabet.end()) {
                newString += l_system.get_replacement(c);
            } else {
                newString += c;
            }
        }
        currentString = newString;
    }

    Lines2D lijnen;

    for (char c : currentString) {
        Vector3D Hold = H;
        Vector3D Uold = U;
        Vector3D Lold = L;
        switch (c) {
            case '+': //we draaien naar links over een hoek angle
                H = Hold * cos(angle) + Lold * sin(angle);
                L = -Hold * sin(angle) + Lold * cos(angle);
                break;
            case '-': // we draaien naar rechts over een hoek angle
                H = Hold * cos(-angle) + Lold * sin(-angle);
                L = -Hold * sin(-angle) + Lold * cos(-angle);
                break;

            case '^': //draaien we draaien angle opwaarts
                H = Hold * cos(angle) + Uold * sin(angle);
                U = -Hold * sin(angle) + Uold * cos(angle);
                break;
            case '&': //draaien we draaien angle neerwaarts
                H = Hold * cos(-angle) + Uold * sin(-angle);
                U = -Hold * sin(-angle) + Uold * cos(-angle);
                break;

            case '\\': //we maken een rolbeweging naar links over angle radialen
                L = Lold * cos(angle) - Uold * sin(angle);
                U = Lold * sin(angle) + Uold * cos(angle);
                break;
            case '/': //we maken een rolbeweging naar rechts over angle radialen
                L = Lold * cos(-angle) - Uold * sin(-angle);
                U = Lold * sin(-angle) + Uold * cos(-angle);
                break;

            case '|': //We keren onze richting om, we roteren pi radialen om de vector U
                H = -Hold;
                L = -Lold;
                break;

            case '(': // Push current state
                positionStack.push(position);
                directionStack.push({Hold, Uold, Lold});
                break;
            case ')': // Pop state
                if (!positionStack.empty() && !directionStack.empty()) {
                    position = positionStack.top();
                    positionStack.pop();

                    auto dirs = directionStack.top();
                    H = dirs[0];
                    U = dirs[1];
                    L = dirs[2];
                    directionStack.pop();
                }
                break;

            default: // Move forward
                Vector3D cur_position = position;
                position = position + H;
                if(l_system.draw(c)){
                    figure.points.push_back(cur_position);
                    figure.points.push_back(position);
                    figure.faces.push_back(Face({point_index, point_index + 1}));
                    point_index += 2;
                }
                break;
        }
    }

    figure.color = color;

}

void confg3DLSystem(LParser::LSystem3D &l_system, const ini::Configuration &configuration, std::string figureString,
                    int size, std::vector<double> backGroundINI, img::Color backgroundColor, int nrO) {

}

LParser::LSystem3D createLSystem3D(const ini::Configuration &confg, std::string figureString, double &scale, double &rotateX, double &rotateY, double &rotateZ, Vector3D &center, Color1 &kleur) {
    std::string inputFile = confg[figureString]["inputfile"];
    LParser::LSystem3D l_system;
    std::ifstream input_stream(inputFile);
    input_stream >> l_system;
    input_stream.close();

    rotateX = confg[figureString]["rotateX"].as_double_or_die();
    rotateY = confg[figureString]["rotateY"].as_double_or_die();
    rotateZ = confg[figureString]["rotateZ"].as_double_or_die();
    scale = confg[figureString]["scale"].as_double_or_die();
    center = Vector3D::point(confg[figureString]["center"].as_double_tuple_or_die()[0], confg[figureString]["center"].as_double_tuple_or_die()[1], confg[figureString]["center"].as_double_tuple_or_die()[2]);
     kleur = Color1(confg[figureString]["color"].as_double_tuple_or_die()[0], confg[figureString]["color"].as_double_tuple_or_die()[1], confg[figureString]["color"].as_double_tuple_or_die()[2]);


    return l_system;
}





