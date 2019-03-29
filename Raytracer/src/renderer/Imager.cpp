#include <renderer/Imager.h>
#include <CImg/CImg.h>
#include <renderer/Vector.h>

Imager::Imager(vector<vector<Vector>> pixels)
{
	const int width = pixels[0].size();
	const int height = pixels.size();

	// Define a width x height RGB color image with 8 bits per color component.
	CImg<unsigned char> imgA(width, height, 1, 3);

	// Initialize img with data from @param pixels
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			//invert y to work with cimg
			int realY = height - y - 1;

			// Set each of the three color channels to this value (results in grayscale)
			for(int i = 0; i < 3; i++) imgA(x, realY, i) = pixels[x][y].vec[i];
		}
	}

	img = imgA;
}

void Imager::displayImage()
{
	img.display("Rendering with The Bois");
}

void Imager::saveImage(string fileName)
{
	fileName += ".ppm";
	// the save method requires a C-style char array
	char name[1024];
	strcpy(name, fileName.c_str());

	img.save(name);
}
