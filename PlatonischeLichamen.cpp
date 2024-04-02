//
// Created by student on 13/03/24.
//
#define _USE_MATH_DEFINES
#include "PlatonischeLichamen.h"
#include "translations.h"




void createCube(Figure& figure) {
    figure.points.clear();
    figure.faces.clear();

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
    figure.points.clear();
    figure.faces.clear();

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
    figure.points.clear();
    figure.faces.clear();

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
    figure.points.clear();
    figure.faces.clear();

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
    figure.points.clear();
    figure.faces.clear();

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

void createCone(Figure &figure, const int n, const double h) {
    figure.points.clear();
    figure.faces.clear();

    for (int i = 0; i < n; ++i) {
        double angle = 2 * M_PI * i / n;
        Vector3D point = Vector3D::point(cos(angle), sin(angle), 0);
        figure.points.push_back(point);
    }

    Vector3D top = Vector3D::point(0, 0, h);
    figure.points.push_back(top);

    for (int i = 0; i < n; ++i) {
        std::vector<int> zijVlak = {i, (i + 1) % n, n};
        figure.faces.push_back(Face(zijVlak));
    }

    std::vector<int> basePoints;
    for (int i = 0; i < n; ++i) {
        basePoints.push_back(i);
    }

    figure.faces.push_back(Face(basePoints));
}

void createCylinder(Figure &figure, const int n, const double h) {
    figure.points.clear();
    figure.faces.clear();

    for (int i = 0; i < n; ++i) {
        double angle = 2 * M_PI * i / n;
        Vector3D bottomPoint = Vector3D::point(cos(angle), sin(angle), 0);
        figure.points.push_back(bottomPoint);
    }

    for (int i = 0; i < n; ++i) {
        double angle = 2 * M_PI * i / n;
        Vector3D topPoint = Vector3D::point(cos(angle), sin(angle), h);
        figure.points.push_back(topPoint);
    }

    for (int i = 0; i < n; ++i) {
        std::vector<int> facePoints = {
                i,
                (i + 1) % n,
                (i + 1) % n + n,
                i + n
        };
        figure.faces.push_back(Face(facePoints));
    }

    std::vector<int> bottomFacePoints;
    for (int i = 0; i < n; ++i) {
        bottomFacePoints.push_back(i);
    }
    figure.faces.push_back(Face(bottomFacePoints));

    std::vector<int> topFacePoints;
    for (int i = n; i < 2*n; ++i) {
        topFacePoints.push_back(i);
    }
    figure.faces.push_back(Face(topFacePoints));
}

int findOrAddPoint(Figure &figure, Vector3D point) {
    point.normalise();
    for (size_t i = 0; i < figure.points.size(); ++i) {
        if (figure.points[i].x == point.x && figure.points[i].y == point.y && figure.points[i].z == point.z) {
            return i;
        }
    }
    figure.points.push_back(point);
    return figure.points.size() - 1;
}

void subdivide(Figure &figure, int n) {
    if (n <= 0) return;

    std::vector<Face> newFaces;

    for (auto &face : figure.faces) {
        int i1 = face.point_indexes[0];
        int i2 = face.point_indexes[1];
        int i3 = face.point_indexes[2];

        Vector3D m1 = Vector3D::point((figure.points[i1].x + figure.points[i2].x) / 2,
                                      (figure.points[i1].y + figure.points[i2].y) / 2,
                                      (figure.points[i1].z + figure.points[i2].z) / 2);

        Vector3D m2 = Vector3D::point((figure.points[i2].x + figure.points[i3].x) / 2,
                                      (figure.points[i2].y + figure.points[i3].y) / 2,
                                      (figure.points[i2].z + figure.points[i3].z) / 2);

        Vector3D m3 = Vector3D::point((figure.points[i1].x + figure.points[i3].x) / 2,
                                      (figure.points[i1].y + figure.points[i3].y) / 2,
                                      (figure.points[i1].z + figure.points[i3].z) / 2);

        int m1i = findOrAddPoint(figure, m1);
        int m2i = findOrAddPoint(figure, m2);
        int m3i = findOrAddPoint(figure, m3);

        newFaces.push_back(Face({i1, m1i, m3i}));
        newFaces.push_back(Face({i2, m2i, m1i}));
        newFaces.push_back(Face({i3, m3i, m2i}));
        newFaces.push_back(Face({m1i, m2i, m3i}));
    }

    figure.faces = newFaces;

    // Recursieve aanroep voor de volgende subdivisie
    subdivide(figure, n - 1);
}

void createSphere(Figure &figure, const int n) {
    createIcosahedron(figure);

    subdivide(figure, n);

    for (auto &point : figure.points) {
        point.normalise();
    }
}

void createTorus(Figure &figure, const int n, const int m, const double R, const double r) {
    figure.points.clear();
    figure.faces.clear();

    // Bereken punten op de torus
    for (int i = 0; i < n; ++i) {
        double u = 2 * M_PI * i / n;
        for (int j = 0; j < m; ++j) {
            double v = 2 * M_PI * j / m;
            double x = (R + r * cos(v)) * cos(u);
            double y = (R + r * cos(v)) * sin(u);
            double z = r * sin(v);
            figure.points.push_back(Vector3D::point(x, y, z));
        }
    }

    // Genereer de oppervlakken
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int p1 = (i * m + j) % (n * m);
            int p2 = ((i + 1) % n * m + j) % (n * m);
            int p3 = ((i + 1) % n * m + (j + 1) % m) % (n * m);
            int p4 = (i * m + (j + 1) % m) % (n * m);
            figure.faces.push_back(Face({p1, p2, p3, p4}));
        }
    }

}

