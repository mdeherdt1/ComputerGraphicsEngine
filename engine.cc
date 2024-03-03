#include "easy_image.h"
#include "ini_configuration.h"
#include "Color.h"
#include "Point2D.h"
#include "Line2D.h"
#include "introduction.h"
#include "l_parser.h"
#include "vector3d.h"
#include "Figure.h"
#include "Face.h"

#include <set>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <ctime>



#include <string>




constexpr double PI = 3.14159265358979323846;



img::EasyImage draw2DLines(const Lines2D &lines, const int size, img::Color background = img::Color(0,0,0)){
    std::vector<double> xjes ;
    std::vector<double>ytjes;



    //push alles in de vectoren om min en max te bepalen
    for (Line2D lijn:lines) {
        xjes.push_back(lijn.p1.x);
        xjes.push_back(lijn.p2.x);
        ytjes.push_back(lijn.p1.y);
        ytjes.push_back(lijn.p2.y);
    }
    double x_min = xjes[0];
    double y_min = ytjes[0];
    double x_max = xjes[0];
    double y_max = ytjes[0];

    for (double x:xjes){
        if(x <= x_min){
            x_min = x;
        }
        if(x >= x_max){
            x_max = x;
        }
    }
    for(double y:ytjes){
        if(y <= y_min){
            y_min = y;
        }
        if(y >= y_max){
            y_max = y;
        }
    }
    double x_range = x_max - x_min;
    double y_range = y_max - y_min;
    double width = size * (x_range / (std::max(x_range,y_range)));
    double height = size * (y_range / (std::max(x_range,y_range)));

    img::EasyImage image(width,height,background);

    double schaalFactor = 0.95 * (width/x_range);

    double DCx = schaalFactor * ((x_min + x_max)/2);
    double DCy = schaalFactor * ((y_min + y_max)/2);

    double dx = width / 2 - DCx;
    double dy = height / 2 - DCy;

    for (Line2D lijn:lines) {
        lijn.p1.x = round(lijn.p1.x * schaalFactor + dx);
        lijn.p1.y = round(lijn.p1.y * schaalFactor + dy);
        lijn.p2.x = round(lijn.p2.x * schaalFactor + dx);
        lijn.p2.y = round(lijn.p2.y * schaalFactor + dy);

        img::Color kleur = img::Color(lijn.color.red*255,lijn.color.green*255,lijn.color.blue*255);

        image.draw_line(lijn.p1.x,lijn.p1.y,lijn.p2.x,lijn.p2.y, kleur);

    }



    return image;


}

LParser::LSystem2D DLSystem(const ini::Configuration &confg){
    std::string inputFile = confg["2DLSystem"]["inputfile"];

    LParser::LSystem2D l_system;
    std::ifstream input_stream(inputFile);
    input_stream >> l_system;
    input_stream.close();

    return l_system;
}

