#include "easy_image.h"
#include "ini_configuration.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>


using namespace std;

img::EasyImage ColorRectangle(const string &type,const int &w, const int &h){
    img::EasyImage image(w,h);
        for(unsigned int i = 0; i < w; i++)
        {
            for(unsigned int j = 0; j < h; j++)
            {
                image(i,j).red = i;
                image(i,j).green = j;
                image(i,j).blue = (i+j)%256;
            }
        }
        return image;
    }


img::EasyImage Blocks(const string &type, const int &w, const int &h, const ini::DoubleTuple &cw, const ini::DoubleTuple &cb, const int &nxB, const int &nyB, bool &invert ){
    int wb = w/nxB;
    int hb = h/nyB;

    img::EasyImage image(w,h);

    for(unsigned int i = 0; i < w; i++)
    {
        for(unsigned int j = 0; j < h; j++)
        {
            int Bx = floor(i/wb);
            int By = floor(j/hb);
            bool even = true;
            if((Bx + By) % 2 != 0 ){
                even = false;
            }
            if(!invert){
                if(even){
                    even = false;
                } else{
                    even = true;
                }
            }
            if(not even){
                image(i,j).red = cw[0] * 255;
                image(i,j).green = cw[1] * 255;
                image(i,j).blue = cw[2] * 255;
            } else{
                image(i,j).red = cb[0] * 255;
                image(i,j).green = cb[1] * 255;
                image(i,j).blue = cb[2] * 255;
            }
        }
    }

    return image;
}

img::EasyImage generate_image(const ini::Configuration &confg)
{

    std::string type = confg["General"]["type"].as_string_or_die();
    int w = confg["ImageProperties"]["width"].as_int_or_die();
    int h = confg["ImageProperties"]["height"].as_int_or_die();

    img::EasyImage image(w,h);

    if(type == "IntroColorRectangle"){
        return ColorRectangle(type, w, h);
    }
    else if (type == "IntroBlocks"){
        ini::DoubleTuple colorWhite = confg["BlockProperties"]["colorWhite"].as_double_tuple_or_die();
        ini::DoubleTuple colorBlack = confg["BlockProperties"]["colorBlack"].as_double_tuple_or_die();
        int nxB = confg["BlockProperties"]["nrXBlocks"].as_int_or_die();
        int nyB = confg["BlockProperties"]["nrYBlocks"].as_int_or_die();
        bool invert = confg["BlockProperties"]["invertColors"].as_bool_or_die();

        return Blocks(type, w, h, colorWhite, colorBlack, nxB, nyB, invert);
    }
    return image;
}







int main(int argc, char const* argv[]){
        int retVal = 0;
        try
        {
                std::vector<std::string> args = std::vector<std::string>(argv+1, argv+argc);
                if (args.empty()) {
                        std::ifstream fileIn("filelist");
                        std::string filelistName;
                        while (std::getline(fileIn, filelistName)) {
                                args.push_back(filelistName);
                        }
                }
                for(std::string fileName : args)
                {
                        ini::Configuration conf;
                        try
                        {
                                std::ifstream fin(fileName);
                                if (fin.peek() == std::istream::traits_type::eof()) {
                                    std::cout << "Ini file appears empty. Does '" <<
                                    fileName << "' exist?" << std::endl;
                                    continue;
                                }
                                fin >> conf;
                                fin.close();
                        }
                        catch(ini::ParseException& ex)
                        {
                                std::cerr << "Error parsing file: " << fileName << ": " << ex.what() << std::endl;
                                retVal = 1;
                                continue;
                        }

                        img::EasyImage image = generate_image(conf);
                        if(image.get_height() > 0 && image.get_width() > 0)
                        {
                                std::string::size_type pos = fileName.rfind('.');
                                if(pos == std::string::npos)
                                {
                                        //filename does not contain a '.' --> append a '.bmp' suffix
                                        fileName += ".bmp";
                                }
                                else
                                {
                                        fileName = fileName.substr(0,pos) + ".bmp";
                                }
                                try
                                {
                                        std::ofstream f_out(fileName.c_str(),std::ios::trunc | std::ios::out | std::ios::binary);
                                        f_out << image;

                                }
                                catch(std::exception& ex)
                                {
                                        std::cerr << "Failed to write image to file: " << ex.what() << std::endl;
                                        retVal = 1;
                                }
                        }
                        else
                        {
                                std::cout << "Could not generate image for " << fileName << std::endl;
                        }
                }
        }
        catch(const std::bad_alloc &exception)
        {
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
