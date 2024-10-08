/*
 * easy_image.cc
 * Copyright (C) 2011  Daniel van den Akker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terreflection_coefficient of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "easy_image.h"
#include <algorithm>
#include <assert.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <cmath>

#ifndef le32toh
#define le32toh(x) (x)
#endif

namespace
{
	//structs borrowed from wikipedia's article on the BMP file format
	struct bmpfile_magic
	{
			uint8_t magic[2];
	};

	struct bmpfile_header
	{
			uint32_t file_size;
			uint16_t reserved_1;
			uint16_t reserved_2;
			uint32_t bmp_offset;
	};
	struct bmp_header
	{
			uint32_t header_size;
			int32_t width;
			int32_t height;
			uint16_t nplanes;
			uint16_t bits_per_pixel;
			uint32_t compress_type;
			uint32_t pixel_size;
			int32_t hres;
			int32_t vres;
			uint32_t ncolors;
			uint32_t nimpcolors;
	};
	//copy-pasted from lparser.cc to allow these classes to be used independently from each other
	class enable_exceptions
	{
		private:
			std::ios& ios;
			std::ios::iostate state;
		public:
			enable_exceptions(std::ios& an_ios, std::ios::iostate exceptions) :
				ios(an_ios)
			{
				state = ios.exceptions();
				ios.exceptions(exceptions);
			}
			~enable_exceptions()
			{
				ios.exceptions(state);
			}
	};
	//helper function to convert a number (char, int, ...) to little endian
	//regardless of the endiannes of the system
	//more efficient machine-dependent functions exist, but this one is more portable
	template<typename T> T to_little_endian(T value)
	{
		//yes, unions must be used with caution, but this is a case in which a union is needed
		union
		{
				T t;
				uint8_t bytes[sizeof(T)];
		} temp_storage;

		for (uint8_t i = 0; i < sizeof(T); i++)
		{
			temp_storage.bytes[i] = value & 0xFF;
			value >>= 8;
		}
		return temp_storage.t;
	}

	template<typename T> T from_little_endian(T value)
	{
		//yes, unions must be used with caution, but this is a case in which a union is needed
		union
		{
				T t;
				uint8_t bytes[sizeof(T)];
		} temp_storage;
		temp_storage.t = value;
		T retVal = 0;

		for (uint8_t i = 0; i < sizeof(T); i++)
		{
			retVal = (retVal << 8) | temp_storage.bytes[sizeof(T) - i - 1];
		}
		return retVal;
	}

}
int i = 0;

double calcDouble(double value){
	value = value/255;
	return value;
}
img::Color::Color() :
	blue(0), green(0), red(0)
{
}
img::Color::Color(uint8_t r, uint8_t g, uint8_t b) :
	blue(b), green(g), red(r)
{
}
img::Color::~Color()
{
}

img::UnsupportedFileTypeException::UnsupportedFileTypeException(std::string const& reflection_coefficientg) :
	message(reflection_coefficientg)
{
}
img::UnsupportedFileTypeException::UnsupportedFileTypeException(const UnsupportedFileTypeException &original)
: std::exception(original)
, message(original.message)
{
}
img::UnsupportedFileTypeException::~UnsupportedFileTypeException() throw ()
{
}
img::UnsupportedFileTypeException& img::UnsupportedFileTypeException::operator=(UnsupportedFileTypeException const& original)
{
	this->message = original.message;
	return *this;
}
const char* img::UnsupportedFileTypeException::what() const throw ()
{
	return message.c_str();
}

img::EasyImage::EasyImage() :
	width(0), height(0), bitmap()
{
}

img::EasyImage::EasyImage(unsigned int _width, unsigned int _height, Color color) :
	width(_width), height(_height), bitmap(width * height, color)
{
}

img::EasyImage::EasyImage(EasyImage const& img) :
	width(img.width), height(img.height), bitmap(img.bitmap)
{
}

img::EasyImage::~EasyImage()
{
	bitmap.clear();
}

img::EasyImage& img::EasyImage::operator=(img::EasyImage const& img)
{
	width = img.width;
	height = img.height;
	bitmap.assign(img.bitmap.begin(),img.bitmap.end());
	return (*this);
}

unsigned int img::EasyImage::get_width() const
{
	return width;
}

unsigned int img::EasyImage::get_height() const
{
	return height;
}

void img::EasyImage::clear(Color color)
{
	for (std::vector<Color>::iterator i = bitmap.begin(); i != bitmap.end(); i++)
	{
		*i = color;
	}
}

img::Color& img::EasyImage::operator()(unsigned int x, unsigned int y)
{
	assert(x < this->width);
	assert(y < this->height);
	return bitmap.at(x * height + y);
}

img::Color const& img::EasyImage::operator()(unsigned int x, unsigned int y) const
{
	assert(x < this->width);
	assert(y < this->height);
	return bitmap.at(x * height + y);
}
void img::EasyImage::draw_line(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, Color color)

{
	if (x0 >= this->width || y0 >= this->height || x1 >= this->width || y1 > this->height) {
        std::stringstream ss;
        ss << "Drawing line from (" << x0 << "," << y0 << ") to (" << x1 << "," << y1 << ") in image of width "
        << this->width << " and height " << this->height;
        throw std::runtime_error(ss.str());
    }
	if (x0 == x1)
	{
		//special case for x0 == x1
		for (unsigned int i = std::min(y0, y1); i <= std::max(y0, y1); i++)
		{
			(*this)(x0, i) = color;
		}
	}
	else if (y0 == y1)
	{
		//special case for y0 == y1
		for (unsigned int i = std::min(x0, x1); i <= std::max(x0, x1); i++)
		{
			(*this)(i, y0) = color;
		}
	}
	else
	{
		if (x0 > x1)
		{
			//flip points if x1>x0: we want x0 to have the lowest value
			std::swap(x0, x1);
			std::swap(y0, y1);
		}
		double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);
		if (-1.0 <= m && m <= 1.0)
		{
			for (unsigned int i = 0; i <= (x1 - x0); i++)
			{
				(*this)(x0 + i, (unsigned int) round(y0 + m * i)) = color;
			}
		}
		else if (m > 1.0)
		{
			for (unsigned int i = 0; i <= (y1 - y0); i++)
			{
				(*this)((unsigned int) round(x0 + (i / m)), y0 + i) = color;
			}
		}
		else if (m < -1.0)
		{
			for (unsigned int i = 0; i <= (y0 - y1); i++)
			{
				(*this)((unsigned int) round(x0 - (i / m)), y0 - i) = color;
			}
		}
	}
}
std::ostream& img::operator<<(std::ostream& out, EasyImage const& image)
{

	//temporaryily enable exceptions on output stream
	enable_exceptions(out, std::ios::badbit | std::ios::failbit);
	//declare some struct-vars we're going to need:
	bmpfile_magic magic;
	bmpfile_header file_header;
	bmp_header header;
	uint8_t padding[] =
	{ 0, 0, 0, 0 };
	//calculate the total size of the pixel data
	unsigned int line_width = image.get_width() * 3; //3 bytes per pixel
	unsigned int line_padding = 0;
	if (line_width % 4 != 0)
	{
		line_padding = 4 - (line_width % 4);
	}
	//lines must be aligned to a multiple of 4 bytes
	line_width += line_padding;
	unsigned int pixel_size = image.get_height() * line_width;

	//start filling the headers
	magic.magic[0] = 'B';
	magic.magic[1] = 'M';

	file_header.file_size = to_little_endian(pixel_size + sizeof(file_header) + sizeof(header) + sizeof(magic));
	file_header.bmp_offset = to_little_endian(sizeof(file_header) + sizeof(header) + sizeof(magic));
	file_header.reserved_1 = 0;
	file_header.reserved_2 = 0;
	header.header_size = to_little_endian(sizeof(header));
	header.width = to_little_endian(image.get_width());
	header.height = to_little_endian(image.get_height());
	header.nplanes = to_little_endian(1);
	header.bits_per_pixel = to_little_endian(24);//3bytes or 24 bits per pixel
	header.compress_type = 0; //no compression
	header.pixel_size = pixel_size;
	header.hres = to_little_endian(11811); //11811 pixels/meter or 300dpi
	header.vres = to_little_endian(11811); //11811 pixels/meter or 300dpi
	header.ncolors = 0; //no color palette
	header.nimpcolors = 0;//no important colors

	//okay that should be all the header stuff: let's write it to the stream
	out.write((char*) &magic, sizeof(magic));
	out.write((char*) &file_header, sizeof(file_header));
	out.write((char*) &header, sizeof(header));

	//okay let's write the pixels thereflection_coefficientelves:
	//they are arranged left->right, bottom->top, b,g,r
	for (unsigned int i = 0; i < image.get_height(); i++)
	{
		//loop over all lines
		for (unsigned int j = 0; j < image.get_width(); j++)
		{
			//loop over all pixels in a line
			//we cast &color to char*. since the color fields are ordered blue,green,red they should be written automatically
			//in the right order
			out.write((char*) &image(j, i), 3 * sizeof(uint8_t));
		}
		if (line_padding > 0)
			out.write((char*) padding, line_padding);
	}
	//okay we should be done
	return out;
}
std::istream& img::operator>>(std::istream& in, EasyImage & image)
{
	enable_exceptions(in, std::ios::badbit | std::ios::failbit);
	//declare some struct-vars we're going to need
	bmpfile_magic magic;
	bmpfile_header file_header;
	bmp_header header;
	//a temp buffer for reading the padding at the end of each line
	uint8_t padding[] =
	{ 0, 0, 0, 0 };

	//read the headers && do some sanity checks
	in.read((char*) &magic, sizeof(magic));
	if (magic.magic[0] != 'B' || magic.magic[1] != 'M')
		throw UnsupportedFileTypeException("Could not parse BMP File: invalid magic header");
	in.read((char*) &file_header, sizeof(file_header));
	in.read((char*) &header, sizeof(header));
	if (le32toh(header.pixel_size) + le32toh(file_header.bmp_offset) != le32toh(file_header.file_size))
		throw UnsupportedFileTypeException("Could not parse BMP File: file size mismatch");
	if (le32toh(header.header_size) != sizeof(header))
		throw UnsupportedFileTypeException("Could not parse BMP File: Unsupported BITMAPV5HEADER size");
	if (le32toh(header.compress_type) != 0)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only uncompressed BMP files can be parsed");
	if (le32toh(header.nplanes) != 1)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only one plane should exist in the BMP file");
	if (le32toh(header.bits_per_pixel) != 24)
		throw UnsupportedFileTypeException("Could not parse BMP File: Only 24bit/pixel BMP's are supported");
	//if height<0 -> read top to bottom instead of bottom to top
	bool invertedLines = from_little_endian(header.height) < 0;
	image.height = std::abs(from_little_endian(header.height));
	image.width = std::abs(from_little_endian(header.width));
	unsigned int line_padding = from_little_endian(header.pixel_size) / image.height - (3 * image.width);
	//re-initialize the image bitmap
	image.bitmap.clear();
	image.bitmap.assign(image.height * image.width, Color());
	//okay let's read the pixels thereflection_coefficientelves:
	//they are arranged left->right., bottom->top if height>0, top->bottom if height<0, b,g,r
	for (unsigned int i = 0; i < image.get_height(); i++)
	{
		//loop over all lines
		for (unsigned int j = 0; j < image.get_width(); j++)
		{
			//loop over all pixels in a line
			//we cast &color to char*. since the color fields are ordered blue,green,red, the data read should be written in the right variables
			if (invertedLines)
			{
				//store top-to-bottom
				in.read((char*) &image(j, image.height - 1 - i), 3 * sizeof(uint8_t));
			}
			else
			{
				//store bottom-to-top
				in.read((char*) &image(j, i), 3 * sizeof(uint8_t));
			}
		}
		if (line_padding > 0)
		{
			in.read((char*) padding, line_padding);
		}
	}
	//okay we're done
	return in;
}

int test_count = 0;
void img::EasyImage::draw_zbuf_line(ZBuffer &f, unsigned int x0, unsigned int y0, double z0,
                                    unsigned int x1, unsigned int y1, double z1, img::Color color) {

    if (x0 == x1)
    {
        double min = std::min(y0, y1);
        double max = std::max(y0, y1);
        double a = max - min;
        for (unsigned int i = min; i <= max; i++)
        {
            double p = (a - (i - min))/a;
            double zi = p/z0 + (1 - p)/z1;
            if((zi) < (f.v[x0][i])){
                (*this)(x0, i) = color;
                f.v[x0][i] = zi;
            	//std::cout << "x0: " << x0 << " y0: " << i << " z: " << zi << std::endl;

            }
        }
    }
    else if (y0 == y1)
    {
        double min = std::min(x0, x1);
        double max = std::max(x0, x1);
        double a = max - min;
        for (unsigned int i = min; i <= max; i++)
        {
            double p = (a - (i - min))/a;
            double zi = p/z0 + (1 - p)/z1;
            if((zi) < (f.v[i][y0])){
                (*this)(i, y0) = color;
                f.v[i][y0] = zi;
            	//std::cout << "x0: " << x0 << " y0: " << i << " z: " << zi << std::endl;

            }
        }
    }
    else
    {
        if (x0 > x1)
        {
            std::swap(x0, x1);
            std::swap(y0, y1);
            std::swap(z0, z1);
            }
        double m = ((double) y1 - (double) y0) / ((double) x1 - (double) x0);
        if (-1.0 <= m && m <= 1.0)
        {
            double a = (x1 - x0);
            for (unsigned int i = 0; i <= (x1 - x0); i++)
            {
                double p = (a - i)/a;
                double zi = p/z0 + (1 - p)/z1;
                if((zi) < (f.v[x0 + i][(unsigned int) round(y0 + m * i)])){
                    (*this)(x0 + i, (unsigned int) round(y0 + m * i)) = color;
                    f.v[x0 + i][(unsigned int) round(y0 + m * i)] = zi;
                	//std::cout << "x0: " << x0 << " y0: " << i << " z: " << zi << std::endl;

                }
            }
        }
        else if (m > 1.0)
        {
            double a = (y1 - y0);
            for (unsigned int i = 0; i <= (y1 - y0); i++)
            {
                double p = (a - i)/a;
                double zi = p/z0 + (1 - p)/z1;
                if((zi) < (f.v[(unsigned int) round(x0 + (i / m))][y0 + i])){
                    (*this)((unsigned int) round(x0 + (i / m)), y0 + i) = color;
                    f.v[(unsigned int) round(x0 + (i / m))][y0 + i] = zi;
                	// std::cout << "x0: " << x0 << " y0: " << i << " z: " << zi << std::endl;

                }
            }
        }
        else if (m < -1.0)
        {
            double a = (y0 - y1);
            for (unsigned int i = 0; i <= a; i++)
            {
                double p = (a - i)/a;
                double zi = p/z0 + (1 - p)/z1;
                if((zi) < (f.v[(unsigned int) round(x0 - (i / m))][y0 - i])){
                    (*this)((unsigned int) round(x0 - (i / m)), y0 - i) = color;
                    f.v[(unsigned int) round(x0 - (i / m))][y0 - i] = zi;
                	// std::cout << "x0: " << x0 << " y0: " << i << " z: " << zi << std::endl;
                }
            }
        }
    }
	// std::cout << "test_count: " << test_count << std::endl;
	// test_count++;

}



img::Color img::EasyImage::get_color_after_lights(img::Color &ambientColor,img::Color &diffuseReflection , Lights3D &lights, Vector3D w) {

	Color newColor(0.0,0.0,0.0);
	Vector3D n = Vector3D::normalise(w);
	for(auto it = lights.begin(); it != lights.end(); it++){
		double redDiffuse = 0;
		double greenDiffuse = 0;
		double blueDiffuse= 0;
		if(it->infinity) {
			double cosA = (n.x * it->ldVector.x) + (n.y * it->ldVector.y) + (n.z * it->ldVector.z);
			if(cosA > 0){
				redDiffuse = ((diffuseReflection.red) * (it)->diffuseLight.red) * cosA;
				greenDiffuse = ((diffuseReflection.green) * (it)->diffuseLight.green) * cosA;
				blueDiffuse = ((diffuseReflection.blue) * (it)->diffuseLight.blue) * cosA;
			}
		}
		newColor.red = newColor.red + redDiffuse;
		newColor.green = newColor.green + greenDiffuse;
		newColor.blue = newColor.blue + blueDiffuse;
	}
	newColor.red = newColor.red + ambientColor.red;
	newColor.green = newColor.green + ambientColor.green;
	newColor.blue = newColor.blue + ambientColor.blue;

	return newColor;
}

img::Color img::EasyImage::get_diffuse_point_color(const Color &colorAfterLights, const Color &diffuseLightColor,
	const Color &specularLightColor, const Lights3D &lights, const Vector3D &w, double x, double y,
	double z, double d, double reflection_coefficient) {

	// if(i == 63792) {
	// 	std::cout<< "help" << std::endl;
	// }

	Color newColor(0.0,0.0,0.0);
    Vector3D n = Vector3D::normalise(w); //Normal vector

    double Ze = 1/(double)z;
    double Xe = (x * (-Ze))/(d);
    double Ye = (y * (-Ze))/(d);
    Vector3D PointP = Vector3D::point(Xe, Ye, Ze);

    for(auto it = lights.begin(); it != lights.end(); it++){
        double redDiffuse = 0;
        double greenDiffuse = 0;
        double blueDiffuse= 0;
        double redReflect = 0;
        double greenReflect = 0;
        double blueReflect = 0;

        if((*it).lightType == point) { //als het een point light is dan moet je de spotangle berekenen
            double As = ((*it).spotAngle) * (M_PI/180);
            Vector3D location = (*it).location;
            Vector3D vectorL = Vector3D::normalise(location - PointP);

            double cosA = (n.x * vectorL.x) + (n.y * vectorL.y) + (n.z * vectorL.z);
            if(cosA > 0){
                double Angle = 0;
                if((*it).spotAngle != 360 && cosA > cos(As)){ //360 is standaard
                    Angle = 1-(1-cosA)/(1-cos(As));
                }
                else if((*it).spotAngle == 360){
                    Angle = cosA;
                }

            	double diffRed = calcDouble(diffuseLightColor.red);
            	double diffGreen = calcDouble(diffuseLightColor.green);
            	double diffBlue = calcDouble(diffuseLightColor.blue);

                redDiffuse = diffRed * (*it).diffuseLight.red * Angle;
                greenDiffuse = diffGreen * (*it).diffuseLight.green * Angle;
                blueDiffuse = diffBlue * (*it).diffuseLight.blue * Angle;


            	Vector3D cam = Vector3D::normalise(-PointP);
                Vector3D r  = Vector3D::normalise(2 * n * cosA - vectorL); //reflection vector

            	double cosB = (r.x * cam.x) + (r.y * cam.y) + (r.z * cam.z);

            	double specRed = calcDouble(specularLightColor.red);
            	double specGreen = calcDouble(specularLightColor.green);
            	double specBlue = calcDouble(specularLightColor.blue);

                if(cosB > 0){
                    cosB = pow(cosB,reflection_coefficient); //reflection coefficient
                    redReflect = specRed * (*it).specularLight.red * cosB;
                    greenReflect = specGreen * (*it).specularLight.green * cosB;
                    blueReflect = specBlue * (*it).specularLight.blue * cosB;
                }
            }
            newColor.red = newColor.red + (redDiffuse + redReflect)*255;
            newColor.green = newColor.green + (greenDiffuse + greenReflect)*255;
            newColor.blue = newColor.blue + (blueDiffuse + blueReflect)*255;
        }
        else if((*it).lightType == infinity2){
            Vector3D vectorL = (*it).ldVector;
            double cosA = (n.x * vectorL.x) + (n.y * vectorL.y) + (n.z * vectorL.z);
            if(cosA > 0) {
                Vector3D r  = Vector3D::normalise(2 * n * cosA - vectorL);
                Vector3D camera = Vector3D::normalise(-PointP);
                double cosB = (r.x * camera.x) + (r.y * camera.y) + (r.z * camera.z);

                if(cosB > 0){
                    cosB = pow(cosB,reflection_coefficient);
                    redReflect = specularLightColor.red * (*it).specularLight.red * cosB;
                    greenReflect = specularLightColor.green * (*it).specularLight.green * cosB;
                    blueReflect = specularLightColor.blue * (*it).specularLight.blue * cosB;
                }
            }
            newColor.red = newColor.red + redDiffuse + redReflect;
            newColor.green = newColor.green + greenDiffuse + greenReflect;;
            newColor.blue = newColor.blue + blueDiffuse + blueReflect;
        }
    }

	//for some reason als ik 129 + 127 doe krijg in 0 terug dus omweg
	int red;
	int green;
	int blue;
    red  = (newColor.red + colorAfterLights.red);
    green = (newColor.green + colorAfterLights.green);
    blue = (newColor.blue + colorAfterLights.blue);

	if(red > 255) {
		red = 255;
	}
	if(green > 255) {
		green = 255;
	}
	if(blue > 255) {
		blue = 255;
	}

	newColor.red = red;
	newColor.green = green;
	newColor.blue = blue;

	i++;

	return newColor;

}