Lines2D drawLSystem(const LParser::LSystem2D &l_system, Color lijnKleur = Color(255,255,255)) {
    srand(static_cast<unsigned int>(time(0)));
    Lines2D lijnen;
    double x = 0, y = 0; // Startpositie
    double angle = l_system.get_angle() * (PI / 180.0); // Omrekenen naar radialen
    double currentAngle = l_system.get_starting_angle() * (PI / 180.0); // Start hoek in radialen
    unsigned int iterations = l_system.get_nr_iterations();
    std::string currentString = l_system.get_initiator();
    std::set<char> alfabet = l_system.get_alphabet();
    std::map<char, std::vector<StochasticRule>> stochastic = l_system.getReplacementStochastic();
    std::stack<std::pair<double, double>> positionStack;
    std::stack<double> angleStack;

    // Bereken de string voor het gegeven aantal iteraties
    for (unsigned int i = 0; i < iterations; i++) {
        std::string newString;
        for (char c : currentString) {
            if (stochastic.find(c) != stochastic.end()) { // Controleer of c in de stochastic rules zit
                double random = static_cast<double>(rand()) / RAND_MAX; 
                double cumulative = 0.0;
                for (const StochasticRule &rule : stochastic.at(c)) {
                    cumulative += rule.probability;
                    if (random <= cumulative) {
                        newString += rule.outcome;
                        break;
                    }
                }
            }
            //controleer of er een normale replacement rule is voor c
            else if(c != '(' && c != ')' && alfabet.find(c) != alfabet.end()){
                newString += l_system.get_replacement(c);
            }
            else{
                newString += c;
            }
        }
        currentString = newString;
    }

    // Loop door de finale string om lijnen te tekenen
    for (char c : currentString) {
        switch (c) {
            case '+': // Draai rechts
                currentAngle += angle;
                break;
            case '-': // Draai links
                currentAngle -= angle;
                break;
            case '(': // Sla huidige positie en hoek op
                positionStack.push({x, y});
                angleStack.push(currentAngle);
                break;
            case ')': // Herstel de laatst opgeslagen positie en hoek
                if (!positionStack.empty() && !angleStack.empty()) {
                    auto position = positionStack.top(); positionStack.pop();
                    x = position.first;
                    y = position.second;
                    currentAngle = angleStack.top(); angleStack.pop();
                }
                break;
            default:
                if (alfabet.find(c) != alfabet.end()) { // Teken een lijn als het karakter in het alfabet zit
                    double newX = x + cos(currentAngle);
                    double newY = y + sin(currentAngle);
                    lijnen.push_back(Line2D(Point2D(x, y), Point2D(newX, newY), lijnKleur));
                    x = newX;
                    y = newY;
                }
                break;
        }
        // Zorg dat de hoek binnen het bereik van 0 tot 2PI blijft
        currentAngle = fmod(currentAngle, 2 * PI);
        if (currentAngle < 0) currentAngle += 2 * PI; // Corrigeer negatieve hoek
    }
    return lijnen;
}

Matrix scaleFigure(const double scale){
    Matrix scaleMatrix = Matrix(); //matrix() maakt een 4x4 matrix aan met alle waarden op 0
    scaleMatrix(1,1) = scale;
    scaleMatrix(2,2) = scale;
    scaleMatrix(3,3) = scale;
    scaleMatrix(4,4) = 1;
    return scaleMatrix;
}
Matrix RotateX(const double angle){
    double radians = angle * (PI / 180.0);
    Matrix rotateMatrix = Matrix();
    rotateMatrix(1,1) = 1;
    rotateMatrix(2,2) = cos(radians);
    rotateMatrix(2,3) = sin(radians);
    rotateMatrix(3,2) = -sin(radians);
    rotateMatrix(3,3) = cos(radians);
    rotateMatrix(4,4) = 1;
    return rotateMatrix;
}

Matrix RotateY(const double angle){
    double radians = angle * (PI / 180.0);
    Matrix rotateMatrix = Matrix();
    rotateMatrix(1,1) = cos(radians);
    rotateMatrix(1,3) = -sin(radians);
    rotateMatrix(2,2) = 1;
    rotateMatrix(3,1) = sin(radians);
    rotateMatrix(3,3) = cos(radians);
    rotateMatrix(4,4) = 1;
    return rotateMatrix;
}

Matrix RotateZ(const double angle){
    double radians = angle * (PI / 180.0);
    Matrix rotateMatrix = Matrix();
    rotateMatrix(1,1) = cos(radians);
    rotateMatrix(1,2) = sin(radians);
    rotateMatrix(2,1) = -sin(radians);
    rotateMatrix(2,2) = cos(radians);
    rotateMatrix(3,3) = 1;
    rotateMatrix(4,4) = 1;
    return rotateMatrix;
}

Matrix translate(const Vector3D &vector){
    Matrix translateMatrix = Matrix();
    translateMatrix(1,1) = 1;
    translateMatrix(2,2) = 1;
    translateMatrix(3,3) = 1;
    translateMatrix(4,4) = 1;
    translateMatrix(1,4) = vector.x;
    translateMatrix(2,4) = vector.y;
    translateMatrix(3,4) = vector.z;
    return translateMatrix;
}

