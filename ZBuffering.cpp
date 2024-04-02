//
// Created by DH Services BVBA on 4/1/2024.
//

#include <list>
#include "ZBuffering.h"
#include "Color1.h"
#include <limits>


img::EasyImage zBuffering(const ini::Configuration &confg){
    int size = confg["General"]["size"];

    img::Color backGroundColor = img::Color();
    Vector3D eyeCords = Vector3D();

    Figures3D figures3D = configure3D(confg,size,backGroundColor,eyeCords);

    return drawTriangulateFaces(figures3D, size, backGroundColor, eyeCords, true);
}

img::EasyImage drawTriangulateFaces(Figures3D figures3D, int size, img::Color bgColor, Vector3D eyeCords, bool buffer) {
    Lines2D lines = doProjection(figures3D);

    double xmin = std::numeric_limits<double>::infinity(), xmax = 0, ymin = +std::numeric_limits<double>::infinity(), ymax = 0;



    //push alles in de vectoren om min en max te bepalen
    for(Lines2D::iterator it = lines.begin(); it != lines.end(); it++) {
        double x1 = it->p1.x;
        double x2 = it->p2.x;

        double y1 = it->p1.y;
        double y2 = it->p2.y;

        if(xmin > x1) xmin = x1;
        if(xmax < x1) xmax = x1;

        if(xmin > x2) xmin = x2;
        if(xmax < x2) xmax = x2;

        if(ymin > y1) ymin = y1;
        if(ymax < y1) ymax = y1;

        if(ymin > y2) ymin = y2;
        if(ymax < y2) ymax = y2;
    }

    double x_range = xmax - xmin;
    double y_range = ymax - ymin;
    double width = size * (x_range / (std::max(x_range,y_range)));
    double height = size * (y_range / (std::max(x_range,y_range)));


    double d = 0.95 * (width / x_range);

    double DCx = d * ((xmin + xmax) / 2);
    double DCy = d * ((ymin + ymax) / 2);

    double dx = width / 2 - DCx;
    double dy = height / 2 - DCy;

    ZBuffer Zbuf = ZBuffer(width, height);

    img::EasyImage image(width,height,bgColor);

    doTriangulation(figures3D, image, Zbuf, d, dx, dy);

    for(auto fig : figures3D){
        for(auto face : fig.faces){
            Vector3D v0 = fig.points[face.point_indexes[0]];
            Vector3D v1 = fig.points[face.point_indexes[1]];
            Vector3D v2 = fig.points[face.point_indexes[2]];
            Color1 c = fig.color;
            image.draw_zbuf_triangle(Zbuf, v0, v1, v2, d, dx, dy, c);
        }
    }


    return image;


}

std::vector<Face> triangulate(const Face face) {
    std::vector<Face> faceTriangulate;
    int P0 = face.point_indexes[0];
    for(int i = 1; i < face.point_indexes.size() - 1; i++){
        faceTriangulate.push_back(Face(std::vector<int>({P0, face.point_indexes[i], face.point_indexes[i + 1]})));
    }
    return faceTriangulate;
}

void doTriangulation(Figures3D& figures, img::EasyImage& image, ZBuffer& zbuf, double d, double dx, double dy) {
    for (Figure& figure : figures) {
        std::vector<Face> facesNew;
        for (Face& face : figure.faces) {
            std::vector<Face> newFaces = triangulate(face);
            facesNew.insert(facesNew.end(), newFaces.begin(), newFaces.end());
        }
        figure.faces = facesNew;

        for (Face& face : figure.faces) {
            Vector3D v0 = figure.points[face.point_indexes[0]];
            Vector3D v1 = figure.points[face.point_indexes[1]];
            Vector3D v2 = figure.points[face.point_indexes[2]];
            Color1 c = figure.color;

            image.draw_zbuf_triangle(zbuf, v0, v1, v2, d, dx, dy, c);
        }
    }
}