void configFigure(double &rotateX, double &rotateY, double &rotateZ, double &scale, Vector3D &center,
                  const ini::Configuration &confg, std::string figureString) {
    rotateX = confg[figureString]["rotateX"].as_double_or_die();
    rotateY = confg[figureString]["rotateY"].as_double_or_die();
    rotateZ = confg[figureString]["rotateZ"].as_double_or_die();
    scale = confg[figureString]["scale"].as_double_or_die();
    center = Vector3D::point(confg[figureString]["center"].as_double_tuple_or_die()[0], confg[figureString]["center"].as_double_tuple_or_die()[1], confg[figureString]["center"].as_double_tuple_or_die()[2]);


}

void configCylinder(double &rotateX, double &rotateY, double &rotateZ, double &scale, Vector3D &center,
                    const ini::Configuration &confg, std::string figureString, double &h, int &n) {
    configFigure(rotateX, rotateY, rotateZ, scale, center, confg, figureString);
     n = confg[figureString]["n"].as_int_or_die();
     h = confg[figureString]["height"].as_double_or_die();
}

void applyAllTransformations(Figure &figure, double scaleFactor, double rotateX, double rotateY, double rotateZ,
                             Vector3D center) {
    applyTransformation(&figure, scaleFigure(scaleFactor));
    applyTransformation(&figure, RotateX(rotateX));
    applyTransformation(&figure, RotateY(rotateY));
    applyTransformation(&figure, RotateZ(rotateZ));
    applyTransformation(&figure, translate(center));
}

void configSphere(double &rotateX, double &rotateY, double &rotateZ, double &scale, Vector3D &center,
                  const ini::Configuration &confg, std::string figureString, int &n) {
    configFigure(rotateX, rotateY, rotateZ, scale, center, confg, figureString);
     n = confg[figureString]["n"].as_int_or_die();
}

void configTorus(double &rotateX, double &rotateY, double &rotateZ, double &scale, Vector3D &center,
                 const ini::Configuration &confg, std::string figureString, double &R, int &r, int &n, int &m) {
    configFigure(rotateX, rotateY, rotateZ, scale, center, confg, figureString);
     n = confg[figureString]["n"].as_int_or_die();
     m = confg[figureString]["m"].as_int_or_die();
     R = confg[figureString]["R"].as_double_or_die();
     r = confg[figureString]["r"].as_int_or_die();
}

void calculateTotalMatrix(Figure &figure) {
    if (figure.firstTime) {
        figure.totalMatrix = scaleFigure(figure.scale) * RotateX(figure.rotateX) * RotateY(figure.rotateY) * RotateZ(figure.rotateZ) * translate(figure.center);
        figure.firstTime = false;
    }
}

void configFigureTranslations(Figure &figure, double rotateX, double rotateY, double rotateZ, double scale, Vector3D center,
                         Vector3D eyeCords) {
    figure.rotateX = rotateX;
    figure.rotateY = rotateY;
    figure.rotateZ = rotateZ;
    figure.scale = scale;
    figure.center = center;
    figure.eyePoint = eyeCords;
}