void applyTransformation(Figure &fig, const Matrix &m) {
for(auto &point:fig.points){
    Matrix newMatrix = m * translate(point);
    point.x = newMatrix(1,4);
    point.y = newMatrix(2,4);
    point.z = newMatrix(3,4);
}
}
void toPolar(const Vector3D &point, double &r, double &theta, double &phi){
    r = sqrt(pow(point.x,2) + pow(point.y,2) + pow(point.z,2));
    theta = atan2(point.y,point.x);
    phi = acos(point.z/r);
}

Matrix eyePointTrans(const Vector3D &eyepoint){
    Matrix eyePointMatrix = Matrix(); // Aanname: Matrix() initialiseert een 4x4 matrix met alle elementen op 0.
    double theta;
    double phi;
    double r;
    toPolar(eyepoint, r, theta, phi);
    eyePointMatrix(1,1) = -sin(theta);
    eyePointMatrix(1,2) = -cos(theta) * cos(phi);
    eyePointMatrix(1,3) = cos(theta) * sin(phi);
    eyePointMatrix(2,1) = cos(theta);
    eyePointMatrix(2,2) = -sin(theta) * cos(phi);
    eyePointMatrix(2,3) = sin(theta) * sin(phi);
    eyePointMatrix(3,2) = sin(phi);
    eyePointMatrix(3,3) = cos(phi);
    eyePointMatrix(4,3) = -r;
    eyePointMatrix(4,4) = 1;
    return eyePointMatrix;


}

void applyTransformation(Figures3D &figs, const Matrix &m){
    for(Figure &fig:figs){
        applyTransformation(fig, m);
    }
}

Point2D doProjection(const Vector3D &point, const double d = 1.0){
    return Point2D(point.x * d / point.z, point.y * d / point.z);
}
Lines2D doProjection(const Figures3D &fig){
    Lines2D lines;
    for(const Figure &figure:fig){
        for(const Face &face:figure.faces){
            for(int i = 0; i < face.point_indexes.size(); ++i){
                Vector3D point1 = figure.points[face.point_indexes[i]];
                Vector3D point2 = figure.points[face.point_indexes[(i+1)%face.point_indexes.size()]];
                lines.push_back(Line2D(Point2D(point1.x,point1.y),Point2D(point2.x,point2.y),figure.color));
            }
        }
    }
    return lines;
}


img::EasyImage Wireframe(const int size, const img::Color &background, const Vector3D &eye, Figures3D &figures, const int rotateX, const int rotateY, const int rotateZ, const double scale, const Vector3D &center) {
    // Voor elke figuur in de lijst van figuren
    for (auto &fig : figures) {
        // Maak de transformatiematrices aan
        Matrix scaleMatrix = scaleFigure(scale);
        Matrix rotateXMatrix = RotateX(rotateX); // Gebruik de meegegeven hoek
        Matrix rotateYMatrix = RotateY(rotateY); // Gebruik de meegegeven hoek
        Matrix rotateZMatrix = RotateZ(rotateZ); // Gebruik de meegegeven hoek
        Matrix translateToCenterMatrix = translate(-center); // Verplaats naar het centrum voor rotatie
        Matrix translateBackMatrix = translate(center); // Verplaats terug na rotatie
        Matrix translateMatrix = eyePointTrans(eye); // Verplaats naar de oogpositie

        // Combineer de transformaties
        Matrix totalMatrix = translateBackMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix * translateToCenterMatrix * translateMatrix;

        // Pas de gecombineerde transformatie toe op de figuur
        applyTransformation(fig, totalMatrix);
    }

    // Projecteer de 3D-figuren naar 2D-lijnen en teken ze
    return draw2DLines(doProjection(figures), size, background);
}


