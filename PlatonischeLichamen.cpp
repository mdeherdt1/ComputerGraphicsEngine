//
// Created by student on 13/03/24.
//
#define _USE_MATH_DEFINES
#include "PlatonischeLichamen.h"


void createCube(Figure& figure) {
    /*
     * points: [1, -1, -1], [-1, 1, -1], [1, 1, 1], [-1, -1, 1], [1, 1, -1], [-1, -1, -1], [1, -1, 1], [-1, 1, 1]
     * faces: [1,5,3,7], [5,2,8,3], [2,6,4,8], [6,1,7,4], [7,3,8,4], [1,6,2,5]
     */

    figure.points.push_back(Vector3D::point(1, -1, -1));
    figure.points.push_back(Vector3D::point(-1, 1, -1));
    figure.points.push_back(Vector3D::point(1, 1, 1));
    figure.points.push_back(Vector3D::point(-1, -1, 1));
    figure.points.push_back(Vector3D::point(1, 1, -1));
    figure.points.push_back(Vector3D::point(-1, -1, -1));
    figure.points.push_back(Vector3D::point(1, -1, 1));
    figure.points.push_back(Vector3D::point(-1, 1, 1));

    figure.faces.push_back(Face({0,4,2,6}));
    figure.faces.push_back(Face({4,1,7,2}));
    figure.faces.push_back(Face({1,5,3,7}));
    figure.faces.push_back(Face({5,0,6,3}));
    figure.faces.push_back(Face({6,2,7,3}));
    figure.faces.push_back(Face({0,5,1,4}));


}

void createTetrahedron(Figure &figure) {
    /*
     * points: [1, -1, -1], [-1, 1, -1], [1, 1, 1], [-1, -1, 1]
     * faces: [0,1,2], [1,3,2], [0,3,1], [0,2,3]
     */

    figure.points.push_back(Vector3D::point(1, -1, -1));
    figure.points.push_back(Vector3D::point(-1, 1, -1));
    figure.points.push_back(Vector3D::point(1, 1, 1));
    figure.points.push_back(Vector3D::point(-1, -1, 1));

    figure.faces.push_back(Face({0,1,2}));
    figure.faces.push_back(Face({1,3,2}));
    figure.faces.push_back(Face({0,3,1}));
    figure.faces.push_back(Face({0,2,3}));


}

void createOctahedron(Figure &figure) {
    /*
     * points: [1, 0, 0], [0, 1, 0], [-1, 0, 0], [0, -1, 0], [0, 0, -1], [0, 0, 1]
     * faces: [0,1,5], [1,2,5], [2,3,5], [3,0,5], [1,0,4], [2,1,4], [3,2,4], [0,3,4]
     */

    figure.points.push_back(Vector3D::point(1, 0, 0));
    figure.points.push_back(Vector3D::point(0, 1, 0));
    figure.points.push_back(Vector3D::point(-1, 0, 0));
    figure.points.push_back(Vector3D::point(0, -1, 0));
    figure.points.push_back(Vector3D::point(0, 0, -1));
    figure.points.push_back(Vector3D::point(0, 0, 1));

    figure.faces.push_back(Face({0,1,5}));
    figure.faces.push_back(Face({1,2,5}));
    figure.faces.push_back(Face({2,3,5}));
    figure.faces.push_back(Face({3,0,5}));
    figure.faces.push_back(Face({1,0,4}));
    figure.faces.push_back(Face({2,1,4}));
    figure.faces.push_back(Face({3,2,4}));
    figure.faces.push_back(Face({0,3,4}));

}

void createIcosahedron(Figure &figure) {
    for(int i = 1; i <= 12; i++) {
        if (i == 1) {
            figure.points.push_back(Vector3D::point(0, 0, sqrt(5) / 2));
        } else if (i <= 6) {
            figure.points.push_back(Vector3D::point(cos((i - 2) * 2 * M_PI / 5), sin((i - 2) * 2 * M_PI / 5), 0.5));
        } else if (i == 12) {
            figure.points.push_back(Vector3D::point(0, 0, -sqrt(5) / 2));
        } else {
            figure.points.push_back(
                    Vector3D::point(cos(M_PI / 5 + (i - 7) * 2 * M_PI / 5), sin(M_PI / 5 + (i - 7) * 2 * M_PI / 5),
                                    -0.5));
        }

        /*
         * faces:
         * [0,1,2] [0,2,3] [0,3,4] [0,4,5] [0,5,1]
         * [1,6,2]
         * [2,6,7] [2,7,3]
         * [3,7,8] [3,8,4]
         * [4,8,9] [4,9,5]
         * [5,9,10] [5,10,1]
         * [1,10,6]
         * [11,7,6] [11,8,7] [11,9,10] [11,10,9] [11,6,10]
         *
         */
    }
        figure.faces.push_back(Face({0,1,2}));
        figure.faces.push_back(Face({0,2,3}));
        figure.faces.push_back(Face({0,3,4}));
        figure.faces.push_back(Face({0,4,5}));
        figure.faces.push_back(Face({0,5,1}));
        figure.faces.push_back(Face({1,6,2}));
        figure.faces.push_back(Face({2,6,7}));
        figure.faces.push_back(Face({2,7,3}));
        figure.faces.push_back(Face({3,7,8}));
        figure.faces.push_back(Face({3,8,4}));
        figure.faces.push_back(Face({4,8,9}));
        figure.faces.push_back(Face({4,9,5}));
        figure.faces.push_back(Face({5,9,10}));
        figure.faces.push_back(Face({5,10,1}));
        figure.faces.push_back(Face({1,10,6}));
        figure.faces.push_back(Face({11,7,6}));
        figure.faces.push_back(Face({11,8,7}));
        figure.faces.push_back(Face({11,9,8}));
        figure.faces.push_back(Face({11,10,9}));
        figure.faces.push_back(Face({11,6,10}));



}

void createDodecahedron(Figure &figure) {
    createIcosahedron(figure);
    std::vector<Vector3D> newPoints;


    for(auto &intPoint : figure.faces) {
        double x = 0;
        double y = 0;
        double z = 0;
        for(auto point : intPoint.point_indexes) {
            x += figure.points[point].x;
            y += figure.points[point].y;
            z += figure.points[point].z;
        }
        x = x/3;
        y = y/3;
        z = z/3;
        newPoints.push_back(Vector3D::point(x, y, z));
    }


    figure.points = newPoints;
    figure.faces.clear();
    figure.faces.push_back(Face({0,1,2,3,4}));
    figure.faces.push_back(Face({0,5,6,7,1}));
    figure.faces.push_back(Face({1,7,8,9,2}));
    figure.faces.push_back(Face({2,9,10,11,3}));
    figure.faces.push_back(Face({3,11,12,13,4}));
    figure.faces.push_back(Face({4,13,14,5,0}));
    figure.faces.push_back(Face({19,18,17,16,15}));
    figure.faces.push_back(Face({19,14,13,12,18}));
    figure.faces.push_back(Face({18,12,11,10,17}));
    figure.faces.push_back(Face({17,10,9,8,16}));
    figure.faces.push_back(Face({16,8,7,6,15}));
    figure.faces.push_back(Face({15,6,5,14,19}));

}
