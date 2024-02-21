//
// Created by student on 21/02/24.
//

#include "introduction.h"
#include <cmath>


img::EasyImage ColorRectangle(const std::string &type,const int &w, const int &h){
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


img::EasyImage Blocks(const std::string &type, const int &w, const int &h, const ini::DoubleTuple &cw, const ini::DoubleTuple &cb, const int &nxB, const int &nyB, bool &invert ){
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

img::EasyImage QuarterCircle(const ini::DoubleTuple backGroundColor, const ini::DoubleTuple lineColor, int nrLines, const int height, const int width) {
    nrLines = nrLines - 1;
    int Hs = height / nrLines; //hoogte van het rechthoekje
    int Ws = width / nrLines; //breedte van het rechthoekje


    img::EasyImage image(width, height,
                         img::Color(backGroundColor[0] * 255, backGroundColor[1] * 255, backGroundColor[2] * 255));
    int counter = 0;
    int x0 = 0;
    int y0 = 0;
    int x1 = 0;
    int y1 = height - 1;
    while (counter <= nrLines) {
        if (x1 == height){
            x1 = height - 1;
        }
        if (y0 == height){
            y0 = height - 1;
        }

        if (std::make_tuple(x0, y0) == std::make_tuple(x1, y1)) {
            x0 += Hs;
            y1 += Ws;

        } else {
            image.draw_line(x0, y0, x1, y1, img::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            y0 += Hs;
            x1 += Ws;
        }

        counter++;
    }
    return image;
}



img::EasyImage Eye(ini::DoubleTuple backGroundColor, ini::DoubleTuple lineColor, int nrLines, int height, int width) {
    nrLines = nrLines - 1;
    int Hs = height / nrLines; //hoogte van het rechthoekje
    int Ws = width / nrLines; //breedte van het rechthoekje


    img::EasyImage image(width, height,
                         img::Color(backGroundColor[0] * 255, backGroundColor[1] * 255, backGroundColor[2] * 255));
    //eerste (linkse)
    int counter = 0;
    int x0 = 0;
    int y0 = 0;
    int x1 = 0;
    int y1 = height - 1;



    while (counter <= nrLines) {
        if (x1 == width){
            x1 = width - 1;
        }
        if (y0 == height){
            y0 = height - 1;
        }

        if (std::make_tuple(x0, y0) == std::make_tuple(x1, y1)) {
            x0 += Hs;
            y1 += Ws;

        } else {
            image.draw_line(x0, y0, x1, y1, img::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            y0 += Hs;
            x1 += Ws;
        }


        counter++;
    }


//    tweede (rechtse)
    int counter2 = 0;
    const int y2 = 0;
    const int x3 = width -1;

    int x2 = 0;
    int y3 = 0;

    while (counter2 <= nrLines) {
        if (x2 == width){
            x2 = width - 1;
        }
        if (y3 == height){
            y3 = height - 1;
        }

        if (std::make_tuple(x2, y2) == std::make_tuple(x3, y3)) {
            x2 += Ws;
            y3 += Hs;


        } else {
            image.draw_line(x2, y2, x3, y3, img::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
            x2 += Ws;
            y3 += Hs;
        }


        counter2++;
    }

    return image;
}


img::EasyImage Diamond(ini::DoubleTuple backGroundColor, ini::DoubleTuple lineColor, int nrLines, int height, int width) {
    nrLines = nrLines - 1;
    int Hs = height / (2 * nrLines); //hoogte van het rechthoekje
    int Ws = width / (2 * nrLines); //breedte van het rechthoekje


    img::EasyImage image(width, height,
                         img::Color(backGroundColor[0] * 255, backGroundColor[1] * 255, backGroundColor[2] * 255));

    //horizontaal
    int x0 = 0;
    int x4 = width - 1;
    const int y0 = height / 2;

    //verticaal
    const int x1 = width / 2;
    int y1 = height / 2;
    int y2 = height / 2 ;

    int counter = 0;

    while (counter <= nrLines) {
        x0 = width/2 + counter * Ws;
        y1 = height/2 + counter * Hs;
        y2 = height/2 - counter * Hs;
        x4 = (width-1) - counter * Ws;

        if(x4 < 0){
            x4 = 0;
        }
        if(x0 == width){
            x0 = width -1;
        }
        if(y1 == height){
            y1 = height -1;
        }

        x0 = counter * Ws;


        image.draw_line(x0, y0, x1, y1, img::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        image.draw_line(x4, y0, x1, y1, img::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));


        image.draw_line(x0, y0, x1, y2, img::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));
        image.draw_line(x4, y0, x1, y2, img::Color(lineColor[0] * 255, lineColor[1] * 255, lineColor[2] * 255));

        counter ++;
    }
    return image;
}

