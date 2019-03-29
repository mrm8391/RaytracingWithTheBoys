/*
Class for image formation capability. 
Constructor takes 2D std::vector of doubles. 
Can display and save an image. 

Example call:
	
	# Image Input Formation
	int no_of_cols = 5;
	int no_of_rows = 10;
	double initial_value = 0.5;
	std::vector<std::vector<double>> matrix;
	matrix.resize(no_of_rows, std::vector<double>(no_of_cols, initial_value));
	matrix[0][0] = 0.9;
	matrix[0][4] = 0.7;

	# Imager call
	Imager mage(matrix);
	mage.displayImage();
	mage.saveImage("testImage");
*/

#ifndef IMG_H

#define IMG_H

#include <iostream>
#include <CImg/CImg.h>
#include <vector>
#include <renderer\Vector.h>

using namespace std;
using namespace cimg_library;

class Imager {

public:
	/*
	Constructs internal representation of image. 
	Expects 0-1 normalized values in pixels. 
	*/
	Imager(vector<vector<Vector>> pixels);

	/*
	Displays image to screen without saving the image. 
	*/
	void displayImage();

	/*
	Saves an image as a .bmp file. Expects @param fileName to be under 1020 characters.  
	*/
	void saveImage(string fileName);

private:
	// Representation of image 
	CImg<unsigned char> img;

};

#endif