void img::EasyImage::draw_zbuf_triangle(ZBuffer &zbuf, Vector3D &A, Vector3D &B, Vector3D &C, double d, double dx,
                                        double dy, Color1 color) {
    double Axp = (d * A.x) / (-A.z) + dx;
    double Ayp = (d * A.y) / (-A.z) + dy;
    Point2D Ap = Point2D(Axp, Ayp);

    double Bxp = (d * B.x) / (-B.z) + dx;
    double Byp = (d * B.y) / (-B.z) + dy;
    Point2D Bp = Point2D(Bxp, Byp);

    double Cxp = (d * C.x) / (-C.z) + dx;
    double Cyp = (d * C.y) / (-C.z) + dy;
    Point2D Cp = Point2D(Cxp, Cyp);

    Line2D AB = Line2D(Ap, Bp, color);
    Line2D AC = Line2D(Ap, Cp, color);
    Line2D BC = Line2D(Bp, Cp, color);

    double yMinTemp = std::min(Ayp, Byp);
    int yMin = round(std::min(yMinTemp, Cyp)+ 0.5);

    double yMaxTemp = std::max(Ayp, Byp);
    int yMax = round(std::max(yMaxTemp, Cyp)- 0.5);


    Vector3D u = B - A;
    Vector3D v = C - A;
    double w1 = (u.y * v.z) - (u.z * v.y);
    double w2 = (u.z * v.x) - (u.x * v.z);
    double w3 = (u.x * v.y) - (u.y * v.x);
    double k = w1 * A.x + w2 * A.y + w3 * A.z;
    double dzdx = w1/(-(d*k));
    double dzdy = w2/(-(d*k));


    for(int yi = yMin; yi <= yMax; yi++){
        double XLab, XLac, XLbc;
        double XRab, XRac, XRbc;
        XLab = XLac = XLbc = std::numeric_limits<int>::max();
        XRab = XRac = XRbc = -std::numeric_limits<int>::max();

        if((yi - AB.p1.y)*(yi - AB.p2.y) <= 0 && AB.p1.y != AB.p2.y){
            Point2D P = AB.p1;
            Point2D Q = AB.p2;
            double xi = Q.x + (P.x - Q.x)*((yi-Q.y)/(P.y-Q.y));
            XLab = XRab = xi;
        }
        if((yi - AC.p1.y)*(yi - AC.p2.y) <= 0 && AC.p1.y != AC.p2.y){
            Point2D P = AC.p1;
            Point2D Q = AC.p2;
            double xi = Q.x + (P.x - Q.x)*((yi-Q.y)/(P.y-Q.y));
            XLac = XRac = xi;
        }
        if((yi - BC.p1.y)*(yi - BC.p2.y) <= 0 && BC.p1.y != BC.p2.y){
            Point2D P = BC.p1;
            Point2D Q = BC.p2;
            double xi = Q.x + (P.x - Q.x)*((yi-Q.y)/(P.y-Q.y));
            XLbc = XRbc = xi;
        }
        double xlTemp = (std::min(XLab, XLac));
        int xl = round(std::min(xlTemp, XLbc) + 0.5);

        double xrTemp = (std::max(XRab, XRac));
        int xr = round(std::max(xrTemp, XRbc) - 0.5);

        double xg = (Axp + Bxp + Cxp)/3;
        double yg = (Ayp + Byp + Cyp)/3;
        double oneOverzg = 1/(3 * A.z) + 1 / (3 * B.z) + 1 / (3 * C.z);

        for(int x = xl; x <= xr; x++){
            double oneOverZ = 1.0001 * oneOverzg + (x - xg)*dzdx + (yi - yg)*dzdy;
            if(oneOverZ < zbuf.v[x][yi]){
                img::Color color1 = Color(color.red*255,color.green*255,color.blue*255);
                (*this)(x, yi) = color1;
                zbuf.v[x][yi] = oneOverZ;
            }
        }
    }
}
