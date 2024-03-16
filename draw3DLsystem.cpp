//
// Created by DH Services BVBA on 3/16/2024.
//
#define _USE_MATH_DEFINES


#include "draw3DLsystem.h"
#include "Face.h"

void drawLSystem3D(LParser::LSystem3D l_system, Figure &figure, Color color) {
    Lines2D lijnen;
    double x = 0, y = 0; // Startpositie
    double angle = l_system.get_angle() * (M_PI / 180.0); // Omrekenen naar radialen
    unsigned int iterations = l_system.get_nr_iterations();
    std::string currentString = l_system.get_initiator();
    std::set<char> alfabet = l_system.get_alphabet();
    std::stack<std::pair<double, double>> positionStack;
    std::stack<double> angleStack;

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

    for (char c : currentString) {
        switch (c) {
            case '+':
                angle += l_system.get_angle() * (M_PI / 180.0);
                break;
            case '-':
                angle -= l_system.get_angle() * (M_PI / 180.0);
                break;
            case '/':
                angle += M_PI / 2;
                break;
            case '\\':
                angle -= M_PI / 2;
                break;
            case '|':
                angle += M_PI;
                break;
            case '[':
                positionStack.push(std::make_pair(x, y));
                angleStack.push(angle);
                break;
            case ']':
                x = positionStack.top().first;
                y = positionStack.top().second;
                positionStack.pop();
                angle = angleStack.top();
                angleStack.pop();
                break;
            default:
                double newX = x + cos(angle);
                double newY = y + sin(angle);
                lijnen.push_back(Line2D(Point2D(x, y), Point2D(newX, newY), color));
                x = newX;
                y = newY;
                break;
        }
    }

    for (Line2D lijn : lijnen) {
        figure.points.push_back(Vector3D::point(lijn.p1.x, lijn.p1.y, 0));
        figure.points.push_back(Vector3D::point(lijn.p2.x, lijn.p2.y, 0));
    }
    //verwijder alle dubbele punten
    for(unsigned int i = 0; i < figure.points.size(); i++){
        for(unsigned int j = i+1; j < figure.points.size(); j++){
            if(figure.points[i].x == figure.points[j].x && figure.points[i].y == figure.points[j].y && figure.points[i].z == figure.points[j].z){
                figure.points.erase(figure.points.begin() + j);
                j--;
            }
        }
    }

    for (unsigned int i = 0; i < figure.points.size(); i += 2) {
        figure.faces.push_back(Face({static_cast<int>(i), static_cast<int>(i + 1), static_cast<int>(i + 2)}));
        figure.faces.push_back(Face({static_cast<int>(i + 1), static_cast<int>(i + 2), static_cast<int>(i + 3)}));
    }

    figure.color = color;

}


