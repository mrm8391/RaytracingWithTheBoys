
#include "renderer/lighting/ToneReproduction.h"

using namespace std;

vector<vector<Vector>> ToneReproduction::LinearScale(vector<vector<Vector>> radiances){

	double maxR=0,maxG=0,maxB=0;

	//scan for max values in input
	for (int i = 0; i < radiances.size(); i++) {
		for (int j = 0; j < radiances[i].size(); j++) {
			Vector cur = radiances[i][j];

			if(cur.vec[0]>maxR) maxR=cur.vec[0];

			if(cur.vec[1]>maxG) maxG=cur.vec[1];

			if(cur.vec[2]>maxB) maxB=cur.vec[2];
		}
	}

	vector<vector<Vector>> pixels;

	//normalize and set output list
	for (int i = 0; i < radiances.size(); i++) {
		pixels.push_back(vector<Vector>());

		for (int j = 0; j < radiances[i].size(); j++) {
			Vector cur = radiances[i][j];

			double r = (cur.vec[0]/maxR) * 255,
				g = (cur.vec[1]/maxG) * 255,
				b = (cur.vec[2]/maxB) * 255;

			pixels[i].push_back(Vector(r,g,b));
		}
	}

	return pixels;
}

vector<vector<Vector>> ToneReproduction::WardScale(vector<vector<Vector>> radiances) {
	// STEP 1: Incoming in @param radiances
	vector<vector<double>> luminances;

	double maxLuminance = 0.0;
	double sigma = 0.0;

	// STEP 2: find luminance values, also scan for max luminance value in input
	// also calculate sigma for log-average luminance at the same time
	for (int i = 0; i < radiances.size(); i++) {
		luminances.push_back(vector<double>());

		for (int j = 0; j < radiances[i].size(); j++) {
			// Calculate luminance at this pixel
			Vector cur = radiances[i][j];
			// L(x,y) = 0.27R(x,y)+0.67G(x,y) +0.06B(x,y)
			double luminance = cur.vec[0] * 0.27 + cur.vec[1] * 0.67 + cur.vec[2] * 0.06;

			if (luminance > maxLuminance) maxLuminance = luminance;

			luminances[i].push_back(luminance);

			// Add log to sigma
			sigma += log(0.00001 + luminance);
		}
	}
	
	// number of pixels
	int N = radiances.size() * radiances[0].size();

	// find log-average luminance of scene
	// e ^ (1/N * sigma( log(delta + Luminance(x,y) ) )
	double L = exp(sigma / N);

	// calculate scale factor
	double innards = (1.219 + pow(maxLuminance / 2.0, 0.4)) / (1.219 + pow(L, 0.4));
	double sf = pow(innards, 2.5);
	
	vector<vector<Vector>> pixels;

	// STEP 3 and STEP 4: multiply by sf, scale by maxLuminance
	for (int i = 0; i < radiances.size(); i++) {
		pixels.push_back(vector<Vector>());

		for (int j = 0; j < radiances[i].size(); j++) {
			Vector cur = radiances[i][j];
			cur.scale(sf / maxLuminance); 
			
			pixels[i].push_back(cur);
		}
	}

	return pixels;
}
