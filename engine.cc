#define _USE_MATH_DEFINES



#include "easy_image.h"
#include "ini_configuration.h"
#include "Color1.h"
#include "Point2D.h"
#include "Line2D.h"
#include "introduction.h"
#include "l_parser.h"
#include "vector3d.h"
#include "Figure.h"
#include "Face.h"
#include "PlatonischeLichamen.h"
#include "translations.h"
#include <set>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stack>
#include <ctime>
#include <string>
#include "draw3DLsystem.h"
#include "Wireframes.h"
#include "ZBuffering.h"
#include "lightedZbuffering.h"




img::EasyImage draw2DLines(const Lines2D &lines, const int size, img::Color background = img::Color(0, 0, 0), bool zBuffer = false) {
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

    double d = 0.95 * (width / x_range);

    double DCx = d * ((x_min + x_max) / 2);
    double DCy = d * ((y_min + y_max) / 2);

    double dx = width / 2 - DCx;
    double dy = height / 2 - DCy;

    ZBuffer Zbuf = ZBuffer(width, height);

    for (Line2D lijn:lines) {
        lijn.p1.x = round(lijn.p1.x * d + dx);
        lijn.p1.y = round(lijn.p1.y * d + dy);
        lijn.p2.x = round(lijn.p2.x * d + dx);
        lijn.p2.y = round(lijn.p2.y * d + dy);

        img::Color kleur = img::Color(lijn.color.red*255,lijn.color.green*255,lijn.color.blue*255);

        if(zBuffer){
            image.draw_zbuf_line(Zbuf, lijn.p1.x, lijn.p1.y, lijn.z1, lijn.p2.x, lijn.p2.y, lijn.z2, kleur);
        }
        else{
            image.draw_line(lijn.p1.x,lijn.p1.y,lijn.p2.x,lijn.p2.y, kleur);
        }

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

Lines2D drawLSystem(const LParser::LSystem2D &l_system, Color1 lijnKleur = Color1(255, 255, 255)) {
    srand(static_cast<unsigned int>(time(0)));
    Lines2D lijnen;
    double x = 0, y = 0; // Startpositie
    double angle = l_system.get_angle() * (M_PI / 180.0); // Omrekenen naar radialen
    double currentAngle = l_system.get_starting_angle() * (M_PI / 180.0); // Start hoek in radialen
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
        currentAngle = fmod(currentAngle, 2 * M_PI);
        if (currentAngle < 0) currentAngle += 2 * M_PI; // Corrigeer negatieve hoek
    }
    return lijnen;
}




img::EasyImage createWireFrame(int size, img::Color color, Vector3D eyeCords, Figures3D figures, bool zBuffer = false){
    return draw2DLines(doProjection(figures), size, color, zBuffer);
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
    }
    else if (type == "IntroLines") {
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
        Color1 rood = Color1(1, 0, 0);
        Color1 groen = Color1(0, 1, 0);
        Color1 blauw = Color1(0, 0, 1);

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
        Color1 LSystemColor = Color1(LSystemINI[0], LSystemINI[1], LSystemINI[2]);

        LParser::LSystem2D l_system = DLSystem(confg);
        std::vector<Line2D> lines = drawLSystem(l_system,LSystemColor);
        return draw2DLines(lines,size,backGroundColor);
    }
    else if(type == "Wireframe"){

        size = confg["General"]["size"];

        img::Color backGroundColor = img::Color();
        Vector3D eyeCords = Vector3D();

        Figures3D figures3D = configure3D(confg,size,backGroundColor,eyeCords);

        return createWireFrame(size, backGroundColor, eyeCords, figures3D);
    }
    else if(type == "ZBufferedWireframe"){
        size = confg["General"]["size"];

        img::Color backGroundColor = img::Color();
        Vector3D eyeCords = Vector3D();

        Figures3D figures3D = configure3D(confg,size,backGroundColor,eyeCords);


        return createWireFrame(size, backGroundColor, eyeCords, figures3D, true);
    }
    else if(type == "ZBuffering"){
        return zBuffering(confg);
    }

    else if (type == "LightedZBuffering"){
        return lightedZBuffering( confg);
    }

    return image;
}





int count = 1;
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
            std::cout << "Generating image " << count++ << " from " << fileName << std::endl;
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