img::EasyImage generate_image(const ini::Configuration &confg) {

    std::string type = confg["General"]["type"].as_string_or_die();
    int width = 0;
    int height = 0;
    int size = 0;
    img::EasyImage image;


    if (type == "IntroColorRectangle") {
         width = confg["ImageProperties"]["width"].as_int_or_die();
         height = confg["ImageProperties"]["height"].as_int_or_die();
        img::EasyImage image(width, height);
        return ColorRectangle(type, width, height);
    }
    else if (type == "IntroBlocks") {
        ini::DoubleTuple colorWhite = confg["BlockProperties"]["colorWhite"].as_double_tuple_or_die();
        ini::DoubleTuple colorBlack = confg["BlockProperties"]["colorBlack"].as_double_tuple_or_die();
        int nxB = confg["BlockProperties"]["nrXBlocks"].as_int_or_die();
        int nyB = confg["BlockProperties"]["nrYBlocks"].as_int_or_die();
        bool invert = confg["BlockProperties"]["invertColors"].as_bool_or_die();

        return Blocks(type, width, height, colorWhite, colorBlack, nxB, nyB, invert);
    } else if (type == "IntroLines") {
        width = confg["ImageProperties"]["width"].as_int_or_die();
        height = confg["ImageProperties"]["height"].as_int_or_die();
        img::EasyImage image(width, height);
        std::string figure = confg["LineProperties"]["figure"];
        ini::DoubleTuple backGroundColor = confg["LineProperties"]["backgroundcolor"];
        ini::DoubleTuple lineColor = confg["LineProperties"]["lineColor"];
        int nrLines = confg["LineProperties"]["nrLines"];

        if (figure == "QuarterCircle") {
            return QuarterCircle(backGroundColor, lineColor, nrLines, height, width);
        }
        if (figure == "Eye") {
            return Eye(backGroundColor, lineColor, nrLines, height, width);
        }
        if (figure == "Diamond") {
            return Diamond(backGroundColor, lineColor, nrLines, height, width);
        }
    }
    else if (type == "drawLines"){
        Color rood = Color(1,0,0);
        Color groen = Color(0,1,0);
        Color blauw = Color(0,0,1);

        const Point2D oorsprong = Point2D(0.0,0.0);

        const Point2D pr1 = Point2D(100.0,100.0);
        const Point2D pg1 = Point2D(50.0,50.0);
        const Point2D pb1 = Point2D(300.0,-50.0);

        Line2D lijnRood = Line2D(oorsprong, pr1, rood);
        Line2D lijnGroen = Line2D(oorsprong, pg1, groen);
        Line2D lijnBlauw = Line2D(oorsprong, pb1, blauw);

        Lines2D lijnen = {lijnRood,lijnGroen,lijnBlauw};

        const int size = 500;


        return draw2DLines(lijnen,size);
    }
    else if(type == "2DLSystem" ){
        size = confg["General"]["size"];
        std::vector<double> BackGroundINI = confg["General"]["backgroundcolor"];
        img::Color backGroundColor = img::Color(BackGroundINI[0]*255, BackGroundINI[1]*255, BackGroundINI[2]*255);
        std::vector<double> LSystemINI = confg["2DLSystem"]["color"];
        Color LSystemColor = Color(LSystemINI[0], LSystemINI[1], LSystemINI[2]);

        LParser::LSystem2D l_system = DLSystem(confg);
        std::vector<Line2D> lines = drawLSystem(l_system,LSystemColor);
        return draw2DLines(lines,size,backGroundColor);
    }
    else if(type == "Wireframe"){
        size = confg["General"]["size"];
        ini::DoubleTuple BackGroundINI = confg["General"]["backgroundcolor"];
        img::Color backGroundColor = img::Color(BackGroundINI[0]*255, BackGroundINI[1]*255, BackGroundINI[2]*255);
        int nrOfFigures = confg["General"]["nrFigures"].as_int_or_die();
        ini::DoubleTuple eyeCordsINI = confg["General"]["eye"];
        Vector3D eyeCords = Vector3D::point(eyeCordsINI[0], eyeCordsINI[1], eyeCordsINI[2]);

        Figures3D figures3D;
        int rotateX;
        int rotateY;
        int rotateZ;
        double scale;
        Vector3D center;
        for (unsigned int i = 0; i < nrOfFigures; ++i) {
            std::string figureString = "Figure" + std::to_string(i);
            std::string type2 = confg[figureString]["type"];

            Figure figure = Figure(Color(confg[figureString]["color"].as_double_tuple_or_die()[0], confg[figureString]["color"].as_double_tuple_or_die()[1], confg[figureString]["color"].as_double_tuple_or_die()[2]));

            if(type2 == "LineDrawing"){
                 rotateX = confg[figureString]["rotateX"].as_int_or_die();
                 rotateY = confg[figureString]["rotateY"].as_int_or_die();
                 rotateZ = confg[figureString]["rotateZ"].as_int_or_die();
                 scale = confg[figureString]["scale"].as_double_or_die();
                Color figureColor = Color(confg[figureString]["color"].as_double_tuple_or_die()[0], confg[figureString]["color"].as_double_tuple_or_die()[1], confg[figureString]["color"].as_double_tuple_or_die()[2]);
                 center = Vector3D::point(confg[figureString]["center"].as_double_tuple_or_die()[0], confg[figureString]["center"].as_double_tuple_or_die()[1], confg[figureString]["center"].as_double_tuple_or_die()[2]);
                int nrPoints = confg[figureString]["nrPoints"].as_int_or_die();
                int nrLines = confg[figureString]["nrLines"].as_int_or_die();
                for(int j = 0; j < nrPoints; ++j){
                    std::string point = "point" + std::to_string(j);
                    figure.points.push_back(Vector3D::point(confg[figureString][point].as_double_tuple_or_die()[0], confg[figureString][point].as_double_tuple_or_die()[1], confg[figureString][point].as_double_tuple_or_die()[2]));
                }
                for(int j = 0; j < nrLines; ++j){
                    std::string Line = "line" + std::to_string(j);
                    std::vector<int> pointIndexes = {};
                    confg[figureString][Line].as_int_tuple_or_die();
                    pointIndexes.push_back(confg[figureString][Line].as_int_tuple_or_die()[0]);
                    pointIndexes.push_back(confg[figureString][Line].as_int_tuple_or_die()[1]);
                    figure.faces.push_back(Face(pointIndexes));
                }
                figures3D.push_back(figure);
            }

        }
        return Wireframe(size, backGroundColor, eyeCords, figures3D, rotateX, rotateY, rotateZ, scale, center);
    }


        return image;
    }

    int main(int argc, char const *argv[]) {
        int retVal = 0;
        try {
            std::vector<std::string> args = std::vector<std::string>(argv + 1, argv + argc);
            if (args.empty()) {
                std::ifstream fileIn("filelist");
                std::string filelistName;
                while (std::getline(fileIn, filelistName)) {
                    args.push_back(filelistName);
                }
            }
            for (std::string fileName: args) {
                ini::Configuration conf;
                try {
                    std::ifstream fin(fileName);
                    if (fin.peek() == std::istream::traits_type::eof()) {
                        std::cout << "Ini file appears empty. Does '" <<
                                  fileName << "' exist?" << std::endl;
                        continue;
                    }
                    fin >> conf;
                    fin.close();
                }
                catch (ini::ParseException &ex) {
                    std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                    retVal = 1;
                    continue;
                }

                img::EasyImage image = generate_image(conf);
                if (image.get_height() > 0 && image.get_width() > 0) {
                    std::string::size_type pos = fileName.rfind('.');
                    if (pos == std::string::npos) {
                        //filename does not contain a '.' --> append a '.bmp' suffix
                        fileName += ".bmp";
                    } else {
                        fileName = fileName.substr(0, pos) + ".bmp";
                    }
                    try {
                        std::ofstream f_out(fileName.c_str(), std::ios::trunc | std::ios::out | std::ios::binary);
                        f_out << image;

                    }
                    catch (std::exception &ex) {
                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                        retVal = 1;
                    }
                } else {
                    std::cout << "Could not generate image for " << fileName << std::endl;
                }
            }
        }
        catch (const std::bad_alloc &exception) {
            //When you run out of memory this exception is thrown. When this happens the return value of the program MUST be '100'.
            //Basically this return value tells our automated test scripts to run your engine on a pc with more memory.
            //(Unless of course you are already consuming the maximum allowed amount of memory)
            //If your engine does NOT adhere to this requirement you risk losing points because then our scripts will
            //mark the test as failed while in reality it just needed a bit more memory
            std::cerr << "Error: insufficient memory" << std::endl;
            retVal = 100;
        }

        return retVal;
    }

