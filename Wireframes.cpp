//
// Created by DH Services BVBA on 3/20/2024.
//

#include "Wireframes.h"



Figures3D configure3D(const ini::Configuration &confg, int& size, img::Color &backGroundColor, Vector3D &eyeCords){
    ini::DoubleTuple BackGroundINI = confg["General"]["backgroundcolor"];
    backGroundColor = img::Color(BackGroundINI[0]*255, BackGroundINI[1]*255, BackGroundINI[2]*255);
    int nrOfFigures = confg["General"]["nrFigures"].as_int_or_die();
    ini::DoubleTuple eyeCordsINI = confg["General"]["eye"].as_double_tuple_or_die();
    eyeCords = Vector3D::point(eyeCordsINI[0], eyeCordsINI[1], eyeCordsINI[2]);


    Figures3D figures3D;
    double rotateX;
    double rotateY;
    double rotateZ;
    double scale;
    Vector3D center;

    //voor fractalen
    int nr_iterations;
    double fractalScaleFactor;
    bool fractal = false;


    for (unsigned int i = 0; i < nrOfFigures; ++i) {
        std::string figureString = "Figure" + std::to_string(i);
        std::string type2 = confg[figureString]["type"];

        Figure figure = Figure(Color1(confg[figureString]["color"].as_double_tuple_or_die()[0],
                                      confg[figureString]["color"].as_double_tuple_or_die()[1],
                                      confg[figureString]["color"].as_double_tuple_or_die()[2]));

        if (type2 == "LineDrawing") {
            rotateX = confg[figureString]["rotateX"].as_double_or_die();
            rotateY = confg[figureString]["rotateY"].as_double_or_die();
            rotateZ = confg[figureString]["rotateZ"].as_double_or_die();
            scale = confg[figureString]["scale"].as_double_or_die();
            center = Vector3D::point(confg[figureString]["center"].as_double_tuple_or_die()[0],
                                     confg[figureString]["center"].as_double_tuple_or_die()[1],
                                     confg[figureString]["center"].as_double_tuple_or_die()[2]);
            int nrPoints = confg[figureString]["nrPoints"].as_int_or_die();
            int nrLines = confg[figureString]["nrLines"].as_int_or_die();
            for (int j = 0; j < nrPoints; ++j) {
                std::string point = "point" + std::to_string(j);
                figure.points.push_back(Vector3D::point(confg[figureString][point].as_double_tuple_or_die()[0],
                                                        confg[figureString][point].as_double_tuple_or_die()[1],
                                                        confg[figureString][point].as_double_tuple_or_die()[2]));
            }
            for (int j = 0; j < nrLines; ++j) {
                std::string Line = "line" + std::to_string(j);
                std::vector<int> pointIndexes = {};
                confg[figureString][Line].as_int_tuple_or_die();
                pointIndexes.push_back(confg[figureString][Line].as_int_tuple_or_die()[0]);
                pointIndexes.push_back(confg[figureString][Line].as_int_tuple_or_die()[1]);
                figure.faces.push_back(Face(pointIndexes));
            }
        } else if (type2 == "Cube") {
            configFigure(rotateX, rotateY, rotateZ, scale, center, confg, figureString);
            createCube(figure);
        }
        else if(type2 == "FractalCube"){
            configFigureFractal(rotateX, rotateY, rotateZ, scale, center, confg, figureString, nr_iterations, fractalScaleFactor);
            createCube(figure);
            generateFractal(figure, figures3D, nr_iterations, fractalScaleFactor,fractal);
        }
        else if (type2 == "Tetrahedron") {
            configFigure(rotateX, rotateY, rotateZ, scale, center, confg, figureString);
            createTetrahedron(figure);
        }
        else if(type2 == "FractalTetrahedron"){
            configFigureFractal(rotateX, rotateY, rotateZ, scale, center, confg, figureString, nr_iterations, fractalScaleFactor);
            createTetrahedron(figure);
            Figures3D fractalFigures;
            generateFractal(figure, figures3D, nr_iterations, fractalScaleFactor,fractal);
        }
        else if (type2 == "Octahedron") {
            configFigure(rotateX, rotateY, rotateZ, scale, center, confg, figureString);
            createOctahedron(figure);
        }
        else if(type2 == "FractalOctahedron"){
            configFigureFractal(rotateX, rotateY, rotateZ, scale, center, confg, figureString, nr_iterations, fractalScaleFactor);
            createOctahedron(figure);
            generateFractal(figure, figures3D, nr_iterations, fractalScaleFactor,fractal);

        }
        else if (type2 == "Icosahedron" || type2 == "BuckyBall" || type2 == "MengerSponge") { //BuckyBall en MengerSponge niet geimplementeerd
            configFigure(rotateX, rotateY, rotateZ, scale, center, confg, figureString);
            createIcosahedron(figure);
        }
        else if(type2 == "FractalIcosahedron"){
            configFigureFractal(rotateX, rotateY, rotateZ, scale, center, confg, figureString, nr_iterations, fractalScaleFactor);
            createIcosahedron(figure);
            generateFractal(figure, figures3D, nr_iterations, fractalScaleFactor,fractal);

        }
        else if (type2 == "Dodecahedron") {
            configFigure(rotateX, rotateY, rotateZ, scale, center, confg, figureString);
            createDodecahedron(figure);
            configFigureTranslations(figure, rotateX, rotateY, rotateZ, scale, center, eyeCords);
        }
        else if(type2 == "FractalDodecahedron"){
            configFigureFractal(rotateX, rotateY, rotateZ, scale, center, confg, figureString, nr_iterations, fractalScaleFactor);
            createDodecahedron(figure);
            generateFractal(figure, figures3D, nr_iterations, fractalScaleFactor,fractal);

        }
        else if (type2 == "Cone") {
            double h;
            int n;

            configCylinder(rotateX, rotateY, rotateZ, scale, center, confg, figureString, h, n);
            createCone(figure, n, h);
            configFigureTranslations(figure, rotateX, rotateY, rotateZ, scale, center, eyeCords);


        } else if (type2 == "Cylinder") {
            double h;
            int n;

            configCylinder(rotateX, rotateY, rotateZ, scale, center, confg, figureString, h, n);
            createCylinder(figure, n, h);
            configFigureTranslations(figure, rotateX, rotateY, rotateZ, scale, center, eyeCords);

        } else if (type2 == "Sphere") {
            int n;

            configSphere(rotateX, rotateY, rotateZ, scale, center, confg, figureString, n);
            createSphere(figure, n);
            configFigureTranslations(figure, rotateX, rotateY, rotateZ, scale, center, eyeCords);

        } else if (type2 == "Torus") {
            int n;
            int m;
            double R;
            int r;

            configTorus(rotateX, rotateY, rotateZ, scale, center, confg, figureString, R, r, n, m);
            createTorus(figure, n, m, R, r);
            configFigureTranslations(figure, rotateX, rotateY, rotateZ, scale, center, eyeCords);


        } else if (type2 == "3DLSystem") {
            Color1 kleur = Color1();

            LParser::LSystem3D l_system = createLSystem3D(confg, figureString, scale, rotateX, rotateY, rotateZ, center,
                                                          kleur);
            drawLSystem3D(l_system, figure, kleur);
            configFigureTranslations(figure, rotateX, rotateY, rotateZ, scale, center, eyeCords);
        }
        else if(type2 == "FractalBuckyBall"){
            configFigureFractal(rotateX, rotateY, rotateZ, scale, center, confg, figureString, nr_iterations, fractalScaleFactor);
            configFigureFractal(rotateX, rotateY, rotateZ, scale, center, confg, figureString, nr_iterations, fractalScaleFactor);
            createIcosahedron(figure);
            generateFractal(figure, figures3D, nr_iterations, fractalScaleFactor,fractal);
        }


        if(fractal){
            for(int j = 0; j < figures3D.size(); j++){
                figures3D[j].color = Color1(confg[figureString]["color"].as_double_tuple_or_die()[0],
                                            confg[figureString]["color"].as_double_tuple_or_die()[1],
                                            confg[figureString]["color"].as_double_tuple_or_die()[2]);
                configFigureTranslations(figures3D[j], rotateX, rotateY, rotateZ, scale, center, eyeCords);
                calculateTotalMatrix(figures3D[j]);
                applyTransformation(&figures3D[j], figures3D[j].totalMatrix);
                applyTransformation(&figures3D[j], eyePointTrans(figures3D[j].eyePoint));
            }
        }
        else {
            figure.color = Color1(confg[figureString]["color"].as_double_tuple_or_die()[0],
                                  confg[figureString]["color"].as_double_tuple_or_die()[1],
                                  confg[figureString]["color"].as_double_tuple_or_die()[2]);

            configFigureTranslations(figure, rotateX, rotateY, rotateZ, scale, center, eyeCords);
            calculateTotalMatrix(figure);
            applyTransformation(&figure, figure.totalMatrix);
            applyTransformation(&figure, eyePointTrans(figure.eyePoint));
            figures3D.push_back(figure);
        }
    }
    return figures3D;
}





